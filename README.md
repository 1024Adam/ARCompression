# Arc
###**File Compression Program**

### Overview
Arc is a file compression program that uses an implementation of the Huffman encoding. 
It is coded mainly in C for the compression aspects, with Java used to implement a GUI interface for the program.
There is also a command line interface in C that has been implemented, and can be used instead of the GUI.

**Note:** 

1. Currently the Java GUI is not connected to the C compression algorithm, and it is because of this that users cannot compress files using the GUI.
2. Currently the decompress function is not fully implemented, meaning that users can only compress files using this program.
3. The programs current function only compresses text files. Future improvements involve adding compression for all types of files.

### Building the Project
1. Build the entire project, linking the Java GUI to the C compression/decompression algorithm (Not Implemented): 

   make

2. Build just the C version of the compression/decompression, implementing the program using a command line interface:

   make arcomp
   
   Running this command will build the program into /bin/huffman/arc

### Running the Project
1. Run the full C/Java GUI version of the program (Not Implemented):

   No command is available for this feature at this time.

2. Run just the command line version of the program:

   bin/huffman/arc
   
   Command line arguments:
   
   The command line version of the program takes in at least **2** command line arguments:
    1. The command itself (bin/huffman/arc)
    2. The file to be compressed
    
   The program also accepts flags, in order to implement both the compression and decompression
   aspects of the program. These flags are as follows:
   ```
   (default, no flags) : Compress the file
   -c                  : Compress the file
   -d                  : Decompress the file
   ```
