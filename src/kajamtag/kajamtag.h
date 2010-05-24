/*
 * File:   kajamtag.h
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

#ifndef _KAJAMTAG_H
#define _KAJAMTAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "ktag_id3.h"
#include "ktag_ogg.h"
#include "ktag_flac.h"
#include "ktag_util.h"
#include "ktag_constants.h"

struct kajamtag 
{
    char* title;
    char* album;
    char* artist;
    char* genre;
    int track;
    char* composer;
    
    wchar_t* wtitle;
    wchar_t* walbum;
    wchar_t* wartist;
    wchar_t* wgenre;
    wchar_t* wcomposer;
};

typedef struct kajamtag kajamtag_t;
kajamtag_t k_tags;

int isUtf16;
int badTag;

int kajamtag_read(char*);
int kajamtag_write(char*, Ktag, char*);
int kajamtag_isUtf16();
void kajamtag_setUtf16(int i);

/* Frees all the memory storing the data.
 * Should be run when done retrieving all
 * the needed data from the tag */
int kajamtag_close();

char* k_getData(Ktag);
wchar_t* k_getData16(Ktag);

int k_getTrack();
char* k_getTitle();
char* k_getArtist();
char* k_getAlbum();
char* k_getComposer();

wchar_t* k_getTitle16();
wchar_t* k_getArtist16();
wchar_t* k_getAlbum16();
wchar_t* k_getComposer16();

#ifdef __cplusplus
}
#endif

#endif
