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

const char* id3tags[] = {
    "TIT2",
    "TALB",
    "TPE1",
    "TCON"
};

const char* oggtags[] = {
    "TITLE",
    "ALBUM",
    "ALBMUM ARTIST",
    "GENRE"
};

typedef struct kajamtag kajamtag_t;
kajamtag_t k_tags;

int kajamtag_read(char*);
char* k_getTag(Ktag);
int k_getTrack();
void k_write(char*, Ktag, char*);

#endif

#ifdef __cplusplus
}
#endif
