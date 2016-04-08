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
#include <math.h>
#include "charCounts.h"
#include "encodingTree.h"

char * getBinaryCode(EncodingTree * root, char * fileToOpen);
char * getLetterCode(SearchTree * root, int letterNum);
int isLetterInTree(EncodingTree * tree, char letter);

int encode(char * rFileName);
int writeToFile(char * wFileName, char * string, EncodingTree * tree);
void filePrintTree(FILE * wFile, EncodingTree * tree);
char * getSubstring(char * string, int start, int end);

int decode(char * rFileName);
char * getDecodeFileName(char * rFileName);
char * getEncodedBinary(char * rFileName);
char * getBinary(unsigned char letter);
int decodeToFile(char * wFileName, char * string, EncodingTree * tree);

#endif
