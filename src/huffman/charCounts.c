/* charCounts.c */

/*
 * Adam Reid
 * December 17, 2015
 */

#include "charCounts.h"

/* 
 * getCharCounts
 * Function: Read file, and record the count of each character into a CharCounts variable
 * Parameters: The string literal of the file you wish to read
 * Return: The counts of every character in the file
 */ 
CharCounts * getCharCounts(char * fileToOpen)
{
    FILE * file;
    char letter;
    CharCounts * counts;

    file = fopen(fileToOpen, "r");
    if(file == NULL)
    {
        printf("Error: file could not be found\n");
        exit(0);
    }
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
                /* Character is not counted yet */
                counts = addChar(counts, letter);
            }
            else
            {
                /* Character has been counted before */
                counts = addCount(counts, letter);
            }
        }
    }
    while(letter != EOF);

    fclose(file);

    return(counts);
}

/*
 * isCounted
 * Function: Identify whether the character has been counted before or not
 * Parameters: The list of characters counted; The character in question
 * Return: 1 - The character has been counted already
 *         0 - The character has not been counted yet
 */
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

/* 
 * createCount
 * Function: Create a new CharCount variable with the new letter 
 * Parameters: The letter to create the count from
 * Return: The new CharCount variable 
 */
CharCounts * createCount(char letter)
{
    CharCounts * newCount;
    newCount = malloc(sizeof(CharCounts));
    if(newCount == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    newCount->letter = letter;
    newCount->count = 1;
    newCount->next = NULL;
    newCount->prev = NULL;

    return(newCount);
}

/*
 * addChar
 * Function: Add a new CharCount to the current list
 * Parameters: The current list of CharCounts; The CharCount to add
 * Return: The new updated list of CharCounts 
 */
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

/*
 * addCount
 * Function: Increment the count of a current CharCount
 * Parameters: The list of CharCounts; The letter of the CharCount to increment the count for
 * Return: The new updated list of CharCounts
 */
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

/*
 * printCounts
 * Function: Print out the current list of CharCounts
 * Parameters: The current list of CharCounts
 * Return: void
 */
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

/*
 * sortCounts
 * Function: Sort the current list of CharCounts from least to greatest count
 * Parameters: The current list of CharCounts
 * Return: The sorted list of CharCounts
 */
CharCounts * sortCounts(CharCounts * root)
{
    CharCounts * temp;
    CharCounts * swap;
    int done;

    temp = root;
    done = 0;

    while(done == 0) /* if done is zero, then there was a swap performed on the last pass */
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

/*
 * getLength
 * Function: Get the current number of CharCounts in the list
 * Parameters: The list of CharCounts
 * Return: The number of CharCounts in the list 
 */
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

/*
 * removeFront
 * Function: Removes and frees the first CharCount in the list
 * Parameters: The current list of CharCounts
 * Return: The new list of CharCounts with the first removed
 */
CharCounts * removeFront(CharCounts * root)
{
    CharCounts * toRemove;

    toRemove = root;
    root = root->next;

    free(toRemove);
    return(root);
}

/*
 * getLetterCount
 * Function: Get the current character count of the character given
 * Parameters: The list of CharCounts; The character in question
 * Return: The character count of the character given
 */
int getLetterCount(CharCounts * counts, char letter)
{
    int letterCount;
    CharCounts * temp;

    letterCount = 0;
    temp = counts;

    /* find the letter passed */
    while(temp != NULL && temp->letter != letter)
    {
        temp = temp->next;
    }

    if(temp->letter == letter)
    {
        return(temp->count);
    }
    else
    {
        return(0);
    }   
}

/* 
 * freeCounts
 * Function: Remove and free all of the CharCounts in the list of CharCounts
 * Parameters: The list of CharCounts
 * Return: NULL
 */
CharCounts * freeCounts(CharCounts * counts)
{
    while(counts != NULL)
    {
        counts = removeFront(counts);
    }
    return(NULL);
}
