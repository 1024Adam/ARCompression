/* huffman.h */

/*
 * Adam Reid
 * November 28, 2015
 */

#include <stdlib.h>
#include <string.h>

typedef struct Encoding
{
    char letter;
    int count;
    struct Chars * next; 
}
Encoding;

Encoding * addEncoding(Encoding * codes, Encoding * toAdd);
Encoding * removeEncoding(Encoding * codes, char to Remove);
Encoding * deleteEncoding(Encoding codes);
