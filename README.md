makefs
======

A FUSE file system that will create your makefiles for you!!!!

In the intial phases of design. This is our first file system so we are figuring out what will be necessary to make
make this work.

QUESTIONS WE NEED TO ANSWER
====================================
Are we going to have the fs create the makefiles as we create new files?
OR
Are we going generate the makefiles on command? 

How are we going to get the directory name and file names from the system?
  Which fuse functions?

IDEAS
======================================
The makefiles could be hidden
We could over load "touch" to update the makefile.
  Adam's idea: 'touch make.o.g.Pendantic' would make an executable using the compiler command -o -g -Pendantic
  
