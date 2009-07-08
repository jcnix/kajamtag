/*
 * File:   testprogram.c
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

#include <stdio.h>
#include <kajamtag/kajamtag.h>

int main()
{
    kajamtag_init("test.mp3");
    char* title = getTitle();
    char* album = getAlbum();
    char* artist = getArtist();
    
    printf("Title: %s\n", title);
    printf("Album: %s\n", album);
    printf("Artist: %s\n", artist);
    
    return 1;
}
