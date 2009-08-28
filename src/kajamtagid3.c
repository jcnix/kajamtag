/*
 * File:   id3.c
 * Author: Casey Jones
 *
 * This file is part of KaJamTag.
 *
 * KaJamTag is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KaJamTag is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with KaJamTag.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kajamtagid3.h"

/* Returns the ID3 tag version */
int id3_header(FILE *f)
{    
    char *id = id3_readID(f);
    
    int majorVer;
    fread(&majorVer, 1, 1, f);
    
    int minorVer = 0;
    fread(&minorVer, 1, 1, f);

    char flags = id3_readFlags(f);
    
    int size = id3_readSize(f, 4);
    
    return majorVer;
}

/* returns number of bytes the frame is */
int id3_frame(FILE *f, int version)
{
    char *id = id3_readID(f);
    
    int size = id3_readSize(f, version);
    //Blank header, probably done reading
    if(size == 0) {
        return 0;
    }

    int flags = id3_readFlags(f);
    
    //skip a byte, not sure what the blank byte is for... padding?
    id3_readByte(f);
    
    char *data = id3_readData(f, size);
    if(data == NULL)
        return 0;
    
    id3_storeData(id, data, size);
    free(id);
    free(data);

    return 1;
}

int id3_storeData(char* identifier, char* data, int size)
{    
    char* d = strdup(data);
    if(strncmp(identifier, "TIT2", 4) == 0)
        k_tags.title = d;
    else if(strncmp(identifier, "TALB", 4) == 0)
        k_tags.album = d;
    else if(strncmp(identifier, "TPE1", 4) == 0)
        k_tags.artist = d;
    else if(strncmp(identifier, "TCON", 4) == 0)
        k_tags.genre = d;
    else if(strncmp(identifier, "TRCK", 4) == 0)
        k_tags.track = atoi(d);
    
    return 1;
}

int id3_writeData(char* identifier, char* data)
{
    int size = strlen(data);
    char *id;
    
    return 1;
}

char* id3_readID(FILE* f)
{
    char *id = malloc(4*sizeof(char));
    fread(id, sizeof(char), 4, f);
    return id;
}

int id3_readSize(FILE* f, int version)
{
    int size = 0;
    fread(&size, sizeof(int), 1, f);
    
    //ID3 2.4 uses synchronized ints, 2.3 does not 
    if(version == 4) 
        size = TAG_TO_INT(htobe32(size));
    else if(version == 3) 
        size = htobe32(size);
    
    return size;
}

int id3_readFlags(FILE* f)
{
    int flags = 0;
    fread(&flags, 2, 1, f);
    return flags;
}

char* id3_readData(FILE* f, int size)
{
    //Using a malloc here because in some cases, we try
    //allocating a huge amount of memory.  Using an array 
    //we couldn't check that.
    char* data = malloc(size*sizeof(char));
    if(data == NULL)
        return NULL;
    
    fread(data, sizeof(char), size - 1, f);
    *(data + size-1) = '\0';
    
    return data;
}

int id3_readByte(FILE* f)
{
    int byte = 0;
    fread(&byte, sizeof(char), 1, f);
    return byte;
}

/* returns 0 or 1, depending on if a flag is set or not */
int id3_getFlag(int byte, int bit)  
{  
    return (byte & 1 << bit)? 1: 0;  
}
