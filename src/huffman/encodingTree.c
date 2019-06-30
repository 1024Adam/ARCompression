/* encodingTree.c */

/*
 * Adam Reid
 * April 30, 2016
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
    CharCounts * tempCount;

    root = NULL;
    queue = NULL;
    toAdd = NULL;
    temp1 = NULL;
    temp2 = NULL;
    tempCount = NULL;
 
    /* Insert all CharCounts into the TreeQueue (sorted least to greatest) */
    tempCount = counts;
    while(tempCount != NULL)
    {
        toAdd = createBranch(tempCount);
        tempCount = tempCount->next;
        queue = insertInQueue(queue, toAdd);
    }
    toAdd = NULL;
    /* 
     * Remove from the TreeQueue, TWO AT A TIME, to create a singular binary tree, 
     * and insert back into sorted queue accordingly 
     * Continue until there is nothing left in the queue
     */
    while(isEmpty(queue) == 0)
    {
        if(toAdd != NULL)
        {
            queue = insertInQueue(queue, toAdd);
        }
        temp1 = queue->root;
        queue = queue->next;
        temp2 = queue->root;
        queue = queue->next;
        temp2 = insertInTree(temp2, temp1);
        toAdd = createBranchFromTree(temp2);
    }

    root = toAdd->root;

    return (root);
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
        return (nodeCount);
    }
    else
    {
        return (nodeCount + 1 + treeNodeCount(root->lChild) + treeNodeCount(root->rChild));
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
        free(newRoot);

        return (toAdd);
    }
    else
    {
        newRoot->lChild = toAdd;
        newRoot->rChild = root;

        return (newRoot);
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
        printf("%c %d\n", root->letter, root->count);
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
    return (NULL);
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

    return (branch);
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

    return (branch);
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

    /* Find the insertion point */
    while(temp != NULL && temp->next != NULL && temp->root->count < toAdd->root->count)
    {   
        temp = temp->next;
    }   
    
    if(root == NULL)
    {   
        toAdd->next = NULL;
        return (toAdd);
    }   
    else if(temp->next == NULL)
    {   
        temp->next = toAdd;
        toAdd->next = NULL;
        return (root);
    }   
    else
    {   
        toAdd->next = temp->next;
        temp->next = toAdd;
        return (root);
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
        return (1);
    }   
    else
    {   
        return (0);
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
    return (root);
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
        temp = temp->next;
    }
}

/*
 * createSearchList
 * Function: Creates a binary search tree list from the EncodingTree passed
 * Parameters: The head of the search list; The EncodingTree to create the search tree list with; the current running code; the current running code length
 * Return: The binary search tree list
 */
