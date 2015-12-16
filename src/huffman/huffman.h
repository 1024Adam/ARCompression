/* huffman.h */

/*
 * Adam Reid
 * December 15, 2015
 */

#ifndef HUFFMAN
#define HUFFMAN

#include "arCompress.h"

char * getBinaryCode(EncodingTree * root, CharCounts * counts, char * fileToOpen);
char * getLetterCode(EncodingTree * root, char letter, char * currentCode, int currentLength);
int isLetterInTree(EncodingTree * tree, char letter);
char convertASCIICode(char * binString);

int encode(char * rFileName);
int writeToFile(char * wFileName, char * string);
char * getSubstring(char * string, int start, int end);

#endif
