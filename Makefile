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
SRCS = src/kajamtag.c src/id3.c
HDRS = src/kajamtag.h src/id3.h
OBJS = build/kajamtag.o build/id3.o

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

clean:
	rm -f bin/* build/* 

install:
	cp bin/libkajamtag.so /usr/lib
	cp src/kajamtag.h /usr/include

