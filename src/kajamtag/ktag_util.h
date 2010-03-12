/*
 * File:   kajamtagutility.h
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

//Utility functions that kajamtag will use internally
//Not needed in the public API.

#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include "kajamtag.h"
#include "ktag_constants.h"

int error(size_t, int);
int util_storeData(char*, char*, tags_t);

//Safely free() char*s
void sfree(char*);

#endif