SearchTreeList * createSearchList(SearchTreeList * head, EncodingTree * eTree, char * currentCode, int currentLength)
{
    SearchTree * temp;
    EncodingTree * tempETree;
    char * letterCode;
    int codeLength;

    temp = NULL;
    tempETree = eTree;
    letterCode = NULL;
    codeLength = currentLength;

    letterCode = malloc(sizeof(char) * (codeLength + 1));
    if(letterCode == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    if(currentCode == NULL)
    {
        strcpy(letterCode, "");
    }
    else
    {
        strcpy(letterCode, currentCode);
    }
    if(tempETree->lChild == NULL && tempETree->rChild == NULL)
    {
        temp = createSearchNode(tempETree, letterCode);
        head = insertSearchNode(head, temp);
    }
    else
    {
        codeLength++;
        letterCode = realloc(letterCode, (sizeof(char) * (codeLength + 1)));
        letterCode[codeLength - 1] = '0';
        head = createSearchList(head, tempETree->lChild, letterCode, codeLength);
        letterCode[codeLength - 1] = '1';
        head = createSearchList(head, tempETree->rChild, letterCode, codeLength);
    }

    return (head);
}

/*
 * createSearchNode
 * Function: Creates a search node for the purpose of being put into a SearchTree
 * Parameters: The EncodingTree to create the node from; the letter code to use;
 * Return: the SearchTree node to insert
 */
SearchTree * createSearchNode(EncodingTree * eTree, char * letterCode)
{
    SearchTree * sTree;

    sTree = malloc(sizeof(SearchTree));
    if(sTree == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    sTree->letter = eTree->letter;
    sTree->letterNum = eTree->letter;
    sTree->letterCode = letterCode;
    sTree->lChild = NULL;
    sTree->rChild = NULL;

    return (sTree);
}

/*  
 * insertSearchNode
 * Function: Insert a newly created SearchTree node into the STL
 * Parameters: The current STL, the node to add
 * Return: The new STL with the node inserted properly
 */
SearchTreeList * insertSearchNode(SearchTreeList * head, SearchTree * toAdd)
{
    SearchTreeList * temp;
    SearchTreeList * newNode;

    temp = head;
    newNode = malloc(sizeof(SearchTreeList));
    if(newNode == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    newNode->sTree = toAdd;
    newNode->next = NULL;

    if(head == NULL)
    {
        return(newNode);
    }
    while(temp->next != NULL && toAdd->letterNum >= temp->next->sTree->letterNum)
    {
        temp = temp->next;
    }
    if(toAdd->letterNum < temp->sTree->letterNum)
    {
        newNode->next = temp;
        return (newNode);
    }
    else
    {
        newNode->next = temp->next;
        temp->next = newNode;
        return (head);
    }
}

/* 
 * printSearchTreeList
 * Function: Print the contents of the STL 
 * Parameters: The SearchTreeList to print
 * Return: void
 */
void printSearchTreeList(SearchTreeList * head)
{
    SearchTreeList * temp;
    temp = head;

    printf("START OF LIST\n");
    while(temp != NULL)
    {
        printf("%c,%d,%s\n", temp->sTree->letter, temp->sTree->letterNum, temp->sTree->letterCode);
        temp = temp->next;
    }
    printf("END OF LIST\n");
}

/*
 * createSearchTree
 * Function: Create a balanced ST to use in the encoding process
 * Parameters: The STL to create the ST with
 * Return: The ST
 */
SearchTree * createSearchTree(SearchTreeList * head)
{
    SearchTree * sTree;
    SearchTreeList * temp;
    SearchTreeList * leftList;
    SearchTreeList * rightList;
    int length;
    int middle;
    int i;

    sTree = NULL;
    temp = head;
    leftList = NULL;
    rightList = NULL;
    length = getLengthOfList(head);
    middle = findHighestDouble(head, ((length + 1) / 2));
    i = 0;
    
    if(length == 0)
    {
        return(NULL);
    }    
    else
    {
        if(length == 1)
        {
            sTree = temp->sTree;
            rightList = NULL;
            leftList = NULL;
            free(temp);
        }
        else if(length == 2)
        {
            sTree = temp->sTree;
            rightList = getList(head, middle, 1);
            leftList = NULL;
            free(temp); 
        }
        else
        {
            rightList = getList(head, middle, 1);
            leftList = getList(head, middle, 0);
            for(i = 1; i < (middle - 1); i++)
            {
                temp = temp->next;
            }
            sTree = temp->next->sTree;
            free(temp->next);
            temp->next = temp->next->next;   
        }
        sTree->lChild = createSearchTree(leftList);
        sTree->rChild = createSearchTree(rightList);
    }

    return (sTree);
}

/*
 * getLengthOfList
 * Function: get the length of the STL
 * Parameters: The STL to get the length of
 * Return: The length of the STL
 */
int getLengthOfList(SearchTreeList * head)
{
    SearchTreeList * temp;
    int count;

    temp = head;
    count = 0;

    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return (count);
}

/*
 * findHighestDouble
 * Function: Get the position of the furthest node with the same letterNum as the middle
 * Parameters: The STL to search in; The middle of the list
 * Return: The next highest position
 */ 
int findHighestDouble(SearchTreeList * head, int middle)
{
    int i;
    int count;
    SearchTreeList * temp;

    i = 0;
    count = 0;
    temp  = head;

    if(temp == NULL)
    {
        return (0);
    }
    else
    {
        for(i = 1; i < middle; i++)
        {
            temp = temp->next;
        }
        count = temp->sTree->letterNum;
    
        while(temp != NULL && temp->sTree->letterNum == count)
        {
            temp = temp->next;
            i++;
        }
        return (i - 1);
    }
}

/* 
 * getList
 * Function: Gets the remaining left/right side of the STL based on the middle specified
 * Parameters: The STL to use; the middle of the list; the side to get (0 left 1 right)
 * Return: The specified side of the original list
 */
SearchTreeList * getList(SearchTreeList * head, int middle, int direction)
{
    int i;
    SearchTreeList * newList;   
 
    i = 1;
    newList = head;
   
    if(getLengthOfList(head) == 2)
    { 
        if(direction == 0)
        {
            return (NULL);
        }
        else if(direction == 1)
        {
            return (newList->next);
        }
        else
        {
            return (NULL);
        }
    }
    else
    { 
        if(direction == 0)
        {
            /* LEFT */
            while(i < middle)
            {
                newList = newList->next;
                i++;
            }

            newList->next = NULL;
            return (head);
        }
        else if(direction == 1)
        {
            /* RIGHT */
            while(i <= middle)
            {
                newList = newList->next;
                i++;
            }
    
            return (newList);
        }
        else
        {
            return (NULL);
        }
    }
}

/* 
 * printSearchTree
 * Function: Print the contents of the tree, using the pre-order method to print them 
 * Parameters: The SearchTree to print
 * Return: void
 */
void printSearchTree(SearchTree * root)
{
    if(root != NULL)
    {
        printf("ROOT\n");
        printf("%c%d\n", root->letter, root->letterNum);
        printf("LeftChild\n");
        printSearchTree(root->lChild);
        printf("\n");
        printf("RightChild\n");
        printSearchTree(root->rChild);
        printf("\n");
    }
}

/*
 * freeSTree
 * Function: Free all of the elements contained in the ST
 * Parameters: The ST to free
 * Return: NULL
 */
SearchTree * freeSTree(SearchTree * sTree)
{
    if(sTree != NULL)
    {
        if(sTree->lChild != NULL)
        {
            sTree->lChild = freeSTree(sTree->lChild);
        }
        if(sTree->rChild != NULL)
        {
            sTree->rChild = freeSTree(sTree->rChild);
        }
        free(sTree->letterCode);
        free(sTree);
    }
    return (NULL);
}

/*
 * freeSTList
 * Function: Free all of the elements contained in the STL
 * Parameters: The STL to free
 * Return: NULL
 */
SearchTreeList * freeSTList(SearchTreeList * sList)
{
    SearchTreeList * temp;

    temp = sList;
    while(sList != NULL)
    {
        temp = sList;
        sList = sList->next;
        free(temp);
    }
    return (NULL);
}

/*
 * getTreeFromFile
 * Function: Use a previously encoded file to create a EncodingTree
 * Parameters: The path to the encoded file
 * Return: The EncodingTree produced
 */
EncodingTree * getTreeFromFile(char * fileName)
{
    FILE * file;
    EncodingTree * eTree;
    EncodingTree * toAdd;
    char phrase[6] = {'\0'};
    char letter;
    int i;

    file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }
    
    eTree = NULL;
    toAdd = NULL;
    i = 0;
    letter = '\0';

    /* Find the point in the file where ":ARC:" is found */
    while(strcmp(phrase, ":ARC:") != 0)
    {
        for(i = 0; i < 5; i ++)
        {
            phrase[i] = fgetc(file);
        }
        phrase[i] = '\0';
        for(i = 4; i > 0; i--)
        {
            ungetc(phrase[i], file);
        }
    }
    for(i = 0; i < 5; i++)
    {
       fgetc(file);
    }
    /***/
    letter = fgetc(file);
    while(letter != EOF)
    {
        toAdd = createSubTree(letter);
        eTree = insertSubTree(eTree, toAdd);    
        letter = fgetc(file);
    }
    
    fclose(file);    
    return (eTree);
}

EncodingTree * createSubTree(unsigned char letter)
{
    EncodingTree * eTree;

    eTree = malloc(sizeof(EncodingTree));
    if(eTree == NULL)
    {
        printf("Error: not enough memory\n");
        exit(0);
    }

    eTree->letter = letter;
    eTree->count = 0;
    eTree->lChild = NULL;
    eTree->rChild = NULL;

    return (eTree);
}

EncodingTree * insertSubTree(EncodingTree * eTree, EncodingTree * toAdd)
{
    EncodingTree * temp;

    temp = eTree;

    if(eTree == NULL)
    {
        return(toAdd);
    }
    else
    {  
        /* LETTERS STOP PROGRESS ON THAT BRANCH */
        temp = findNextPosition(eTree, NULL, 0);
        if(temp == NULL)
        {
            printf("Error: invalid .arc file\n");
            exit(0);
        }        
        else if(temp->lChild == NULL)
        { 
            temp->lChild = toAdd;
        }
        else /*(temp->rChild == NULL)*/
        {
            temp->rChild = toAdd;
        }
        return(eTree);
    }
} 

EncodingTree * findNextPosition(EncodingTree * eTree, EncodingTree * eParent, int checkedLeft)
{
    EncodingTree * temp;
    
    temp = eTree;
    
    if(eTree == NULL)
    {
        if(checkedLeft == 1) /* Left side has been checked already */
        {
            return (eParent);
        }
        else
        {
            return (NULL);
        }
    }
    else if(eTree->letter == '\0' && eTree->lChild == NULL)
    {
        return (eTree);
    }
    else if((eTree->lChild != NULL && eTree->lChild->letter != '\0') && eTree->rChild == NULL)
    {
        return (eTree);
    }
    else
    {
        temp = findNextPosition(eTree->lChild, eTree, 0);
        if(temp != NULL)
        { 
            return (temp);
        }
        else
        {
            if(eTree->letter == '\0') /* Denotes a possible available location to the right */
            {
                temp = findNextPosition(eTree->rChild, eTree, 1);
            }
            else
            {
                temp = findNextPosition(eTree->rChild, eTree, 0);
            }
            return (temp);
        }
    }
}
