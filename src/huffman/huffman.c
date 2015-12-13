/* huffman.c */

/*
 * Adam Ried
 * December 13, 2015
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

CharCounts * removeFront(CharCounts * root)
{
    CharCounts * toRemove;

    toRemove = root;
    root = root->next;

    free(toRemove);
    return(root);
}

int getLetterCount(CharCounts * counts, char letter)
{
    int letterCount;
    CharCounts * temp;

    letterCount = 0;
    temp = counts;

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

CharCounts * freeCounts(CharCounts * counts)
{
    while(counts != NULL)
    {
        counts = removeFront(counts);
    }
    return(NULL);
}

EncodingTree * createTree(CharCounts * counts)
{
    EncodingTree * root;
    TreeQueue * queue;
    TreeQueue * toAdd;
    EncodingTree * temp1;
    EncodingTree * temp2;
    int nodeCount;
    CharCounts * tempCount;
    
    root = NULL;
    queue = NULL;
    toAdd = NULL;
    temp1 = NULL;
    temp2 = NULL;
    nodeCount = 0;
    tempCount = NULL;

    tempCount = counts;
    while(tempCount != NULL)
    {
        toAdd = createBranch(tempCount);
        tempCount = tempCount->next;
        queue = insertInQueue(queue, toAdd);
    }  
    /*printQueue(queue);*/
    toAdd = NULL;
    while(isEmpty(queue) == 0)
    {
        /*printf("boom\n");*/        
        if(toAdd != NULL)
        {
            queue = insertInQueue(queue, toAdd);
        }
        /* Remove two from queue */
        temp1 = queue->root;
        /*printf("%c%d\n\nQueue1\n", temp1->letter, temp1->count);*/
        /*printQueue(queue);*/
        queue = queue->next;
        /*printf("Queue2\n");*/
        /*printQueue(queue);*/
        temp2 = queue->root;
        /*printf("%c%d\n\n", temp2->letter, temp2->count);*/
        queue = queue->next;
        /*printQueue(queue);*/
        temp2 = insertInTree(temp2, temp1);
        toAdd = createBranchFromTree(temp2);
    }

    root = toAdd->root;

    return(root);
}

