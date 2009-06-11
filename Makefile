##############################################################################
# Makefile for building bin/kajamtag
#
# Author: Casey Jones
##############################################################################

CC = gcc
LD = ld
CFLAGS = -Wall -fpic
LDFLAGS = -lm
BUILD_DIR = build/
BIN_DIR = bin/
TARGET = bin/libkajamtag.so
OBJS = kajamtag.o

prog1: $(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)

kajamtag.o:
	$(CC) -c $(CFLAGS) src/kajamtag.c

clean:
	rm -f bin/* build/* kajamtag.o

install:
	cp bin/libkajamtag.so /lib
	cp src/kajamtag.h /usr/include

