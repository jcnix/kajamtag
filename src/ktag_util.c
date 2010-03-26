/*
 * File:   ktag_util.c
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

#include "kajamtag/ktag_util.h"

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
int util_storeData(char* id, char* data, tags_t tags)
{
    //Use strlen(tags.ids[]) instead of a literal because
    //ID3 2.4 and 2.3 use 4 chars, but 2.2 uses 3.
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
    isUtf16 = 1;
    
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

void sfree(char* buffer)
{
    if(buffer != NULL)
    {
        free(buffer);
    }
}

//Convert string to upper case
char* strup(char* in)
{
    char c;
    int i;
    
    for(i = 0; i < strlen(in); i++)
    {
        c = in[i];
        if(islower(c))
            c = toupper(c);
        in[i] = c;
    }
    
    return in;
}
