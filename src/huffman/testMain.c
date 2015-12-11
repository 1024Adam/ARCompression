/* testMain.c */

/*
 * Adam Reid
 * December 10, 2015
 */

#include <stdio.h>
#include "huffman.h"

int main()
{
    CharCounts * counts;
    EncodingTree * tree;
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

    tree = createTree(counts);
    printTree(tree);

    return(0);
}
