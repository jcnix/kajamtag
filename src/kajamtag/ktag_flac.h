/*
 * File:   ktag_flac.h
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
 * Kajamtag Flac tag reader
 *
 * Is similar enough to Ogg that it will use some
 * functions from ktag_ogg.
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _FLAC_H
#define _FLAC_H

#include <stdio.h>
#include <stdlib.h>

#include "kajamtag.h"
#include "ktag_ogg.h"

int flac_read(FILE*, tags_t);
int flac_read_to_comments(FILE*);
int flac_read_comments(FILE*, tags_t, int);

#endif

#ifdef __cplusplus
}
#endif

