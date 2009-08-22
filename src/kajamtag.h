#ifdef __cplusplus
extern "C" {
#endif

/*
 * File:   kajamtag.h
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

#ifndef _KAJAMTAG_H
#define _KAJAMTAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kajamtagid3.h"
#include "kajamtagogg.h"

enum Tag {
    TITLE,
    ALBUM,
    ARTIST,
    GENRE,
};

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

int kajamtag_init(char*);

char* k_getTag(Tag);
int k_getTrack();

#endif

#ifdef __cplusplus
}
#endif
