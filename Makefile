##############################################################################
# Makefile for building bin/kajamtag
#
# Author: Casey Jones
##############################################################################

CC = gcc
LD = gcc
CFLAGS = -c -Wall -fpic
LDFLAGS = -lm
BUILD_DIR = build/
BIN_DIR = bin/
TARGET = bin/libkajamtag.so
SRCS = src/kajamtag.c
OBJS = build/kajamtag.o

all: $(SRCS) $(OBJS) $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) -shared -o $(TARGET) $(OBJS)	

build/kajamtag.o: src/kajamtag.c src/kajamtag.h
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS)

clean:
	rm -f bin/* build/* 

install:
	cp bin/libkajamtag.so /lib
	cp src/kajamtag.h /usr/include

