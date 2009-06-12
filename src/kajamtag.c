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
    kajamtag_t tags;
    FILE *musicFile;
    musicFile = fopen(musicString, "rb");
    
    findHeader(musicFile);
    getFrameHeader(musicFile, tags);
    
    return 1;
}

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
    
    printf("%s\n", identifier);
    printf("%d ", majorVer);
    printf("%d\n", minorVer);
    printf("%d\n", flags);
    printf("%d\n", size);
    
    return 1;
}

int getFrameHeader(FILE *musicFile, kajamtag_t tags)
{
    char* header = malloc(4);
    fread(header, 1, 4, musicFile);

    int size = 0;
    fread(&size, 4, 1, musicFile);
    size = TAG_TO_INT(htobe32(size));

    int flags = 0;
    fread(&flags, 2, 1, musicFile);
    
    printf("%s\n", header);
    printf("%d\n", size);
    printf("%d\n", flags);
    
    //skip a byte, not sure what the blank byte is for... padding?
    int skip = 0;
    fread(&skip, 1, 1, musicFile);
    
    char *data = malloc(size - 1);
    fread(data, 1, size - 1, musicFile);
    
    if(strcmp(header, "TIT2") == 0)
    {
        tags.title = malloc(size);
        tags.title = data;
    }
    
    printf("%s\n", tags.title);
    
    return 1;
}
