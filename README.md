makefs
======

A FUSE-based file system to essentially generate a Makefile based on the files of a specified directory. 

##As of now:
To generate a working Makefile:

    1) cd into the working directory
    2) gcc .driver.c
    3) ./a.out <desired CFLAGS> (no error checking so spell them correctly)
        Example: ./a.out -g -Wall -pedantic -O2 -Wextra (only ones supported so far)
        Example: ./a.out allf (same effect as above: enables all flags)

A Makefile and executable ("runnable") are generated. Can compile using g++/gcc; the driver determines this implicitly. The driver parses through a generated text file (executing ls -R > files.txt and then reading from it) containing the list of files in the directory, and the first .c/.cpp read determines whether CC = gcc or g++. make is executed at the end of the driver’s run.

##Our current filesystem (not finished):
USAGE: ./makefs [FUSE and MOUNT options] root_directory mountpoint:

    To test it:
    1) cd into makefs/src
    2) make
    3) ./makefs -f root_dir mount_dir
    5) open a new termminal window and start using the new filesystem. As you cause system calls
       to happen the first terminal will be notifying you.
    

