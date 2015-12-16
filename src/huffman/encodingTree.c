/* encodingTree.c */

/*
 * Adam Reid
 * December 15, 2015
 */

#include "encodingTree.h"

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
