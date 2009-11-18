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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KAJAMTAG_H
#define _KAJAMTAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ktagid3.h"
#include "ktagogg.h"
#include "ktag_constants.h"

typedef enum {
    KTITLE,
    KALBUM,
    KARTIST,
    KGENRE,
} Ktag;

struct kajamtag 
{
    char* title;
    char* album;
    char* artist;
    char* genre;
    int track;
};

typedef struct kajamtag kajamtag_t;
kajamtag_t k_tags;

int badTag;

int kajamtag_read(char*);
int kajamtag_write(char*, Ktag, char*);
char* k_getData(Ktag);
char* k_getTitle();
char* k_getArtist();
char* k_getAlbum();
int k_getTrack();

#endif

#ifdef __cplusplus
}
#endif
