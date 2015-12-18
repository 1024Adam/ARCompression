/* huffman.c */

/*
 * Adam Reid
 * December 15, 2015
 */

#include "huffman.h"

/* 
 * getBinaryCode
 * Function: Retrieve the character read from the file as a binary code (using the EncodingTree)
 * Parameters: The EncodingTree to retreive the binary codes from; The string literal of the file path name
 * Return: The full binary code of the file
 */
char * getBinaryCode(EncodingTree * root, char * fileToOpen)
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

    encodedString = getBinaryCode(tree, rFileName);
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
