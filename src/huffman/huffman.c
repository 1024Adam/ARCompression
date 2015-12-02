/* huffman.c */

/*
 * Adam Ried
 * December 1, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CharCounts * getCharCounts(char * fileToOpen)
{
    FILE * file;
    char letter;
    CharCounts * counts; 

    file = fopen(fileToOpen, "r");
    letter = '\0';
    counts = NULL;

    do
    {
        letter = fgetc(file);
        if(isCounted(counts, letter) == 0)
        {
            counts = addChar(counts, letter);
        }
        else
        {
            counts = addCount(counts, letter);
        }
    }
    while(letter != 'EOF');

    fclose(file);
}

