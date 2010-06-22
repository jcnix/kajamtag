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

/*
 * Converts a wchar_t* to a char*
 * This is only done if the data cannot be found,
 * so it will check the stored utf16 data
 */
char* convert_to_utf8(wchar_t *str)
{
    int size = wcslen(str);
    char* new_str = malloc(size + 1);
    int i;
    
    for(i = 0; i < size; i++)
    {
        char c = (char) *(str + i);
        *(new_str + i) = c;
    }
    
    *(new_str + size) = 0x0;
    return new_str;
}

wchar_t* convert_to_utf16(char *str)
{
    int size = strlen(str);
    wchar_t* new_str = malloc(sizeof(wint_t) * size/2 + 1);
    int i;
    
    for(i = 0; i < size; i++)
    {
        wint_t c = (wint_t) *(str + i);
        *(new_str + i) = c;
    }
    
    *(new_str + size) = 0x0;
    return new_str;
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
