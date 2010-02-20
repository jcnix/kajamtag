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

    int comment_size = 0;
    comment_size = ogg_readCommentSize(f);
    readBytes += 1;

    /* +6 because there are 6 bytes between where
     * it's left off, and where the size of the first
     * tag */
    ogg_skipBytes(f, comment_size + 7);
    readBytes += comment_size + 7;
    
    while(readBytes < size)
    {
        comment_size = 0;
        comment_size = ogg_readCommentSize(f);
        readBytes += 1;
        //Three null bytes
        ogg_skipBytes(f, 3);

        char* data = ogg_readData(f, comment_size);
        data[comment_size + 1] = '\0';
        readBytes += comment_size + 3;

        char* id = ogg_storeData(data, tags);

        if(ktag != KNULL && strcmp(id, tags.ids[ktag]) == 0)
        {
            int s = -s;
            fseek(f, s, SEEK_CUR);
            break;
        }
        free(id);
    }
    printf("read one file\n");

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

int ogg_readCommentSize(FILE* f)
{
    int size = 0;
    fread(&size, 1, 1, f);

    return size;
}

char* ogg_readData(FILE* f, int size)
{
    //+1 to make room for \0
    char* data = malloc(size + 1);
    fread(data, 1, size, f);

    return data;
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
