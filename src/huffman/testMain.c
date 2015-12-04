/* testMain.c */

/*
 * Adam Reid
 * December 3, 2015
 */

#include <stdio.h>
#include "huffman.h"

int main()
{
    CharCounts * counts;
    int length;

    counts = getCharCounts("test.txt");
    length = 0;

    printCounts(counts);
    length = getLength(counts);
    printf("\nLength: %d\n\n", length);

    counts = sortCounts(counts);

    printCounts(counts);
    length = getLength(counts);
    printf("\nLength: %d\n\n", length);
    return(0);
}
