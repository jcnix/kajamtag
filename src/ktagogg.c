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
 
#include "kajamtag/ktagogg.h"

int ogg_read(FILE *musicFile, tags_t tags)
{
    int readBytes = 0;
    int i = 0;
    char byte = 0;
    char strData[INIT_SIZE];
    int inTag = 0;
    size_t bytes;
    
    while(strcmp(strData, "vorbis+BCV") != 0)
    {
        bytes = fread(&byte, sizeof(char), 1, musicFile);
        readBytes++;
        
        /* Not an Alpha character, we'll assume
         * that it ends whatever we're trying to read */
        if(byte < 0x20 || byte > 0x7a)
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
    if(strcmp(id, tags.ids[KTITLE]) == 0)
        k_tags.title = data;
    else if(strcmp(id, tags.ids[KALBUM]) == 0)
        k_tags.album = data;
    else if(strcmp(id, tags.ids[KARTIST]) == 0)
        k_tags.artist = data;
    else if(strcmp(id, tags.ids[KGENRE]) == 0)
        k_tags.genre = data;
    else if(strcmp(id, tags.ids[KTRACK]) == 0)
        k_tags.track = atoi(data);
    
    bytes = malloc(INIT_SIZE);
    return 1;
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
