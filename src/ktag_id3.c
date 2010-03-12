/*
 * File:   ktag_id3.c
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

#include "kajamtag/ktag_id3.h"

int id3_read(FILE* f, tags_t tags)
{
    int version = id3_header(f);
        
    if(version == 2)
        tags.ids = (char**) tags_id3_v2_2;
    else
        tags.ids = (char**) tags_id3;
    
    int read = 1;
    while(read == 1) 
    {
        read = id3_frame(f, version, tags);
    }
}

/* Returns the ID3 tag version */
int id3_header(FILE *musicFile)
{
    size_t bytes;
    char identifier[3];
    //bytes = fread(identifier, sizeof(char), 3, musicFile);
    fseek(musicFile, 3, SEEK_SET);
    
    int majorVer = 0;
    bytes = fread(&majorVer, 1, 1, musicFile);
    
    int minorVer = 0;
    //bytes = fread(&minorVer, sizeof(char), 1, musicFile);
    fseek(musicFile, 1, SEEK_CUR);
    
    char flags = 0;
    //bytes = fread(&flags, sizeof(char), 1, musicFile);
    fseek(musicFile, 1, SEEK_CUR);
    
    int size = 0;
    bytes = fread(&size, sizeof(int), 1, musicFile);
    size = TAG_TO_INT(htobe32(size));
    
    return majorVer;
}

/* returns number of bytes the frame is */
int id3_frame(FILE *f, int version, tags_t tags)
{
    char *id;
    int size;
    int flags;
    char *data;
    
    int read = id3_readFullFrame(f, version, &id, &size, &flags, &data);
    
    if(read == ILLEGAL_SIZE)
    {
        return 0;
    }
    
    id3_storeData(id, data, tags);
    free(id);
    free(data);

    return KTAG_OKAY;
}

int id3_write(FILE* f, Ktag tag, char* data)
{
    int version = id3_header(f);
    
    tags_t tags;
    if(version == 2)
        tags.ids = (char**) tags_id3_v2_2;
    else
        tags.ids = (char**) tags_id3;
    
    char* identifier = tags.ids[tag];
    
    int size = strlen(data);
    int oldSize = 0;
    
    int fullFrameRead = 1;
    char *nid, *ndata;
    int nsize, flags;
    
    //Find the frame we want to rewrite
    while(fullFrameRead != 0)
    {
        char *id = id3_readID(f);
        
        if(strcmp(id, identifier) == 0)
        {
            oldSize = id3_readSize(f, version) - 1; //subtract null
            fseek(f, -4, SEEK_CUR);
            break;
        }
        else
        {
            //rewind 4 bytes since readID reads 4 bytes
            //and finish reading the frame
            fseek(f, -4, SEEK_CUR);
            fullFrameRead = id3_readFullFrame(f, version, &nid, &nsize, &flags,
                                              &ndata);
            
            free(ndata);
            free(nid);
        }
        free(id);
    }
    int bookmarkPos = ftell(f); //bookmark location
    
    int diffSize = oldSize - size;
    fseek(f, oldSize+7, SEEK_CUR); //advance file pointer
    
    /* Rewrite the rest of the data
     * We're going to cheat a little here and find how much data there is left
     * and then read the rest as a big hunk and then write it again.
     * This is because we'd have to read backwards if the new data is
     * larger than the old data, otherwise we'd overwrite data we haven't read yet.*/
    int sumSize = 0;
    while(fullFrameRead != 0)
    {
        fullFrameRead = id3_readFullFrame(f, version, &nid, &nsize, &flags, 
                                          &ndata);

        if(fullFrameRead != 0)
        {
            free(ndata);
            free(nid);
        }
        if(nsize < 500000) // ~500kb
        {
            sumSize += nsize + 11;
        }
    }
    fseek(f, bookmarkPos + oldSize + 7, SEEK_SET);
    char* bigBuffer = malloc(sumSize);
    fread(bigBuffer, sizeof(char), sumSize, f);
    //return to original spot, and adjust to where the new spot should be
    fseek(f, -sumSize - diffSize, SEEK_CUR);
    fwrite(bigBuffer, sizeof(char), sumSize, f); //write the big hunk
    free(bigBuffer);
    
    fseek(f, bookmarkPos, SEEK_SET); //return to where the data should go
    
    //add terminating null of the data string
    id3_writeSize(f, size + 1, version);
    
    id3_readFlags(f); //advancing the file pointer
    fseek(f, 1, SEEK_CUR);
    
    //Write the new data
    id3_writeData(f, data);
    
    //Rewrite the ID3 tag size in the header
    fseek(f, 6, SEEK_SET);
    int isize = 0;
    fread(&isize, sizeof(int), 1, f);
    fseek(f, 6, SEEK_SET); //return to where we were
    isize = TAG_TO_INT(htobe32(isize));
    isize = htobe32(TAG_TO_INT(isize - diffSize));
    fwrite(&isize, sizeof(int), 1, f);

    return KTAG_OKAY;
}

