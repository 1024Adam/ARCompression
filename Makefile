CFLAGS = -ansi -Wall
LFLAGS = -lm
CC = gcc
HUFF_DIR = src/huffman
HUFF_OUT = arc
UNAME_S := $(shell uname -s)

all: arcomp

arcomp: src/huffman/charCounts.c src/huffman/charCounts.h src/huffman/encodingTree.c src/huffman/encodingTree.h src/huffman/huffman.c src/huffman/huffman.h
	$(CC) $(CFLAGS) $(HUFF_DIR)/charCounts.c $(HUFF_DIR)/encodingTree.c $(HUFF_DIR)/huffman.c $(HUFF_DIR)/testMain.c $(LFLAGS) -o $(HUFF_OUT)

clean:
	rm $(HUFF_OUT) 

alias:
	if [ "$(UNAME_S)" = "Linux" ]; \
        then \
	    printf "%s%s%s" "alias arc='" $(PWD) "/bin/huffman/arc'" >> ~/.bashrc;\
	else\
	    printf "%s%s%s" "alias arc='" $(PWD) "/bin/huffman/arc'" >> ~/.bash_profile;\
	fi
