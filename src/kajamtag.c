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
    
    char* identifier = readIdentifier(musicFile);
    
    if(isID3(identifier))
    {
        free(identifier);
        int version = id3_header(musicFile);
    
        int bytes = 0;
        while((bytes = id3_frame(musicFile, version)) != 0) 
        {
            if(bytes == 0)
                break;
        }
    }
    else if(isOgg(identifier))
    {
        free(identifier);

        int bytes = 0;
        bytes = ogg_read(musicFile);
    }
    
    return 1;
}

/* Reads the first three bytes
 * retuns identifier string */
char* readIdentifier(FILE* file)
{
    char* identifier = malloc(3);
    fread(identifier, sizeof(char), 3, file);
    
    return identifier;
}

int isID3(char* identifier)
{
    int ID3 = 0;
    if(strcmp(identifier, "ID3") == 0)
        ID3 = 1;
    
    return ID3;
}

int isOgg(char* identifier)
{
    int ogg = 0;
    if(strcmp(identifier, "Ogg") == 0)
        ogg = 1;

    return ogg;
}

char* getTitle()
{
    return tags.title;
}

char* getAlbum()
{
    return tags.album;
}

char* getArtist()
{
    return tags.artist;
}

