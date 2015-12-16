/* encodingTree.h */

/*
 * Adam Reid
 * December 15, 2015
 */

#ifndef ENCODING_TREE
#define ENCODING_TREE

#include "arCompress.h"

typedef struct EncodingTree
{
    char letter;
    int count;
    struct EncodingTree * lChild;
    struct EncodingTree * rChild; 
}
EncodingTree;

EncodingTree * createTree(CharCounts * counts);
int treeNodeCount(EncodingTree * root);
EncodingTree * insertInTree(EncodingTree * root, EncodingTree * toAdd);
void printTree(EncodingTree * root);
EncodingTree * freeTree(EncodingTree * tree);

#endif
