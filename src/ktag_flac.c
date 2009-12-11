/*
 * File:   ktag_flac.c
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

#include "kajamtag/ktag_flac.h"

int flac_read(FILE *musicFile, tags_t tags)
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
    ogg_readComments(musicFile, tags, size);

    return 0;
}
