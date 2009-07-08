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
INCLUDE_DIR = /usr/include/kajamtag
TARGET = bin/libkajamtag.so
SRCS = src/kajamtag.c src/id3.c src/ogg.c
HDRS = src/kajamtag.h src/id3.h src/ogg.h
OBJS = build/kajamtag.o build/id3.o build/ogg.o

all: $(SRCS) $(OBJS) $(TARGET) 

$(TARGET): $(OBJS) $(BIN_DIR)
	$(CC) -shared -o $(TARGET) $(OBJS)	

$(OBJS): $(SRCS) $(HDRS) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS)
	mv *.o $(BUILD_DIR)

$(BUILD_DIR)/:
	mkdir -p $@

$(BIN_DIR)/:
	mkdir -p $@

$(INCLUDE_DIR)/:
	mkdir -p $@

clean:
	rm -f bin/* build/* 

install: $(INCLUDE_DIR)
	cp bin/libkajamtag.so /usr/lib
	cp src/kajamtag.h $(INCLUDE_DIR)
	cp src/id3.h $(INCLUDE_DIR)
	cp src/ogg.h $(INCLUDE_DIR)
    
