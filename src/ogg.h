/*
 * File:   ogg.h
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

/*
 * Kajamtag Ogg tag reader
 */

#ifndef _OGG_H
#define _OGG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kajamtag.h"

#define INIT_SIZE 50*sizeof(char)

int ogg_read(FILE*);
int ogg_storeData(char*);

#endif

