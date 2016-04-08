CFLAGS = -ansi -Wall
CC = gcc
HUFF_DIR = src/huffman
HUFF_OUT = bin/huffman

all: arcomp

arcomp: src/huffman/charCounts.c src/huffman/charCounts.h src/huffman/encodingTree.c src/huffman/encodingTree.h src/huffman/huffman.c src/huffman/huffman.h
	$(CC) $(CFLAGS) $(HUFF_DIR)/charCounts.c $(HUFF_DIR)/encodingTree.c $(HUFF_DIR)/huffman.c $(HUFF_DIR)/testMain.c -o $(HUFF_OUT)/arc

clean:
	rm $(HUFF_OUT)/arc 
