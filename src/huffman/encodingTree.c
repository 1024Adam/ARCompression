/* encodingTree.c */

/*
 * Adam Reid
 * December 24, 2015
 */

#include "encodingTree.h"

/*
 * createTree
 * Function: Uses a CharCounts list to create a min-heap Huffman binary tree
 * Parameters: The CharCounts list to use
 * Return: The min-heap Huffman binary tree
 */
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
 
    /* Insert all CharCounts into the TreeQueue (sorted least to greatest) */
    tempCount = counts;
    while(tempCount != NULL)
    {
        toAdd = createBranch(tempCount);
        tempCount = tempCount->next;
        queue = insertInQueue(queue, toAdd);
    }
    /*printQueue(queue);*/
    toAdd = NULL;
    /* 
     * Remove from the TreeQueue, TWO AT A TIME, to create a singular binary tree, 
     * and insert back into sorted queue accordingly 
     * Continue until there is nothing left in the queue
     */
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

/*
 * treeNodeCount
 * Function: Count the number of nodes contained in the EncodingTree passed
 * Parameters: The EncodingTree to count the nodes in
 * Return: The count of the number of nodes in the EncodingTree
 */
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

/*
 * insertInTree
 * Function: Take the two EncodingTrees passed, and combine them into one EncodingTree
 * Parameters: The original EncodingTree; The EncodingTree to combine with the original
 * Return: The new EncodingTree, containing the two EncodingTrees passed
 */
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

/* 
 * printTree
 * Function: Print the contents of the tree, using the pre-order method to print them 
 * Parameters: The EncodingTree to print
 * Return: void
 */
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

/* 
 * freeTree
 * Function: Remove, and free all of the nodes within the EncodingTree passed
 * Parameters: The EncodingTree to free
 * Return: NULL
 */
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

/* 
 * createBranch
 * Function: Create a new "branch" to insert into the TreeQueue
 * Parameters: The CharCount to be used to create the branch
 * Return: The new branch for the TreeQueue
 */
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

/*
 * createBranchFromTree
 * Function: Create a new "branch" to insert into the TreeQueue
 * Parameters: The EncodingTree to be used to create the branch
 * Return: The new branch for the TreeQueue
 */
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

/* 
 * insertInQueue
 * Function: Insert the new TreeQueue item into the current TreeQueue, maintaining the least to greatest sorting
 * Parameters: The original TreeQueue; The TreeQueue item to add
 * Return: The updated TreeQueue item
 */
TreeQueue * insertInQueue(TreeQueue * root, TreeQueue * toAdd)
{
    TreeQueue * temp;
    temp = root;

    /*printf("ToAdd\n");
    printQueue(toAdd);*/
 
    /* Find the insertion point */
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

/*
 * isEmpty
 * Function: Check to see if the queue has any items in it
 * Parameters: The TreeQueue in question
 * Return: 1 - The TreeQueue IS empty
 *         0 - The TreeQueue IS NOT empty
 */
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

/*
 * removeFromQueue
 * Function: Removes the first item from the TreeQueue, and frees the removed item
 * Parameters: The TreeQueue to remove from
 * Return: The updated TreeQueue
 */
TreeQueue * removeFromQueue(TreeQueue * root)
{
    TreeQueue * temp;
    temp = root;

    root = root->next;

    free(temp);
    return(root);
}

/*
 * printQueue
 * Function: Print out all of the TreeQueue items, in the order that they appear in the queue
 * Parameters: The TreeQueue to print
 * Return: void
 */
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

/*
 * createSearchList
 * Function: Creates a binary search tree list from the EncodingTree passed
 * Parameters: The EncodingTree to create the seaarch tree list with
 * Return: The binary search tree list
 */
SearchTreeList * createSearchList(SearchTreeList head, EncodingTree * eTree)
{
    SearchTreeList * temp;
    EncodingTree * tempETree;

    temp = NULL;
    tempETree = eTree;

    if(tempETree->lChild == NULL && tempETree->rChild == NULL)
    {
        temp = createSearchNode(tempETree);
        head = insertSearchNode(head, temp);
    }
    else
    {
        head = createSearchList(head, tempETree->lChild);
        head = createSearchList(head, tempETree->rChild);
    }

    return(head);
}

SearchTree * createSearchNode(EncodingTree * eTree, char * letterCode)
{
    SearchTree * sTree;

    sTree = malloc(sizeof(SearchTree));

    sTree->letter = eTree->letter;
    sTree->count = eTree->count;
    sTree->letterCode = letterCode;
    sTree->lChild = NULL;
    sTree->rChild = NULL;

    return(sTree);
}

SearchTreeList * insertSearchNode(SearchTreeList * head, SearchTree * toAdd)
{
    SearchTreeList * temp;
    SearchTreeList * newNode;

    temp = head;
    newNode = malloc(sizeof(SearchTreeList));
    newNode->sTree = toAdd;
    newNode->next = NULL;

    while(temp->next != NULL && toAdd->count <= temp->next->sTree->count)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return(head);
}
