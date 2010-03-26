/*
 * File:   ktag_ogg.c
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

int ogg_read(FILE *f, tags_t tags)
{
    fseek(f, 27, SEEK_CUR);
    int size = 0;
    fread(&size, 1, 1, f);
    fseek(f, size, SEEK_CUR);
    
    fseek(f, 26, SEEK_CUR);
    fread(&size, 1, 1, f);
    fseek(f, size, SEEK_CUR);
    
    fseek(f, 1 + strlen("vorbis"), SEEK_CUR);
    fread(&size, 1, 1, f);
    fseek(f, size + 3, SEEK_CUR);
    fread(&size, 1, 1, f);
    
    ogg_readComments(f, tags, size);
    
    return 1;
}

int ogg_read_comments_to(FILE* f, tags_t tags, Ktag ktag, int num)
{
    size_t bytes;

    int comment_size = 0;
    ogg_skipBytes(f, 3);
    
    int i = 0;
    while(i < num)
    {
        char* data;
        ogg_readComment(f, &data);
        char* id = ogg_storeData(data, tags);
        i++;

//         if(ktag != KNULL && strcmp(id, tags.ids[ktag]) == 0)
//         {
//             int s = -s;
//             fseek(f, s, SEEK_CUR);
//             break;
//         }
        free(id);
    }

    return ftell(f);
}

int ogg_readComment(FILE* f, char** data)
{
    int readBytes = 0;
    int comment_size = ogg_readCommentSize(f);
    readBytes += 1;

    char* d = ogg_readData(f, comment_size);
    d[comment_size] = '\0';
    *data = d;
    
    readBytes += comment_size + 3;
    
    return readBytes;
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
    return ogg_read_comments_to(f, tags, KNULL, size);
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

int ogg_readCommentSize(FILE* f)
{
    int size = 0;
    fread(&size, 4, 1, f);

    return size;
}

char* ogg_readData(FILE* f, int size)
{
    //+1 to make room for \0
    char* data = malloc(size + 1);
    fread(data, 1, size, f);
    //printf("data: %s\n", data);

    return data;
}

int ogg_skipBytes(FILE* f, int size)
{
    fseek(f, size, SEEK_CUR);
}

