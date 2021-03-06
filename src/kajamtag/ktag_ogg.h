/*
 * File:   ktag_gogg.h
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
 * Kajamtag Ogg tag reader
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _OGG_H
#define _OGG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "kajamtag.h"
#include "ktag_constants.h"
#include "ktag_util.h"

#define INIT_SIZE 100*sizeof(char)

int ogg_read(FILE* f, tags_t tags);
char* ogg_storeData(char* data, tags_t tags);
int ogg_write(FILE* f, Ktag tag, char* data);

/* Skips the useless data, and gets right to the Comments
 * returns number of comments */
int ogg_read_header(FILE* f);
/* Reads until a tag, and stops
 * returns position */
int ogg_read_comments_to(FILE*, tags_t, Ktag, int num);
/* Reads through the Xiph comment and stores all the data */
int ogg_readComments(FILE* f, tags_t tags, int size);

int ogg_readComment(FILE*, char**);
int ogg_readSize(FILE*);
int ogg_readCommentSize(FILE*);
char* ogg_readData(FILE*, int);

#endif

#ifdef __cplusplus
}
#endif
