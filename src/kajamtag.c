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

static int isUtf16;
static int badTag;
static kajamtag_t k_tags;

static int isID3 = 0;
static int isXiph = 0;

static int tried_utf8 = 0;
static int tried_utf16 = 0;

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
        id3_read(musicFile, tags);
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);
        tags.ids = (char**) tags_ogg;

        ogg_read(musicFile, tags);
    }
    else if(k_isFlac(identifier))
    {
        free(identifier);
        tags.ids = (char**) tags_ogg;
        
        flac_read(musicFile, tags);
    }
    
    //"BAD_TAG" means the tag is not recognized.
    //It is neither ID3 nor Ogg.
    else
    {
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
    
    if(k_isID3(identifier))
    {
        free(identifier);
        id3_write(musicFile, tag, data);
    }
    else if(k_isOgg(identifier))
    {
        free(identifier);
        ogg_write(musicFile, tag, data);
    }
        
    fclose(musicFile);
    
    return 1;
}

int kajamtag_isUtf16()
{
    return isUtf16;
}

void kajamtag_setUtf16(int i)
{
    isUtf16 = i;
}

int kajamtag_close()
{
    sfree(k_tags.title);
    sfree(k_tags.album);
    sfree(k_tags.artist);
    sfree(k_tags.genre);
    sfree(k_tags.composer);

    sfree(k_tags.wtitle);
    sfree(k_tags.walbum);
    sfree(k_tags.wartist);
    sfree(k_tags.wgenre);
    sfree(k_tags.wcomposer);
    
    kajamtag_setUtf16(0);
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
    {
        ID3 = 1;
        isID3 = 1;
    }
    
    return ID3;
}

int k_isOgg(char* id)
{
    int ogg = 0;
    if(strncmp(id, "OggS", 4) == 0)
    {
        ogg = 1;
        isXiph = 1;
    }

    return ogg;
}

int k_isFlac(char* id)
{
    int flac = 0;
    if(strncmp(id, "fLaC", 4) == 0)
    {
        flac = 1;
        isXiph = 1;
    }

    return flac;
}

/* Generic storeData function
 * Can be used by both ID3 and Ogg or anything else */
int util_storeData(char* id, char* data, tags_t tags)
{
    if(strncmp(id, tags.ids[KTITLE], strlen(tags.ids[KTITLE])) == 0)
        k_tags.title = data;
    else if(strncmp(id, tags.ids[KALBUM], strlen(tags.ids[KALBUM])) == 0)
        k_tags.album = data;
    else if(strncmp(id, tags.ids[KARTIST], strlen(tags.ids[KARTIST])) == 0)
        k_tags.artist = data;
    else if(strncmp(id, tags.ids[KGENRE], strlen(tags.ids[KGENRE])) == 0)
        k_tags.genre = data;
    else if(strncmp(id, tags.ids[KTRACK], strlen(tags.ids[KTRACK])) == 0)
        k_tags.track = atoi(data);
    else if(strncmp(id, tags.ids[KCOMPOSER], strlen(tags.ids[KCOMPOSER])) == 0)
        k_tags.composer = data;
    else
        free(data);
}

int util_storeData16(char* id, wchar_t* data, tags_t tags)
{
    kajamtag_setUtf16(1);
    
    if(strncmp(id, tags.ids[KTITLE], strlen(tags.ids[KTITLE])) == 0)
        k_tags.wtitle = data;
    else if(strncmp(id, tags.ids[KALBUM], strlen(tags.ids[KALBUM])) == 0)
        k_tags.walbum = data;
    else if(strncmp(id, tags.ids[KARTIST], strlen(tags.ids[KARTIST])) == 0)
        k_tags.wartist = data;
    else if(strncmp(id, tags.ids[KGENRE], strlen(tags.ids[KGENRE])) == 0)
        k_tags.wgenre = data;
    else if(strncmp(id, tags.ids[KCOMPOSER], strlen(tags.ids[KCOMPOSER])) == 0)
        k_tags.wcomposer = data;
    else
        free(data);
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
    
    // tried_utf8 is an infinite loop preventer
    if(data == NULL && !tried_utf8) {
        tried_utf8 = 1;
        
        //Try to get utf16 data and convert it to utf8.
        wchar_t *wdata = k_getData16(tag);
        
        //Give up if data is still null
        if(wdata == NULL)
        {
            data = "NO_DATA";
        }
        else //store it
        {
            data = convert_to_utf8(wdata);
            tags_t tags;
            if(isID3)
                tags.ids = (char**) tags_id3;
            else if(isXiph)
                tags.ids = (char**) tags_ogg;
            
            //Store the data so it can be disposed of
            //by kajamtag_close();
            util_storeData(tags.ids[tag], data, tags);
        }
    }
    
    tried_utf8 = 0;
    return data;
}

wchar_t* k_getData16(Ktag tag)
{    
    if(badTag)
        return "BAD_TAG";
    
    wchar_t* data;
    switch(tag)
    {
        case KTITLE:
            data = k_tags.wtitle;
            break;
        case KALBUM:
            data = k_tags.walbum;
            break;
        case KARTIST:
            data = k_tags.wartist;
            break;
        case KGENRE:
            data = k_tags.wgenre;
            break;
        case KCOMPOSER:
            data = k_tags.wcomposer;
        default:
            //Should never happen
            break;
    }
    
    if(data == NULL && !tried_utf16) {
        tried_utf16 = 1;
        
        //Try to get utf16 data and convert it to utf8.
        char *data = k_getData(tag);
        
        //Give up if data is still null
        if(data == NULL)
        {
            data = "NO_DATA";
        }
        else //store it
        {
            data = convert_to_utf16(data);
            tags_t tags;
            if(isID3)
                tags.ids = (char**) tags_id3;
            else if(isXiph)
                tags.ids = (char**) tags_ogg;
            
            //Store the data so it can be disposed of
            //by kajamtag_close();
            util_storeData16(tags.ids[tag], data, tags);
        }
    }
    
    tried_utf16 = 0;
    return data;
}

int k_getTrack()
{
    if(badTag)
        return 0;
    
    return k_tags.track;
}

char* k_getTitle()
{
    return k_getData(KTITLE);
}

char* k_getArtist()
{   
    return k_getData(KARTIST);
}

char* k_getAlbum()
{
    return k_getData(KALBUM);
}

char* k_getComposer()
{
    return k_getData(KCOMPOSER);
}

wchar_t* k_getTitle16()
{
    return k_getData16(KTITLE);
}

wchar_t* k_getArtist16()
{   
    return k_getData16(KARTIST);
}

wchar_t* k_getAlbum16()
{
    return k_getData16(KALBUM);
}

wchar_t* k_getComposer16()
{
    return k_getData16(KCOMPOSER);
}
