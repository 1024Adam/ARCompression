/* encodingTree.h */

/*
 * Adam Reid
 * December 15, 2015
 */

#ifndef ENCODING_TREE
#define ENCODING_TREE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charCounts.h"

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

EncodingTree * createTree(CharCounts * counts);
int treeNodeCount(EncodingTree * root);
EncodingTree * insertInTree(EncodingTree * root, EncodingTree * toAdd);
void printTree(EncodingTree * root);
EncodingTree * freeTree(EncodingTree * tree);

TreeQueue * createBranch(CharCounts * count);
TreeQueue * createBranchFromTree(EncodingTree * root);
TreeQueue * insertInQueue(TreeQueue * root, TreeQueue * toAdd);
int isEmpty(TreeQueue * root);
TreeQueue * removeFromQueue(TreeQueue * root);
void printQueue(TreeQueue * root);

#endif
