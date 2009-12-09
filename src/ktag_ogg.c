/*
 * File:   kajamtagogg.c
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
 
#include "kajamtag/ktag_ogg.h"

int ogg_read(FILE *musicFile, tags_t tags)
{
    size_t bytes;
    int size;
    int header = 0;
    
    char* id = malloc(4*sizeof(char));
    bytes = fread(id, 1, 4, musicFile);
    free(id);
    
    int version;
    bytes = fread(&version, 1, 1, musicFile);
    
    size = ogg_readSize(musicFile);
    ogg_skipBytes(musicFile, size);
    
    while(1)
    {
        bytes = fread(&header, 1, 1, musicFile);        
        size = ogg_readSize(musicFile);
        
        if(header != 4)
            ogg_skipBytes(musicFile, size);
        else
            break;
    }
    
    //Read through the Xiph comment area and store the data.
    ogg_readComments(musicFile);

    return 0;
}

int ogg_storeData(char* bytes, tags_t tags)
{
    if(strchr(bytes, '=') == NULL)
    {
        return 0;
    }
    
    char* tokens = strtok(bytes, "=");
    if(tokens == NULL)
        return 0;
    
    char* id = strdup(tokens);
    id = strup(id);
    
    tokens = strtok(NULL, "=");    
    if(tokens == NULL)
        return 0;
    
    char* data = strdup(tokens);
    
    //Store some data!
    util_storeData(id, data, tags);
    free(id);
    
    return 1;
}

int ogg_readComments(FILE *f)
{
    int readBytes = 0;
    int i = 0;
    char byte = 0;
    char strData[INIT_SIZE] = "";
    int inTag = 0;
    
    while(strcmp(strData, "vorbis+BCV") != 0  && readBytes < size)
    {
        bytes = fread(&byte, sizeof(char), 1, f);
        readBytes++;
        
        /* Not an Alpha character, we'll assume
        * that it ends whatever we're trying to read */
        if(byte < 0x20 || byte > 0x7d)
        {
            if(inTag) {
                inTag = 0;
                strData[i] = '\0';
                i = 0;
                ogg_storeData(strData, tags);
            }
        }
        /* We're reading alpha characters, store these */
        else
        {
            inTag = 1;
            strData[i] = byte;
            i++;
        }
    }
}

int ogg_readSize(FILE* f)
{
    int size;
    fread(&size, 3, 1, f);
    
    //Convert to big endian
    size = htobe32(size);
    
    /* Shift one byte; 8 bits.
     * Since the size is stored as 3 bytes,
     * the 4th byte is just 0x00 */
    size >>= 8;
    
    return size;
}

int ogg_skipBytes(FILE* f, int size)
{
    char* skip = malloc(size);
    fread(skip, 1, size, f);
    free(skip);
}

//Convert string to upper case
char* strup(char* in)
{
    char c;
    int i;
    
    for(i = 0; i < strlen(in); i++)
    {
        c = in[i];
        if(islower(c))
            c = toupper(c);
        in[i] = c;
    }
    
    return in;
}
