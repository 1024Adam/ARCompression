/* huffman.c */

/*
 * Adam Reid
 * January 28, 2017
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
    unsigned char uletter;
    char letter;
    char * letterCode;
    char * binaryString;
    int binaryLength;
    long i;
    SearchTreeList * sList;
    SearchTree * sTree;

    uletter = '\0';
    letter = '\0';
    letterCode = NULL;
    binaryString = NULL;
    binaryLength = 0;
    i = 0;
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
    
    printf("\r######                30%% Processing file contents...    ");
    fflush(stdout);
    do
    {
        if(i == 500000)
        {
            printf("\r##########            50%% Still working... don't worry :)");
            fflush(stdout);
        }
        uletter = fgetc(file);
        letter = uletter;
        if(letter != EOF)
        {
            /*printf("Letter: %c\n", letter);*/
            letterCode = getLetterCode(sTree, uletter);
            /*printf("LetterCode: %s\n", letterCode);*/
            binaryLength += strlen(letterCode);
            /*printf("BinaryLength: %d\n", binaryLength);*/
            binaryString = realloc(binaryString, (sizeof(char) * (binaryLength + 1)));
            if(binaryString == NULL)
            {
                printf("Error: not enough memory\n");
                exit(0);
            }
            strcat(binaryString, letterCode);
            /*printf("BinaryString: %s\n", binaryString);*/
            letterCode = NULL;
        }
        i++;
    }
    while(letter != EOF);

    fclose(file);
    freeSTree(sTree);

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
    
    /* Recursive Method */
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
    /* Iterative Method
    while(temp->letterNum != letterNum)
    {
        if(letterNum <= temp->letterNum)
        {
            temp = temp->lChild;
        }
        else
        {
            temp = temp->rChild;
        }    
    }
    return(temp->letterCode);
    */
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
    
    printf("                       0%% Configuring encoding...          ");
    fflush(stdout);
    counts = getCharCounts(rFileName);
    counts = sortCounts(counts);
    
    tree = createTree(counts);
    /*printTree(tree);*/
    printf("\r#####                 25%% Creating encoding string...    ");
    fflush(stdout);
    encodedString = getBinaryCode(tree, rFileName);
    /*printf("%s\n", encodedString);*/
    printf("\r###############       75%% Printing to file...            ");
    fflush(stdout);
    success = writeToFile(wFileName, encodedString, tree);
    if (success == 1)
    {
        printf("\r#################### 100%% The file has been encoded to %s\n", wFileName);
        fflush(stdout);
    }
    free(wFileName);
    free(encodedString);
    counts = freeCounts(counts);
    tree = freeTree(tree);

    return(success);
}

/*
 * writeToFile
 * Function: Write the encodedi/decoded string to the new file
 * Parameters: The string literal of the new file path name; The encoded/decoded string to write to the file; (For encoding) the encoding tree used, otherwise NULL
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
    
    /* Grab each substring of 8 characters, and write the ASCII value to the file */
    length = strlen(string);
    /*printf("Length: %d\n", length);*/
    for(i = 0; i < length; i += 8)
    {
        if((i + 7) >= length)
        {
            substring = getSubstring(string, i, (length - 1));
            /*printf("substring %d to %d: %s\n", i, (length - 1), substring);*/
        }
        else
        {
            substring = getSubstring(string, i, i + 7);
            /*printf("substring %d to %d: %s\n", i, i + 7, substring);*/
        }
        letter = strtol(substring, NULL, 2);
        /*printf("Resulting letter: %c\n\n", letter);*/
        fprintf(wFile, "%c", letter);
    }

    fprintf(wFile, ":ARC:");
    length = strlen(substring);
    fprintf(wFile, "%d", length);
    filePrintTree(wFile, tree);

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
        fprintf(wFile, "%c", tree->letter);
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

int decode(char * rFileName)
{
    char * wFileName;
    EncodingTree * eTree;
    char * encodedString;   
    int success;
 
    success = 0;
    eTree = getTreeFromFile(rFileName);
    /*printTree(eTree);*/

    wFileName = getDecodeFileName(rFileName);    
    encodedString = getEncodedBinary(rFileName);
    /*printf("%s\n", encodedString);*/
    success = decodeToFile(wFileName, encodedString, eTree);

    free(encodedString);
    free(wFileName);
    freeTree(eTree);

    return(1);
}

