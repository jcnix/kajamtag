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

int flac_read_to_comments(FILE* f)
{
    size_t bytes;
    int size;
    int header = 0;
    
    char* id = malloc(4*sizeof(char));
    bytes = fread(id, 1, 4, f);
    free(id);
    
    int version;
    bytes = fread(&version, 1, 1, f);
    
    size = ogg_readSize(f);
    ogg_skipBytes(f, size);
    
    while(1)
    {
        bytes = fread(&header, 1, 1, f);
        size = ogg_readSize(f);
        
        if(header != 4)
            ogg_skipBytes(f, size);
        else
            break;
    }

    return size;
}

int flac_read(FILE *f, tags_t tags)
{
    int size = flac_read_to_comments(f);
    int readBytes = 0;
    
    int comment_size = 0;
    comment_size = ogg_readCommentSize(f);
    readBytes += 4;

    /* +4 because there are 4 bytes between where
     * it's left off, and where the size of the first
     * tag */
    ogg_skipBytes(f, comment_size + 4);
    readBytes += comment_size + 4;
    
    while(readBytes < size)
    {
        char* data;
        readBytes += ogg_readComment(f, &data);
        char* id = ogg_storeData(data, tags);
        free(id);
    }
    
    return ftell(f);
}
