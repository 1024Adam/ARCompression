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
    counts = getCharCounts("test.txt");

    printCounts(counts);

    return(0);
}
