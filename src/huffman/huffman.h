/* huffman.h */

/*
 * Adam Reid
 * December 6, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct CharCounts
{
    char letter;
    int count;
    struct CharCounts * next; 
    struct CharCounts * prev;
}
CharCounts;

typedef struct EncodingTree
{
    char letter;
    int count;
    struct EncodingTree * lChild;
    struct EncodingTree * rChild; 
}
EncodingTree;

typedef struct TreeQueue
{
    EncodingTree * root;
    struct TreeQueue * next;
}
TreeQueue;

CharCounts * getCharCounts(char * fileToOpen);
int isCounted(CharCounts * root, char letter);
CharCounts * createCount(char  letter);
CharCounts * addChar(CharCounts * root, char toAdd);
CharCounts * addCount(CharCounts * root, char letter);
void printCounts(CharCounts * root);
CharCounts * sortCounts(CharCounts * root);
int getLength(CharCounts * root);
CharCounts * removeFront(CharCounts * root);

EncodingTree * createTree(CharCounts * counts);
TreeQueue * createBranch(CharCounts * count);
TreeQueue * createBranchFromTree(EncodingTree * root);
int treeNodeCount(EncodingTree * root);
EncodingTree * insertInTree(EncodingTree * root, EncodingTree * toAdd);
TreeQueue * insertInQueue(TreeQueue * root, TreeQueue * toAdd);
int isEmpty(TreeQueue * root);
TreeQueue * removeFromQueue(TreeQueue * root);
