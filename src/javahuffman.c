/* javahuffman.c */

/*
 * Adam Reid
 * February 13, 2016
 */

#include <jni.h>
#include <stdio.h>
#include "arcompression_SubmitListener.h"
#include "huffman.h"

JNIEXPORT void JNICALL Java_arcompression_SubmitListener_compressFile
  (JNIEnv * env, jobject obj)
{
    encode("tests/test.txt");
}

JNIEXPORT void JNICALL Java_arcompression_SubmitListener_decompressFile
  (JNIEnv * env, jobject obj)
{
    decode("tests/test.txt");
}
