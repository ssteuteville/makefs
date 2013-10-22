Note: This was my first time ever working in c and I'm aware that there are currently memory issues in the code.

MAKEFS
======

A [FUSE](http://fuse.sourceforge.net/)-based file system to essentially generate a Makefile based on the files of a specified directory. Fire up the file system, create a project, and automatically have a Makefile generated for your project!

* status: building

###Getting Started:

     1. Set up your system for use with fuse file systems. This includes setting up proper permissions and group settings. 
          A good example can be found here: https://help.ubuntu.com/community/FuseSmb
     2. Download the src directory from our repo and cd into it using bash. type make.
     3. Create two directories within src to represent the root directory and mountpoint.
          The root directory is the actual location where your file system writes and reads data.   
          The mountpoint is the directory used to work in the file system.
     4. cd into the src directory and type: ./makefs <fuse/mount options> root_dir mountpoint
     5. Your file system should now be running.
    
###Detailed usage:

##Usage:

     ./makefs [FUSE and MOUNT options] root_directory mountpoint        
     root_directory will be accessed through mountpoint. 
     makefs' functionality applies to anything created within mountpoint
     
     Known bugs:
     1. Run makefs in the foreground otherwise removing/renaming files in your project breaks it.
          Example: ./makefs -f root_directory mountpoint
     

     1. Once you have your file system up and running type: mkdir to create a directory for your project.
     2. cd into this directory and type: touch <filename> to create a couple file.
     A project may consist of (.c's and .h's) or (.cpp's and .h's) files.
     3. Once you are done type one of these options: 
          touch Makefile to create a Makefile with no CFLAGS
          touch Makefile.CFLAG1.CFLAG2.CFLAG3, etc. to create a Makefile with optional CFLAGS
          touch Makefile.allf to create a Makefile with all supported CFLAGS
     Current supported CFLAGS: -g -Wall -pedantic -O2 -Wextra
     4. Type: make and viola, you have an executable named after the directory and a Makefile.

###Usage Examples:

* touch Makefile.-g.-Wall.-pedantic
* touch Makefile.allf
* touch Makefile

=

####Generating a Makefile without using FUSE:

    1) cd into the working directory
    2) Compile .driver.c (found in this repo): gcc .driver.c
    3) Run the driver: ./a.out <desired CFLAGS> (no error checking so spell them correctly)
        Example: ./a.out -g -Wall -pedantic -O2 -Wextra (only ones supported so far)
        Example: ./a.out allf (same effect as above: enables all flags)

A Makefile and executable ("runnable") are generated in the working directory. Can compile using g++/gcc; the driver determines this implicitly. The driver parses through a generated text file (executing ls -R > files.txt and then reading from it) containing the list of files in the directory, and the first .c/.cpp read determines whether CC = gcc or g++. make is executed at the end of the driver’s run.
