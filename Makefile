##############################################################################
# Makefile for building bin/kajamtag
#
# Author: Casey Jones
##############################################################################

CC = gcc
LD = gcc
CFLAGS = -c -Wall -fpic
LDFLAGS = -lm
BUILD_DIR = build
BIN_DIR = bin
TARGET = bin/libkajamtag.so
SRCS = src/kajamtag.c
OBJS = build/kajamtag.o

all: $(SRCS) $(OBJS) $(TARGET) 

$(TARGET): $(OBJS) $(BIN_DIR)
	$(CC) -shared -o $(TARGET) $(OBJS)	

build/kajamtag.o: src/kajamtag.c src/kajamtag.h $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS)

$(BUILD_DIR)/:
	mkdir -p $@

$(BIN_DIR)/:
	mkdir -p $@

clean:
	rm -f bin/* build/* 

install:
	cp bin/libkajamtag.so /usr/lib
	cp src/kajamtag.h /usr/include

