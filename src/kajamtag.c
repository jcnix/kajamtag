/*
 * File:   kajamtag.c
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

#include "kajamtag.h"

int kajamtag_init(char* musicString)
{    
    FILE *musicFile;
    musicFile = fopen(musicString, "rb");
    
    int totalBytes = findHeader(musicFile);
    int foundBytes = 10; //Header is 10 bytes
    
    printf("Total Bytes: %d\n", totalBytes);
    printf("Found Bytes: %d\n", foundBytes);
    
    while(foundBytes < totalBytes) {
        foundBytes += getFrameHeader(musicFile);
        printf("Found Bytes: %d\n", foundBytes);
    }
    
    return 1;
}

/* Returns the number of bytes the ID3 tag is. */
int findHeader(FILE *musicFile)
{
    char* identifier = malloc(3);
    fread(identifier, 1, 3, musicFile);
    
    int majorVer = 0;
    fread(&majorVer, 1, 1, musicFile);
    
    int minorVer = 0;
    fread(&minorVer, 1, 1, musicFile);

    char flags = 0;
    fread(&flags, 1, 1, musicFile);

    int size = 0;
    fread(&size, 4, 1, musicFile);
    size = TAG_TO_INT(htobe32(size));
    
    free(identifier);
    
    return size;
}

/* returns number of bytes the frame is */
int getFrameHeader(FILE *musicFile)
{
    char* identifier = malloc(4);
    fread(identifier, 1, 4, musicFile);
    
    int size = 0;
    fread(&size, 4, 1, musicFile);
    size = TAG_TO_INT(htobe32(size));

    int flags = 0;
    fread(&flags, 2, 1, musicFile);
    
    //skip a byte, not sure what the blank byte is for... padding?
    int skip = 0;
    fread(&skip, 1, 1, musicFile);
    
    char *data = malloc(size - 1);
    fread(data, 1, size - 1, musicFile);
    
    printf("Identifier: %s\n", identifier);
    
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
    
    free(identifier);
    free(data);
    
    return 1;
}

char* getTitle()
{
    return tags.title;
}

char* getAlbum()
{
    return tags.album;
}
