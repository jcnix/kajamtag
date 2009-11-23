/*
 * File:   kajamtagutility.c
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

#include "kajamtag/ktagutil.h"

/* Used after freads and fwrites
 * If the real number of bytes read doesn't match how many
 * bytes should have been read return false */
int fread_error(size_t real, int desired)
{
    if(real == desired)
        return 1;
    else
        return 0;
}

/* Generic storeData function
 * Can be used by both ID3 and Ogg or anything else */
int util_storeData(char* identifier, char* data, tags_t tags)
{
    if(strcmp(identifier, tags.ids[KTITLE]) == 0)
        k_tags.title = data;
    else if(strcmp(identifier, tags.ids[KALBUM]) == 0)
        k_tags.album = data;
    else if(strcmp(identifier, tags.ids[KARTIST]) == 0)
        k_tags.artist = data;
    else if(strcmp(identifier, tags.ids[KGENRE]) == 0)
        k_tags.genre = data;
    else if(strcmp(identifier, tags.ids[KTRACK]) == 0)
        k_tags.track = atoi(data);
    else if(strcmp(identifier, tags.ids[KCOMPOSER]) == 0)
        k_tags.composer = data;
}
