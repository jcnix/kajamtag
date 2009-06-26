/*
 * File:   id3.c
 * Author: Casey Jones
 *
 * This file is part of KaJamTag.
 *
 * KaJamTag is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KaJamTag is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KaJamTag.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "id3.h"

/* Returns the ID3 tag version */
int id3_header(FILE *musicFile)
{
    char* identifier = malloc(3);
    fread(identifier, sizeof(char), 3, musicFile);
    
    int majorVer;
    fread(&majorVer, 1, 1, musicFile);
    
    int minorVer = 0;
    fread(&minorVer, sizeof(char), 1, musicFile);

    char flags = 0;
    fread(&flags, sizeof(char), 1, musicFile);
    int usynch = getFlag(flags, 7);
    int exHeader = getFlag(flags, 6);
    int exp = getFlag(flags, 5);
    int footer = getFlag(flags, 4);
    printf("Flags: %d %d %d %d\n", usynch, exHeader, exp, footer);

    int size = 0;
    fread(&size, sizeof(int), 1, musicFile);
    size = TAG_TO_INT(htobe32(size));
    
    free(identifier);
    
    return majorVer;
}

/* returns number of bytes the frame is */
int id3_frame(FILE *musicFile, int version)
{
    char* identifier = malloc(4);
    fread(identifier, sizeof(char), 4, musicFile);
    
    int size = 0;
    fread(&size, sizeof(int), 1, musicFile);
    
    //ID3 2.4 uses synchronized ints, 2.3 does not 
    if(version == 4) size = TAG_TO_INT(htobe32(size));
    else if(version == 3) size = htobe32(size);

    //Blank header, probably done reading
    if(size == 0) {
        free(identifier);
        return 0;
    }

    int flags = 0;
    fread(&flags, 2, 1, musicFile);
    
    //skip a byte, not sure what the blank byte is for... padding?
    int skip = 0;
    fread(&skip, sizeof(char), 1, musicFile);
    
    char *data = malloc(size);
    fread(data, sizeof(char), size - 1, musicFile);
    
    printf("Ident: %s\n", identifier);
    printf("Size: %d\n", size);
    printf("Data: %s\n", data);
    
    storeData(identifier, data, size);
    
    //Add 10 to include size of frame header
    return size + 10;
}

int storeData(char* identifier, char* data, int size)
{    
    if(strcmp(identifier, "TIT2") == 0)
    {
        tags.title = malloc(size);
        strcpy(tags.title, data);
    }
    else if(strcmp(identifier, "TALB") == 0)
    {
        tags.album = malloc(size);
        strcpy(tags.album, data);
    }
    else if(strcmp(identifier, "TPE1") == 0)
    {
        tags.artist = malloc(size);
        strcpy(tags.artist, data);
    }
    
    free(identifier);
    free(data);
    
    return 1;
}

int getFlag(int byte, int bit)  
{  
    return (byte & 1 << bit)? 1: 0;  
} 
