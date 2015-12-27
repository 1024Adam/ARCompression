/* huffman.c */

/*
 * Adam Reid
 * December 24, 2015
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
    SearchTreeList * sList;
    SearchTree * sTree;

    letter = '\0';
    letterCode = NULL;
    binaryString = NULL;
    binaryLength = 0;
    sList = NULL;
    sTree = NULL;

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

    sList = createSearchList(sList, root, NULL, 0);
    /*printSearchTreeList(sList);*/
    sTree = createSearchTree(sList);
    /*printSearchTree(sTree);*/
    /*printf("\n\n");*/

    do
    {
        letter = fgetc(file);
        if(letter != EOF)
        {
            /*printf("Letter: %c\n", letter);*/
            letterCode = getLetterCode(sTree, letter);
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
            letterCode = NULL;
        }
    }
    while(letter != EOF);

    fclose(file);

    return(binaryString);
}

/*
 * getLetterCode
 * Function: Get the binary code for the individual letter passed 
 * Parameters: The EncodingTree to retrieve the binary code from; The letter to retrieve the binary code for;
 *             The current running binary code of the letter; The current running length of the binary code
 * Return: The binary code for the letter passed
 */
char * getLetterCode(SearchTree * root, int letterNum)
{
    SearchTree * temp;
    temp = root;
    
    if(temp == NULL)
    {
        return(NULL);
    }
    
    if(temp->letterNum == letterNum)
    {
        return(temp->letterCode);
    }
    else
    {
        if(letterNum <= temp->letterNum) 
        {
            return(getLetterCode(temp->lChild, letterNum));
        }
        else if(letterNum > temp->letterNum)
        {
            return(getLetterCode(temp->rChild, letterNum));
        }
        else
        {
            return(NULL);
        }
    }
}

/* 
 * isLetterInTree
 * Function: find if the letter passed is contatined in the EncodingTree
 * Parameters: the EncodingTree to search in; The letter in question
 * Return: 1 - The letter IS in the EncodingTree
 *         0 - The letter IS NOT in the EncodingTree
 */
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

/*
 * convertASCIICode
 * Function: Convert the binary code (as a string) into a character value
 * Parameters: The binary string to be converted
 * Return: The binary value as a character 
 */
char convertASCIICode(char * binString)
{
    return(strtol(binString, NULL, 2));
}

/*
 * encode
 * Function: Convert the entire file passed into an encoded string, and write the string to a new file
 * Parameters: The file path as a string literal to read from
 * Return: 1 - On success
 *         0 - On failure
 */
int encode(char * rFileName)
{
    char * wFileName;
    CharCounts * counts;
    EncodingTree * tree;
    char * encodedString;
    int success;
    SearchTreeList * sTreeList;
    SearchTree * sTree;

    wFileName = NULL;
    counts = NULL;
    tree = NULL;
    encodedString = NULL;
    success = 0;    
    sTreeList = NULL;
    sTree = NULL;

    wFileName = malloc(sizeof(char) * (strlen(rFileName) + 5));
    if(wFileName == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    strcpy(wFileName, rFileName);
    strcat(wFileName, ".arc");

    counts = getCharCounts(rFileName);
    counts = sortCounts(counts);

    tree = createTree(counts);

    encodedString = getBinaryCode(tree, rFileName);
    /*printf("%s\n", encodedString);*/
    success = writeToFile(wFileName, encodedString, tree);

    counts = freeCounts(counts);
    tree = freeTree(tree);

    return(success);
}

/*
 * writeToFile
 * Function: Write the encoded string to the new file
 * Parameters: The string literal of the new file path name; The encoded string to write to the file
 * Return: 1 - On success
 *         0 - On failure
 */
int writeToFile(char * wFileName, char * string, EncodingTree * tree)
{
    FILE * wFile;
    int length;
    int i;
    char * substring;
    char letter;
 
    length = 0;
    i = 0;
    substring = NULL;
    letter = '\0';

    wFile = fopen(wFileName, "w");
    if(wFile == NULL)
    {
        printf("Error: file could not be found\n");
        exit(0);
    }

    /* Greab each substring of 8 characters, and write the ASCII value to the file */
    length = strlen(string);
    for(i = 0; i < length; i += 8)
    {
        substring = getSubstring(string, i, i + 7);
        /*printf("substring %d to %d: %s\n", i, i + 7, substring);*/
        letter = convertASCIICode(substring);
        /*printf("Resulting letter: %c\n\n", letter);*/
        fprintf(wFile, "%c", letter);
    }
    fprintf(wFile, "\n:ARC:\n");
    length = strlen(substring);
    fprintf(wFile, "%d\n", length);
    filePrintTree(wFile, tree);
    
    printf("The file has been encoded to %s\n", wFileName);

    fclose(wFile);
    
    return(1);    
}

/*
 * filePrintTree
 * Function: Print the contents of the tree to a file in a compressed format
 * Parameters: The file to write to; The tree to print
 * Return: void 
 */
void filePrintTree(FILE * wFile, EncodingTree * tree)
{
    if(tree != NULL)
    {
        fprintf(wFile, "%c,", tree->letter);
        filePrintTree(wFile, tree->lChild);
        filePrintTree(wFile, tree->rChild);
    }
}

/* 
 * getSubstring
 * Function: Retrieve a substring of the given string from the start number to the end number
 * Parameters: The string to get the substring from; the start character position;
               The end character position
 * Return: The substring from start to end
 */
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
    if(substring == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    for(i = 0; i < length; i++)
    {
        substring[i] = string[start + i];
    }    
    substring[i] = '\0';

    return(substring);
}
