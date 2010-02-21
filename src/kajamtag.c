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

static char* k_readIdentifier(FILE*);
static int k_isID3(char*);
static int k_isOgg(char*);
static int k_isFlac(char*);

int kajamtag_read(char* musicString)
{
    FILE *musicFile;
    tags_t tags;
    
    musicFile = fopen(musicString, "rb");
    if(musicFile == NULL)
    {
        printf("File %s not found.\n", musicString);
        return 0;
    }
    
    char* identifier = k_readIdentifier(musicFile);
    
    badTag = 0;
    if(k_isID3(identifier))
    {
        free(identifier);
        int version = id3_header(musicFile);
        
        if(version == 2)
            tags.ids = (char**) tags_id3_v2_2;
        else
            tags.ids = (char**) tags_id3;
        
        while(id3_frame(musicFile, version, tags)) 
        {
        }
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);
        tags.ids = (char**) tags_ogg;

        int bytes = 0;
        bytes = ogg_read(musicFile, tags);
    }
    else if(k_isFlac(identifier))
    {
        free(identifier);
        tags.ids = (char**) tags_ogg;
        
        int bytes = 0;
        bytes = flac_read(musicFile, tags);
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
    musicFile = fopen(file, "rb+");
    
    char* identifier = k_readIdentifier(musicFile);
    
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
    
    if(id3)
    {
        id3_write(musicFile, tag, data);
    }
        
    fclose(musicFile);
    
    return 1;
}

int kajamtag_close()
{
    free(k_tags.title);
    free(k_tags.album);
    free(k_tags.artist);
    free(k_tags.genre);
    free(k_tags.composer);
}

/* Reads the first three bytes
 * retuns identifier string */
char* k_readIdentifier(FILE* file)
{   
    //Use 4 now.  If the file is a .flac, it will be four chars.
    //For ID3 continue using strncmp with 3 chars.
    char* identifier = malloc(4);
    fread(identifier, sizeof(char), 4, file);
    fseek(file, -4, SEEK_CUR);
    
    return identifier;
}

int k_isID3(char* id)
{
    int ID3 = 0;
    if(strncmp(id, "ID3", 3) == 0)
        ID3 = 1;
    
    return ID3;
}

int k_isOgg(char* id)
{
    int ogg = 0;
    if(strncmp(id, "OggS", 4) == 0)
        ogg = 1;

    return ogg;
}

int k_isFlac(char* id)
{
    int flac = 0;
    if(strncmp(id, "fLaC", 4) == 0)
        flac = 1;

    return flac;
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
        case KCOMPOSER:
            data = k_tags.composer;
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

char* k_getComposer()
{
    if(badTag)
        return 0;
    
    return k_tags.composer;
}
