/* testMain.c */

/*
 * Adam Reid
 * December 13, 2015
 */

#include <stdio.h>
#include <time.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
    encode(argv[1]);
    return(0);
}
