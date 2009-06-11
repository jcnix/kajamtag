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

#include <stdio.h>
#include <stdlib.h>
#include <endian.h>

#define TAG_TO_INT(tag) ((tag) &0x7f) | (((tag) &0x7f00) >> 1) | (((tag)&0x7f0000)>>2) | (((tag)&0x7f000000)>>3)

int kajamtag_init(char*);
int findHeader(FILE*);
int getFrameHeader(FILE*);

typedef struct kajamtags 
{
    char* title;
    char* album;
    char* artist;
    char* track;
} tags;
