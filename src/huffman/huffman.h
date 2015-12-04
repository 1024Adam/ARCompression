/* huffman.h */

/*
 * Adam Reid
 * December 3, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct CharCounts
{
    char letter;
    int count;
    struct CharCounts * next; 
    struct CharCounts * prev;
}
CharCounts;

typedef struct EncodingTree
{
    char letter;
    int count;
    struct EncodingTree * next; 
}
EncodingTree;

CharCounts * getCharCounts(char * fileToOpen);
int isCounted(CharCounts * root, char letter);
CharCounts * createCount(char  letter);
CharCounts * addChar(CharCounts * root, char toAdd);
CharCounts * removeChar(CharCounts * root, char toRemove);
CharCounts * addCount(CharCounts * root, char letter);
void printCounts(CharCounts * root);
CharCounts * sortCounts(CharCounts * root);
int getLength(CharCounts * root);

EncodingTree * createTree(CharCounts * counts);
EncodingTree * addToTree(EncodingTree * root, char toAdd, int letterCount); 
