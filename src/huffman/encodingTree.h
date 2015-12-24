/* encodingTree.h */

/*
 * Adam Reid
 * December 24, 2015
 */

#ifndef ENCODING_TREE
#define ENCODING_TREE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

typedef struct SearchTree
{
    char letter;
    int count;
    char * letterCode;
    struct EncodingTree * lChild;
    struct EncodingTree * rChild;
}
SearchTree;

typedef struct SearchTreeList
{
    SearchTree * sTree;
    struct SearchTreeList * next;
}
SearchTreeList;

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

SearchTreeList * createSearchList(SearchTreeList * head, EncodingTree * eTree);
SearchTree * createSearchNode(EncodingTree * eTree, char * letterCode);
SearchTreeList * insertSearchNode(SearchTreeList head, SearchTree * toAdd);

#endif
