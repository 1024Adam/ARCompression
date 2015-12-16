/* treeQueue.c */

/*
 * Adam Reid
 * December 15, 2015
 */

#include "treeQueue.h"

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

