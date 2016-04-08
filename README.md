# ARCompression
###**File Compression GUI**

### Overview
ARCompression is a file compression program that uses an implementation of the Huffman encoding. 
It is coded mainly in C for the compression aspects, with Java used to implement a GUI interface for the program.
There is also a command line interface in C that has been implemented, and can be used instead of the GUI.

**Note:** 

1. Currently the Java GUI is not connected to the C compression algorithm, and it is because of this that users cannot compress files using the GUI.
2. Currently the decompress function is not fully implemented, meaning that users can only compress files using this program.
3. The programs current function only compresses text files. Future improvements involve adding compression for all types of files.

### Compilation
1. Build the entire project, linking the Java GUI to the C compression/decompression algorithm **(Not Implemented)**: 

   **make**

2. Build just the C version of the compression/decompression, implementing the program using a command line interface: 

   **make arcomp**
   
   Running this command will build the program into /bin/huffman/test
