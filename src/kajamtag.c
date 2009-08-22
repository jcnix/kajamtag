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

int kajamtag_init(char* musicString)
{
    if(strcmp(musicString, "") == 0)
        return 0;
    
    FILE *musicFile;
    
    char* identifier = k_readIdentifier(musicString);
    musicFile = fopen(musicString, "rb");
    
    if(k_isID3(identifier))
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
    else if(k_isOgg(identifier))
    {
        free(identifier);

        int bytes = 0;
        bytes = ogg_read(musicFile);
    }
    //"BAD_TAG" means the tag is not recognized.
    //It it neither ID3 nor Ogg.
    else {
        k_tags.title = "BAD_TAG";
        k_tags.artist = "BAD_TAG";
        k_tags.album = "BAD_TAG";
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
    if(strncmp(identifier, "ID3", 3) == 0)
        ID3 = 1;
    
    return ID3;
}

int k_isOgg(char* identifier)
{
    int ogg = 0;
    if(strncmp(identifier, "Ogg", 3) == 0)
        ogg = 1;

    return ogg;
}

char* k_getTag(Tag tag)
{
    char* data;
    switch(tag)
    {
        case TITLE:
            data = k_tags.title;
            break;
        case ALBUM:
            data = k_tags.album;
            break;
        case ARTIST:
            data = k_tags.artist;
            break;
        case GENRE:
            data = k_tags.genre;
            break;
        default:
            //Should never happen
            break;
    }
}

char* k_getTitle()
{
    if(k_tags.title == NULL)
        k_tags.title = "NO_DATA";
    
    return k_tags.title;
}

char* k_getAlbum()
{
    if(k_tags.album == NULL)
        k_tags.album = "NO_DATA";
    
    return k_tags.album;
}

char* k_getArtist()
{
    if(k_tags.artist == NULL)
        k_tags.artist = "NO_DATA";
    
    return k_tags.artist;
}

char* k_getGenre()
{
    if(k_tags.artist == NULL)
        k_tags.artist = "NO_DATA";
    
    return k_tags.genre;
}

int k_getTrack()
{
    return k_tags.track;
}
