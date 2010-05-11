/*
 * File:   ktag_id316.c
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
 * This is where all the utf-16 functions for id3 are
 */

#include "kajamtag/ktag_id3.h"

int id3_isUTF16(FILE* f)
{
    int utf;
    size_t bytes = fread(&utf, 2, 1, f);
    
    if(utf == 0xfeff)
    {
        //return to original position
        fseek(f, -2, SEEK_CUR);
        return 1;
    }
    else
    {
        fseek(f, -2, SEEK_CUR);
        return 0;
    }
}

//TODO
int id3_write16(FILE* f, Ktag tag, wchar_t* data)
{
    return KTAG_OKAY;
}

//This function reads a full frame with a UTF-16 data string
int id3_readFullFrame16(FILE* f, int version, char **id, int *size,
                      int *flags, wchar_t **data)
{
    *id = id3_readID(f);
    
    *size = id3_readSize(f, version);

    //Blank header, probably done reading
    if(*size <= 0 || *size >= 32000) // ~32kb
        return ILLEGAL_SIZE;
    
    *flags = id3_readFlags(f);
    fseek(f, 1, SEEK_CUR); //skip an unused byte
    
    if(!id3_isUTF16(f))
    {
        fseek(f, -11, SEEK_CUR);
        return IS_UTF8;
    }
    
    *data = id3_readData16(f, *size);
    if(data == NULL)
        return 0;
        
    return KTAG_OKAY;
}

wchar_t* id3_readData16(FILE *f, int size)
{
    //We don't want to reread the two byte UTF16 identifier
    fseek(f, 2, SEEK_CUR);
    size -= 2;

    // (On GNU) 4 bytes * size/2 characters
    // size is the number of bytes the data in the frame
    // 2 is the number of bytes per char in the frame
    wchar_t* data = malloc(sizeof(wint_t) * size/2);
    if(data == NULL)
        return NULL;
    
    //TODO: Figure out why this doesn't work.
    //fread(data, 2, size/2, f);
    
    int i;
    for(i = 0; i < size/2; i++)
    {
        wint_t c = 0x0;
        fread(&c, 2, 1, f);
        data[i] = c;
    }
    
    *(data + (size/2)) = '\0';
    return data;
}

//TODO
int id3_writeData16(FILE* f, wchar_t* data)
{
    return KTAG_OKAY;
}