TreeQueue * createBranch(CharCounts * count)
{
    TreeQueue * branch;

    branch = malloc(sizeof(TreeQueue));
    if(branch == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    branch->root = malloc(sizeof(EncodingTree));
    if(branch->root == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    branch->root->letter = count->letter;
    branch->root->count = count->count;
    branch->root->lChild = NULL;
    branch->root->rChild = NULL;
    branch->next = NULL;

    return(branch); 
}

TreeQueue * createBranchFromTree(EncodingTree * root)
{
    TreeQueue * branch;

    branch = malloc(sizeof(TreeQueue));
    if(branch == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    branch->root = root;
    branch->next = NULL;

    return(branch);
}

int treeNodeCount(EncodingTree * root)
{
    EncodingTree * temp;
    int nodeCount;

    temp = root;
    nodeCount = 0;
    
    if(temp == NULL)
    {
        return(nodeCount);
    }
    else
    {
        return(nodeCount + 1 + treeNodeCount(root->lChild) + treeNodeCount(root->rChild));
    }
}

EncodingTree * insertInTree(EncodingTree * root, EncodingTree * toAdd)
{
    int nodeCount;
    EncodingTree * newRoot;

    nodeCount = treeNodeCount(root);
    newRoot = malloc(sizeof(EncodingTree));
    if(newRoot == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    newRoot->letter = '\0';
    newRoot->count = root->count + toAdd->count;

    if(nodeCount == 0)
    {
        return(toAdd);
    }
    else
    {
        newRoot->lChild = toAdd;
        newRoot->rChild = root;

        return(newRoot);
    }
}

TreeQueue * insertInQueue(TreeQueue * root, TreeQueue * toAdd)
{
    TreeQueue * temp;
    temp = root;

    /*printf("ToAdd\n");
    printQueue(toAdd);*/

    while(temp != NULL && temp->next != NULL && temp->root->count < toAdd->root->count)
    {
        temp = temp->next;
    }
    
    if(root == NULL)
    {
        toAdd->next = NULL;
        /*printQueue(toAdd);*/
        return(toAdd);
    }
    else if(temp->next == NULL)
    {
        temp->next = toAdd;
        toAdd->next = NULL;
        /*printQueue(root);*/
        return(root);
    }
    else
    {
        toAdd->next = temp->next;
        temp->next = toAdd;
        /*printQueue(root);*/
        return(root);
    }
}

int isEmpty(TreeQueue * root)
{
    if(root == NULL)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

TreeQueue * removeFromQueue(TreeQueue * root)
{
    TreeQueue * temp;
    temp = root;

    root = root->next;

    free(temp);
    return(root);    
}

void printTree(EncodingTree * root)
{
    if(root != NULL)
    {
        printf("ROOT\n");
        printf("%c%d\n", root->letter, root->count);
        printf("LeftChild\n");
        printTree(root->lChild);
        printf("\n");
        printf("RightChild\n");
        printTree(root->rChild);
        printf("\n");
    }
}

void printQueue(TreeQueue * root)
{
    TreeQueue * temp;

    temp = root;
    while(temp != NULL)
    {
        printf("%c%d\n", temp->root->letter, temp->root->count);
        /*if(temp->next != NULL)
        {
            printf("Next:%c\n", temp->next->root->letter);
        }*/
        temp = temp->next;
    }
    /*printf("end\n");*/
}

EncodingTree * freeTree(EncodingTree * tree)
{
    if(tree != NULL)
    {
        if(tree->lChild != NULL)
        {
            tree->lChild = freeTree(tree->lChild);
        }
        if(tree->rChild != NULL) 
        {
            tree->rChild = freeTree(tree->rChild);
        }
        free(tree);
    }
    return(NULL);
}

char * getBinaryCode(EncodingTree * root, CharCounts * counts, char * fileToOpen)
{
    FILE * file;
    char letter;
    char * letterCode;
    char * binaryString;
    int binaryLength;

    letter = '\0';
    letterCode = NULL;
    binaryString = NULL;
    binaryLength = 0;

    file = fopen(fileToOpen, "r");
    if(file == NULL)
    {
        printf("Error: file could not be found\n");
        exit(0);
    }
    
    binaryString = malloc(sizeof(char));
    if(binaryString == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    strcpy(binaryString, "");

    do
    {
        letter = fgetc(file);
        if(letter != EOF)
        {
            /*printf("Letter: %c\n", letter);*/
            letterCode = getLetterCode(root, letter, NULL, 0);
            /*printf("LetterCode: %s\n", letterCode);*/
            binaryLength += strlen(letterCode);
            /*printf("BinaryLength: %d\n", binaryLength);*/
            binaryString = reallocf(binaryString, (sizeof(char) * (binaryLength + 1)));
            if(binaryString == NULL)
            {
                printf("Error: not enough memory\n");
                exit(0);
            }
            strcat(binaryString, letterCode);
            /*printf("BinaryString: %s\n", binaryString);*/
            free(letterCode);
            letterCode = NULL;
        }
    }
    while(letter != EOF);

    fclose(file);

    return(binaryString);
}

char * getLetterCode(EncodingTree * root, char letter, char * currentCode, int currentLength)
{
    EncodingTree * temp;
    char * letterCode;
    int codeLength;

    temp = root;
    letterCode = NULL;
    codeLength = currentLength;

    letterCode = malloc(sizeof(char) * (codeLength + 1));
    if(letterCode == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    if(currentCode != NULL)
    { 
        strcpy(letterCode, currentCode);
        free(currentCode);
    }
    else
    {
        /*printf("FirstRun\n");*/
        strcpy(letterCode, "");
    }

    if(temp == NULL)
    {
        return(NULL);
    }

    if(temp->letter == letter)
    {
        return(letterCode);
    }
    else
    {
        codeLength++;
        letterCode = reallocf(letterCode, (sizeof(char) * (codeLength + 1)));
        if(letterCode == NULL)
        {
            printf("Error: not enough memory\n");
            exit(0);
        }
        if(isLetterInTree(temp->lChild, letter) == 1)
        {
            strcat(letterCode, "0");
            /*printf("Curent Code: %s\n", letterCode);*/
            return(getLetterCode(temp->lChild, letter, letterCode, codeLength));
        }
        else if(isLetterInTree(temp->rChild, letter) == 1)
        {
            strcat(letterCode, "1");
            /*printf("Curent Code: %s\n", letterCode);*/
            return(getLetterCode(temp->rChild, letter, letterCode, codeLength));
        }
        else
        {
            return(NULL);
        }
    }
}

int isLetterInTree(EncodingTree * tree, char letter)
{
   if(tree == NULL)
   {
       return(0);
   } 
   else
   {
       if(tree->letter == letter)
       {
           return(1);
       }
       else
       {
           return(isLetterInTree(tree->lChild, letter) | isLetterInTree(tree->rChild, letter));
       }
   }
}

char convertASCIICode(char * binString)
{
    return(strtol(binString, NULL, 2));
}

int encode(char * rFileName)
{
    char * wFileName;
    CharCounts * counts;
    EncodingTree * tree;
    char * encodedString;

    wFileName = NULL;
    counts = NULL;
    tree = NULL;
    encodedString = NULL;    

    wFileName = malloc(sizeof(char) * (strlen(rFileName) + 5));
    strcpy(wFileName, rFileName);
    strcat(wFileName, ".arc");

    counts = getCharCounts(rFileName);
    counts = sortCounts(counts);

    tree = createTree(counts);

    encodedString = getBinaryCode(tree, counts, rFileName);
    /*printf("%s\n", encodedString);*/

    return(1);
}

int writeToFile(char * wFileName, char * string)
{
    FILE * wFile;

    wFile = fopen(wFileName, "w");
    if(wFile == NULL)
    {
        printf("Error: file could not be found\n");
        exit(0);
    }

    /* TODO Get substrings from string, and write the ASCII letters to the file */

    fclose(wFile);
    
    return(1);    
}

char * getSubstring(char * string, int start, int end)
{
    char * substring;
    int length;
    int i;

    substring = NULL;
    length = 0;
    i = 0;

    length = end - start + 1;
    substring = malloc(sizeof(char) * (length + 1));

    for(i = 0; i < length; i++)
    {
        substring[i] = string[start + i];
    }    
    substring[i] = '\0';

    return(substring);
}
