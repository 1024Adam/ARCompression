CFLAGS = -ansi -Wall

all: arcomp arcgui jnihead jni

arcomp: src/huffman/charCounts.c src/huffman/charCounts.h src/huffman/encodingTree.c src/huffman/encodingTree.h src/huffman/huffman.c src/huffman/huffman.h
	gcc $(CFLAGS) src/huffman/charCounts.c src/huffman/encodingTree.c src/huffman/huffman.c src/huffman/testMain.c -o bin/huffman/test
 
