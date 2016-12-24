#include <jni.h>
#include <stdio.h>
#include "arcompression_SubmitListener.h"
#include "huffman.h"
JNIEXPORT void JNICALL Java_arcompression_SubmitListener_compressFile (JNIEnv * env, jobject obj, jstring path)
{
    encode(path);
}


JNIEXPORT void JNICALL Java_arcompression_SubmitListener_decompressFile (JNIEnv *, jobject, jstring);
{
    decode(path);
}
