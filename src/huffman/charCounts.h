/* charCounts.h */

/*
 * Adam Reid
 * December 15, 2015
 */

#ifndef CHAR_COUNTS
#define CHAR_COUNTS

#include "arCompress.h"

typedef struct CharCounts
{
    char letter;
    int count;
    struct CharCounts * next; 
    struct CharCounts * prev;
}
CharCounts;

CharCounts * getCharCounts(char * fileToOpen);
int isCounted(CharCounts * root, char letter);
CharCounts * createCount(char  letter);
CharCounts * addChar(CharCounts * root, char toAdd);
CharCounts * addCount(CharCounts * root, char letter);
void printCounts(CharCounts * root);
CharCounts * sortCounts(CharCounts * root);
int getLength(CharCounts * root);
CharCounts * removeFront(CharCounts * root);
int getLetterCount(CharCounts * counts, char letter);
CharCounts * freeCounts(CharCounts * counts);

#endif