char * getDecodeFileName(char * rFileName)
{
    char * wFileName;
    int length;

    length = strlen(rFileName);
    wFileName = malloc(sizeof(char) * (length - 3));

    strncpy(wFileName, rFileName, (length - 4));
    wFileName[length - 4] = '\0';

    /*printf("%s\n", wFileName);*/     
  
    return(wFileName);
}

char * getEncodedBinary(char * rFileName)
{
    FILE * rFile;
    unsigned char phrase[6] = {'\0'};
    char sphrase[6] = {'\0'};
    char * encodedBinary;
    char * charBinary;
    char temp[2] = {'\0'};
    int length;
    int lastLength;
    int i;

    i = 0;
    length = 1;
    lastLength = 0;
    rFile = fopen(rFileName, "r");
    charBinary = NULL;
    encodedBinary = malloc(sizeof(char));
    if(encodedBinary == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    strcpy(encodedBinary, "");
    
    /* Until the point in the file where ":ARC:" is found */
    while(strcmp(sphrase, ":ARC:") != 0)
    {
        for(i = 0; i < 5; i++)
        {
            phrase[i] = fgetc(rFile);
            sphrase[i] = phrase[i];
        }
        phrase[i] = '\0';
        sphrase[i] = '\0';

        if(strcmp(sphrase, ":ARC:") != 0)
        {
            /* Figure out what the binary string is */
            /*printf("%c\n", phrase[0]);*/
            charBinary = getBinary(phrase[0]);
            for(i = 0; i < 4; i++)
            {
                phrase[i] = phrase[i + 1];
                sphrase[i] = phrase[i];
            }
            phrase[i] = fgetc(rFile);
            sphrase[i] = phrase[i];
            i++;
            phrase[i] = '\0';
            sphrase[i] = '\0';
            if(strcmp(sphrase, ":ARC:") == 0)
            {
                temp[0] = fgetc(rFile);
                lastLength = strtol(temp, NULL, 10);
                /*printf("LastLength: %d\n", lastLength);*/
                length += lastLength;
            
                charBinary = getSubstring(charBinary, 8 - lastLength, 7);
            }
            else
            {
                for(i = 4; i >= 0; i--)
                {
                    ungetc(phrase[i], rFile);
                }
                length += 8;
            }
            encodedBinary = realloc(encodedBinary, length);
            strcat(encodedBinary, charBinary);
            /*printf("%s\n", encodedBinary);*/
            free(charBinary);
        }
    }

    fclose(rFile);
    return(encodedBinary);
}

char * getBinary(unsigned char letter)
{
    char * binaryCode;
    int i;
    int length;

    binaryCode = malloc(sizeof(char) * 9);
    i = 0;
    length = 0;
    
    if(binaryCode == NULL)
    {
        printf("Error: Not enough memory\n");
        exit(0);
    }

    /*printf("%u\n", letter);*/

    for(i = 7; i >= 0; i--)
    {
        if(letter - pow(2, i) >= 0)
        {
            binaryCode[length] = '1';
            letter -= pow(2, i);
        }
        else
        {
            binaryCode[length] = '0';
        }
        length++;
    }
    binaryCode[length] = '\0';

    return(binaryCode);
}

int decodeToFile(char * wFileName, char * string, EncodingTree * tree)
{
    FILE * wFile;
    int i;
    EncodingTree * tempTree;
 
    i = 0;
    tempTree = tree;

    wFile = fopen(wFileName, "w");
    if(wFile == NULL)
    {
        printf("Error: file could not be found\n");
        exit(0);
    }
 
    while(string[i] != '\0')
    {
        while(tempTree->lChild != NULL && tempTree->rChild != NULL)
        {
            /*printf("%c\n", string[i]);*/
            if(string[i] == '0')
            {
                /*printf("LEFT\n");*/
                tempTree = tempTree->lChild; 
            }
            else /* string[i] == 1 */ 
            {
                /*printf("RIGHT\n");*/
                tempTree = tempTree->rChild; 
            }
            i++;
        }
        fprintf(wFile, "%c", tempTree->letter);
        tempTree = tree;
    }
    
    printf("The file has been decoded to %s\n", wFileName);

    fclose(wFile);
    
    return(1);    
}
