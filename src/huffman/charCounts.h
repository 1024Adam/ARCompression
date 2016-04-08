/* charCounts.h */

/*
 * Adam Reid
 * December 28, 2015
 */

#ifndef CHAR_COUNTS
#define CHAR_COUNTS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct CharCounts
{
    unsigned char letter;
    int count;
    struct CharCounts * next; 
    struct CharCounts * prev;
}
CharCounts;

CharCounts * getCharCounts(char * fileToOpen);
int isCounted(CharCounts * root, unsigned char letter);
CharCounts * createCount(unsigned char letter);
CharCounts * addChar(CharCounts * root, unsigned char toAdd);
CharCounts * addCount(CharCounts * root, unsigned char letter);
void printCounts(CharCounts * root);
CharCounts * sortCounts(CharCounts * root);
int getLength(CharCounts * root);
CharCounts * removeFront(CharCounts * root);
int getLetterCount(CharCounts * counts, unsigned char letter);
CharCounts * freeCounts(CharCounts * counts);

#endif
