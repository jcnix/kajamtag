/*
 * File:   ogg.c
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
 
#include "ogg.h"

int ogg_read(FILE *musicFile)
{
    int readBytes = 0;
    int i = 0;
    char byte = 0;
    char* bytes = malloc(INIT_SIZE);
    int inTag = 0;
    
    while(readBytes <= 500)
    {
        fread(&byte, sizeof(char), 1, musicFile);
        readBytes++;
        
        /* Not an Alpha character, we'll assume
         * that it ends whatever we're trying to read */
        if(byte < 0x20 || byte > 0x7a)
        {
            if(inTag) {
                inTag = 0;
                *(bytes+i) = '\0';
                i = 0;
                ogg_storeData(bytes);
            }
        }
        /* We're reading alpha characters, store these */
        else
        {
            inTag = 1;
            *(bytes+i) = byte;
            i++;
        }
    }

    return 0;
}

int ogg_storeData(char* bytes)
{
    printf("%s\n", bytes);
    //TODO: Lets store some data...
    
    free(bytes);
    bytes = malloc(INIT_SIZE);
    return 0;
}
