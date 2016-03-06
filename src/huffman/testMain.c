/* testMain.c */

/*
 * Adam Reid
 * March 6, 2016
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
    if((argc == 3) && (strcmp(argv[1], "-d") == 0))
    {
        decode(argv[2]);
    }
    else if(((argc == 3) && (strcmp(argv[1], "-c") == 0)) || (argc == 2))
    {
        if(argc == 2)
        {
            encode(argv[1]);
        }
        else
        {
            encode(argv[2]);
        }
    }
    else
    {
        printf("Error: invalid arguments\n");
    }
    return(0);
}
