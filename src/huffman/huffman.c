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
        newCount->prev = temp;
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
    newCount->prev = NULL;

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

CharCounts * sortCounts(CharCounts * root)
{
    CharCounts * temp;
    CharCounts * swap;
    int done;

    temp = root;
    done = 0;

    while(done == 0)
    {
        done = 1;
        temp = root;
        while(temp != NULL && temp->next != NULL)
        {
            if(temp->count > temp->next->count)
            {
                /* swap */
                /*printf("Start\n");*/
                /*printf("Letter 1: %c %d\n", temp->letter, temp->count);*/
                /*printf("Letter 2: %c %d\n", temp->next->letter, temp->next->count);*/
                done = 0;
                swap = temp->next;
                temp->next = temp->next->next;
                if(temp->next != NULL)
                {
                    temp->next->prev = temp;
                }

                swap->next = temp;
                swap->prev = temp->prev;
                if(swap->prev != NULL)
                {
                    swap->prev->next = swap;
                }
                
                temp->prev = swap;
                
                if(swap->prev == NULL)
                {
                    root = swap;
                }
                /*printf("Letter 1: %c %d\n", temp->prev->letter, temp->prev->count);*/
                /*printf("Letter 2: %c %d\n", temp->letter, temp->count);*/
            }
            else
            {
                temp = temp->next;
            }
        }
    }

    return(root);
}

int getLength(CharCounts * root)
{
    CharCounts * temp;
    int length;

    temp = root;
    length = 0;

    while(temp != NULL)
    {
        length++;
        temp = temp->next;
    }

    return(length);
}
