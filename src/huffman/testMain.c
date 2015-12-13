/* testMain.c */

/*
 * Adam Reid
 * December 13, 2015
 */

#include <stdio.h>
#include "huffman.h"

int main()
{
    CharCounts * counts;
    EncodingTree * tree;
    int length;
    char * encoding;

    counts = getCharCounts("test.txt");
    length = 0;

    /*printCounts(counts);*/
    length = getLength(counts);
    /*printf("\nLength: %d\n\n", length);*/
    counts = sortCounts(counts);
    /*printCounts(counts);*/
    length = getLength(counts);
    /*printf("\nLength: %d\n\n", length);*/

    tree = createTree(counts);
    /*printTree(tree);
    printf("End of Tree\n");*/
    /*printCounts(counts);*/

    encoding = getBinaryCode(tree, counts, "test.txt");
    printf("%s\n", encoding);

    counts = freeCounts(counts);
    tree = freeTree(tree);
    free(encoding);
    encoding = NULL;

    if(counts == NULL && tree == NULL && encoding == NULL)
    {
        printf("All done\n");
    }
    else
    {
        printf("Trouble freeing\n");
    }

    return(0);
}
