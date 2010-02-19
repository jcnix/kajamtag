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
    ogg_readComments(musicFile, tags, 0);    
    
    return 0;
}

int ogg_read_comments_to(FILE* f, tags_t tags, Ktag ktag, int size)
{
    int readBytes = 0;
    int i = 0;
    char byte = 0;
    char strData[INIT_SIZE] = "";
    int inTag = 0;
    size_t bytes;
    
    //We don't know how big it really is
    //Assuming 1Kb
    if(size <= 0)
        size = 1024;
    
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
                int s = sizeof(strData);
                char* id = ogg_storeData(strData, tags);

                if(ktag != KNULL && strcmp(id, tags.ids[ktag]) == 0)
                {
                    int s = -s;
                    fseek(f, s, SEEK_CUR);
                    break;
                }
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
    
    return ftell(f);
}

char* ogg_storeData(char* bytes, tags_t tags)
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
    
    return id;
}

int ogg_readComments(FILE *f, tags_t tags, int size)
{
    ogg_read_comments_to(f, tags, KNULL, size);
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
    fseek(f, size, SEEK_CUR);
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