int id3_storeData(char* identifier, char* data, tags_t tags)
{
    char* d = strdup(data);
    util_storeData(identifier, d, tags);
    
    return 1;
}

//This function reads a frame and returns all data
int id3_readFullFrame(FILE* f, int version, char **id, int *size, int *flags, char **data)
{
    *id = id3_readID(f);
    
    *size = id3_readSize(f, version);
    //Blank header, probably done reading
    if(*size <= 0 || *size >= 32000) // ~32kb
        return ILLEGAL_SIZE;
    
    *flags = id3_readFlags(f);
    fseek(f, 1, SEEK_CUR); //skip an unused byte
    
    *data = id3_readData(f, *size);
    if(data == NULL)
        return 0;
    
    return KTAG_OKAY;
}

char* id3_readID(FILE* f)
{
    char *id = malloc(4*sizeof(char));
    size_t bytes = fread(id, sizeof(char), 4, f);
    return id;
}

int id3_readSize(FILE* f, int version)
{
    int size = 0;
    size_t bytes = fread(&size, sizeof(int), 1, f);
    
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
    size_t bytes = fread(&flags, 2, 1, f);
    return flags;
}

char* id3_readData(FILE* f, int size)
{
    char* data = malloc(size*sizeof(char));
    if(data == NULL)
        return NULL;
    
    if(id3_isUTF16(f))
    {
        //readData_UTF16 will reallocate it.
        free(data);
        data = id3_readData_UTF16(f, size);
    }
    else
    {
        size_t bytes = fread(data, 1, size - 1, f);
        *(data + size - 1) = '\0';
    }
    
    return data;
}

char* id3_readData_UTF16(FILE *f, int size)
{   
    //We don't want to reread the two byte UTF16 identifier
    fseek(f, 2, SEEK_CUR);
    size -= 2;
    
    char* data = malloc(size/2);
    if(data == NULL)
        return NULL;
    
    int i;
    int j = 0;
    for(i = 0; i < size -1; i++)
    {
        char c = ' ';
        fread(&c, 1, 1, f);
        if(c == '\0')
        {
            continue;
        }
        
        data[j] = c;
        j++;
    }
    
    *(data + (size/2)) = '\0';
    return data;
}

/* returns 0 or 1, depending on if a flag is set or not */
int id3_getFlag(int byte, int bit)  
{  
    return (byte & 1 << bit)? 1: 0;  
}

int id3_isUTF16(FILE* f)
{
    int utf;
    size_t bytes = fread(&utf, 2, 1, f);
    
    if(utf == 0xfeff)
    {
        //return to original position
        fseek(f, -2, SEEK_CUR);
        return 1;
    }
    else
    {
        fseek(f, -2, SEEK_CUR);
        return 0;
    }
}

int id3_writeSize(FILE* f, int size, int version)
{
    if(version == 4)
        size = htobe32(TAG_TO_INT(size));
    else if(version == 3)
        size = be32toh(size);
    
    size_t bytes = fwrite(&size, sizeof(int), 1, f);
    return KTAG_OKAY;
}

int id3_writeData(FILE* f, char* data)
{
    size_t bytes = fwrite(data, sizeof(char), strlen(data), f);
    return KTAG_OKAY;
}
