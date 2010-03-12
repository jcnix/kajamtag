/*
 * File:   ktag_id3.h
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

/*
 * Kajamtag ID3 tag reader
 */

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ID3_H
#define _ID3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>

#include "kajamtag.h"
#include "ktag_constants.h"
#include "ktag_util.h"

#define TAG_TO_INT(tag) ((tag)&0x7f) | (((tag)&0x7f00)>>1) | (((tag)&0x7f0000)>>2) | (((tag)&0x7f000000)>>3)

//Error codes
#define KTAG_OKAY 1
#define ILLEGAL_SIZE 2
#define IS_UTF16 3
#define IS_UTF8 4

int id3_read(FILE*, tags_t tags);
int id3_header(FILE*);
int id3_frame(FILE*, int, tags_t);
int id3_write(FILE*, Ktag, char*);
int id3_storeData(char*, char*, tags_t);
int id3_getFlag(int, int);

int id3_readFullFrame(FILE*, int, char**, int*, int*, char**);
char* id3_readID(FILE*);
int id3_readSize(FILE*, int);
int id3_readFlags(FILE*);
char* id3_readData(FILE*, int);
char* id3_readData_UTF16(FILE*, int);
int id3_isUTF16(FILE*);
int id3_writeSize(FILE*, int, int);
int id3_writeData(FILE*, char*);

#endif

#ifdef __cplusplus
}
#endif
