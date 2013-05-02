makefs
======

A FUSE-based file system to essentially generate a Makefile based on the files of a specified directory. 

##As of now:
To generate a working Makefile:

    1) edit the paths in driver_cmd_args.c (several places) to point to the directory containing the to-be-compiled files
    2) gcc driver_cmd_args.c
    3) ./a.out <desired CFLAGS> (no error checking so spell them correctly)
    
Can compile using g++/gcc. The driver parses through a generated text file (executing ls -R > files.txt and then reading from it) containing the list of files in the directory, and the first .c/.cpp read determines whether CC = gcc or g++. make is executed at the end of the driver’s run and an executable called, “runnable,” is placed in the directory.

FUSE has yet to be associated with this beauty.
