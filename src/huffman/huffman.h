/* huffman.h */

/*
 * Adam Reid
 * December 30, 2015
 */

#ifndef HUFFMAN
#define HUFFMAN

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charCounts.h"
#include "encodingTree.h"

char * getBinaryCode(EncodingTree * root, char * fileToOpen);
char * getLetterCode(SearchTree * root, int letterNum);
int isLetterInTree(EncodingTree * tree, char letter);
char convertASCIICode(char * binString);

int encode(char * rFileName);
int writeToFile(char * wFileName, char * string, EncodingTree * tree);
void filePrintTree(FILE * wFile, EncodingTree * tree);
char * getSubstring(char * string, int start, int end);

int decode(char * rFileName);
char * getDecodeFileName(char * rFileName);

#endif
