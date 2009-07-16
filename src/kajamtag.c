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

static char* k_readIdentifier(char*);
static int k_isID3(char*);
static int k_isOgg(char*);

static kajamtag_t *global_tags;

int kajamtag_init(char* musicString)
{
    kajamtag_t *k_tags;
    global_tags = k_tags;
    FILE *musicFile;
    
    char* identifier = k_readIdentifier(musicString);
    musicFile = fopen(musicString, "rb");
    
    if(k_isID3(identifier))
    {
        int version = id3_header(musicFile);
    
        int bytes = 0;
        while((bytes = id3_frame(musicFile, version, k_tags)) != 0) 
        {
            if(bytes == 0)
                break;
        }
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);

        int bytes = 0;
        bytes = ogg_read(musicFile, k_tags);
    }
    
    fclose(musicFile);
    
    return 1;
}

/* Reads the first three bytes
 * retuns identifier string */
char* k_readIdentifier(char* strFile)
{
    FILE* file = fopen(strFile, "rb");
    char* identifier = malloc(3);
    fread(identifier, sizeof(char), 3, file);
    fclose(file);
    
    return identifier;
}

int k_isID3(char* identifier)
{
    int ID3 = 0;
    if(strcmp(identifier, "ID3") == 0)
        ID3 = 1;
    
    return ID3;
}

int k_isOgg(char* identifier)
{
    int ogg = 0;
    if(strcmp(identifier, "Ogg") == 0)
        ogg = 1;

    return ogg;
}

char* k_getTitle()
{
    return global_tags->title;
}

char* k_getAlbum()
{
    return global_tags->album;
}

char* k_getArtist()
{
    return global_tags->artist;
}
