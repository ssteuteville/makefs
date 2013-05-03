makefs
======

A FUSE-based file system to essentially generate a Makefile based on the files of a specified directory. 

##As of now:
To generate a working Makefile:

    1) cd into the working directory
    2) gcc .driver.c
    3) ./a.out <desired CFLAGS> (no error checking so spell them correctly)
    
A Makefile and executable ("runnable") are generated. Can compile using g++/gcc; the driver determines this implicitly. The driver parses through a generated text file (executing ls -R > files.txt and then reading from it) containing the list of files in the directory, and the first .c/.cpp read determines whether CC = gcc or g++. make is executed at the end of the driver’s run.

We have yet to introduce FUSE to his new girlfriend.
