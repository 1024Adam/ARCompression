/* huffman.c */

/*
 * Adam Ried
 * December 3, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

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
        if(letter != EOF)
        {
            /*printf("Letter: %c\n", letter);*/

            if(isCounted(counts, letter) == 0)
            {
                counts = addChar(counts, letter);
            }
            else
            {
                counts = addCount(counts, letter);
            }
        }
    }
    while(letter != EOF);

    fclose(file);

    return(counts);
}

int isCounted(CharCounts * root, char letter)
{
    CharCounts * temp;
    temp = root;

    while(temp != NULL && temp->letter != letter)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return(0);
    }
    else
    {
        return(1);
    }
}

CharCounts * addChar(CharCounts * root, char toAdd)
{
    CharCounts * temp;
    CharCounts * newCount;

    temp = root;
    newCount = createCount(toAdd);

    if(temp == NULL)
    {
        return(newCount);
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newCount;

        return(root);
    }
}

CharCounts * addCount(CharCounts * root, char letter)
{
    CharCounts * temp;
    temp = root;

    if(temp == NULL)
    {
        return(NULL);
    }
    else
    {
        while(temp->letter != letter)
        {
            temp = temp->next;
        }
        temp->count++;

        return(root);
    }
}

CharCounts * createCount(char letter)
{
    CharCounts * newCount;
    newCount = malloc(sizeof(CharCounts));

    newCount->letter = letter;
    newCount->count = 1;
    newCount->next = NULL;

    return(newCount);
}

void printCounts(CharCounts * root)
{
    CharCounts * temp;
    temp = root;

    while(temp != NULL)
    {
        printf("%c %d\n", temp->letter, temp->count);
        temp = temp->next;
    }
}
