/* treeQueue.h */

/*
 * Adam Reid
 * December 15, 2015
 */

#ifndef TREE_QUEUE
#define TREE_QUEUE

#include "arCompress.h"

typedef struct TreeQueue
{
    EncodingTree * root;
    struct TreeQueue * next;
}
TreeQueue;

TreeQueue * createBranch(CharCounts * count);
TreeQueue * createBranchFromTree(EncodingTree * root);
TreeQueue * insertInQueue(TreeQueue * root, TreeQueue * toAdd);
int isEmpty(TreeQueue * root);
TreeQueue * removeFromQueue(TreeQueue * root);
void printQueue(TreeQueue * root);

#endif
