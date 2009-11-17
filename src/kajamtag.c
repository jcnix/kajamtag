/*
 * File:   kajamtag.c
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

#include "kajamtag/kajamtag.h"

static const char* getId3Char(Ktag);
static const char* getOggChar(Ktag);
static char* k_readIdentifier(char*);
static int k_isID3(char*);
static int k_isOgg(char*);

int kajamtag_read(char* musicString)
{
    if(strcmp(musicString, "") == 0)
        return 0;
    
    FILE *musicFile;
    
    char* identifier = k_readIdentifier(musicString);
    musicFile = fopen(musicString, "rb");
    
    badTag = 0;
    if(k_isID3(identifier))
    {
        free(identifier);
        int version = id3_header(musicFile);
        
        char *id;
        while(id3_frame(musicFile, version)) 
        {
        }
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);

        int bytes = 0;
        bytes = ogg_read(musicFile);
    }
    //"BAD_TAG" means the tag is not recognized.
    //It is neither ID3 nor Ogg.
    else {
        badTag = 1;
    }
    
    fclose(musicFile);
    
    return 1;
}

int kajamtag_write(char* file, Ktag tag, char* data)
{
    if(strcmp(file, "") == 0)
        return 0;
    
    FILE *musicFile;
    
    char* identifier = k_readIdentifier(file);
    musicFile = fopen(file, "rb+");
    
    int id3 = 0;
    int ogg = 0;
    
    if(k_isID3(identifier))
    {
        free(identifier);
        id3 = 1;
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);
        ogg = 1;
    }
    
    char* ctag;
    if(id3) id3_write(musicFile, id3tags[tag], data);
    
    fclose(musicFile);
    
    return 1;
}

static const char* getId3Char(Ktag t)
{
    return id3tags[t];
}

static const char* getOggChar(Ktag t)
{
    return oggtags[t];
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

char* k_getData(Ktag tag)
{
    if(badTag)
        return "BAD_TAG";
    
    char* data;
    switch(tag)
    {
        case KTITLE:
            data = k_tags.title;
            break;
        case KALBUM:
            data = k_tags.album;
            break;
        case KARTIST:
            data = k_tags.artist;
            break;
        case KGENRE:
            data = k_tags.genre;
            break;
        default:
            //Should never happen
            break;
    }
    
    if(data == NULL)
        data = "NO_DATA";
    
    return data;
}

char* k_getTitle()
{
    if(badTag)
        return "BAD_TAG";
    
    char* data = k_tags.title;
    
    if(data == NULL)
        data = "NO_DATA";
    
    return data;
}

char* k_getArtist()
{
    if(badTag)
        return "BAD_TAG";
    
    char* data = k_tags.artist;
    
    if(data == NULL)
        data = "NO_DATA";
    
    return data;
}
char* k_getAlbum()
{
    if(badTag)
        return "BAD_TAG";
    
    char* data = k_tags.album;
    
    if(data == NULL)
        data = "NO_DATA";
    
    return data;
}

int k_getTrack()
{
    if(badTag)
        return 0;
    
    return k_tags.track;
}
