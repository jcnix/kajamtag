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

#ifndef _KTAG_CONSTANTS_H
#define _KTAG_CONSTANTS_H

typedef enum {
    KTITLE,
    KALBUM,
    KARTIST,
    KGENRE,
    KTRACK,
    KCOMPOSER
} Ktag;

struct Tags
{
    //Pointer to an array of strings.
    char** ids;
};

typedef struct Tags tags_t;

static const char* tags_id3[] = {
    "TIT2",
    "TALB",
    "TPE1",
    "TCON",
    "TRCK",
    "TCOM"
};

//ID3 v2.2 tags.
//They only use 3 chars instead of 4.
static const char* tags_id3_v2_2[] = {
    "TT2",
    "TAL",
    "TP1",
    "TCO",
    "TRK",
    "TCM"
};

static const char* tags_ogg[] = {
    "TITLE",
    "ALBUM",
    "ALBUM ARTIST",
    "GENRE",
    "TRACKNUMBER",
    "COMPOSER"
};

#endif

#ifdef __cplusplus
}
#endif
