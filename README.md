MAKEFS
======

A FUSE-based file system to essentially generate a Makefile based on the files of a specified directory. Fire up the file system, create a project, automatically have makefiles generated for your project!

##Our current filesystem (not finished):
Overview:

     usage: ./makefs [FUSE and MOUNT options] root_directory mountpoint
     root_directory will be accessed through mountpoint. 
     makefs's functionality applies to anything created within mountpoint
     More usage and set up details below.

Getting Started:

    1)set up your system for use with fuse file systems. This includes setting up proper permissions and group settings.
    A good example can be found here: https://help.ubuntu.com/community/FuseSmb
    Note: I am in no way affiliated with FuseSmb. 
    The thread I linked just has valuable information to help set up any fuse file system.
    2)Download the src directory from our repo and cd into it using bash. type make.
    3)Choose your montpoint and root directory.
    The root directory is the actual location where your file system writes and reads data.
    Mountpoint is the directory you enter to work in the file system.
    4)Using bash cd into the src directory and type:
    ./makefs root_dir mountpoint (all fuse and mounting options are supported)
    5)Your file system should now be running.
    
Detailed usage:

    Once you have your file system up and running creating makefile becomes simple.
    Cd into a directory. Create a project within the directory.
    A project may consist of (.c and .h) or (.cpp and .h) files.
    Once you are done type touch Makefile.flag1.flag2.flag3 to create a Makefile.
    Now just type make and viola, you have an executable named after the directory.

Usage Examples:

    Example: Custom Flags (not yet supported)
    touch Makefile.-g.-Wall.-pedantic
    Example: N9 Flags
    touch Makefile
    Example: allf <-g -Wall -pedantic -O2 -Wextra>
    touch Makefile.allf

##driver.c found in the testing directory:
To generate a working Makefile:

    1) cd into the working directory
    2) gcc .driver.c
    3) ./a.out <desired CFLAGS> (no error checking so spell them correctly)
        Example: ./a.out -g -Wall -pedantic -O2 -Wextra (only ones supported so far)
        Example: ./a.out allf (same effect as above: enables all flags)

A Makefile and executable ("runnable") are generated. Can compile using g++/gcc; the driver determines this implicitly. The driver parses through a generated text file (executing ls -R > files.txt and then reading from it) containing the list of files in the directory, and the first .c/.cpp read determines whether CC = gcc or g++. make is executed at the end of the driver’s run.
