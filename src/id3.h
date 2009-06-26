/*
 * Kajamtag ID3 tag reader
 */

#ifndef _ID3_H
#define _ID3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include "kajamtag.h"

#define TAG_TO_INT(tag) ((tag) &0x7f) | (((tag) &0x7f00) >> 1) | (((tag)&0x7f0000)>>2) | (((tag)&0x7f000000)>>3)

int findHeader(FILE*);
int getFrameHeader(FILE*, int);
int storeData(char*, char*, int);
int getFlag(int, int);

#endif