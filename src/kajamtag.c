/*
 * File:   main.c
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

int main()
{    
    FILE *musicFile;
    musicFile = fopen("test.mp3", "rb");
    
    findHeader(musicFile);
    
    char* titleHeader = malloc(4);
    fread(titleHeader, 1, 4, musicFile);

    int titleSize = 0;
    fread(&titleSize, 4, 1, musicFile);

    int titleFlags;
    fread(&titleFlags, 2, 1, musicFile);

    char* title1 = malloc(10);
    fread(title1, 1, 10, musicFile);

    char* title = malloc(10);
    fread(title, 1, 10, musicFile);
    
    printf("%s\n", titleHeader);
    
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
    size = TAG_TO_INT(htonl(size));
    
    printf("%s\n", identifier);
    printf("%d ", majorVer);
    printf("%d\n", minorVer);
    printf("%d\n", flags);
    printf("%d\n", size);
    
    return 1;
}
