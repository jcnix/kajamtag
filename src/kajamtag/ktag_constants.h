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

typedef enum {
    KTITLE,
    KALBUM,
    KARTIST,
    KGENRE,
} Ktag;

struct Tags
{
    //Pointer to an array of strings.
    char*** tags;
};

static const char* id3tags[] = {
    "TIT2",
    "TALB",
    "TPE1",
    "TCON"
};

//ID3 v2.2 tags.
//They only use 3 chars instead of 4.
static const char* id3_v2_2_tags[] = {
    "TT2",
    "TAL",
    "TP1",
    "TCO"
};

static const char* oggtags[] = {
    "TITLE",
    "ALBUM",
    "ALBUM ARTIST",
    "GENRE"
};
