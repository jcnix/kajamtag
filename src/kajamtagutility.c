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

#include "kajamtagutility.h"

/* Used after freads and fwrites
 * If the real number of bytes read doesn't match how many
 * bytes should have been read return false */
//TODO: return something more fatal than 0 or 1
// stop execution perhaps?
int error(size_t real, int desired)
{
    if(real == desired)
        return 1;
    else
        return 0;
}
