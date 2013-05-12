#ifndef MAKE_GENERATOR_H
#define MAKE_GENERATOR_H

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#define max_files 50

/* ...:::correct_type:::...
# This function will loop through the meta data file and search for the first 
# .c or .cpp to determine which type is correct.
# @param meta_path -- the path where the meta data is kept
# @param file_path -- the path where the new file is
# @return -- true if the new file matches the correct file type
*/
bool correct_type(char* meta_path, char* file_path);

/* ...:::add_meta:::...
# This function will add the new file name to the meta data file
# @param meta_path -- the file to be written to
# @param file_path -- the path that contains the filename being written
*/
void add_meta(char* meta_path, char* file_path);

/* ...:::get_meta_path:::...
# This function will return the path to the meta file we need
# @param new_file_path -- the path to the file being worked on
# @return the path to the meta file we need.
*/ 
char* get_meta_path(char* new_file_path);

/* ...:::make_gen:::...
# This function will create a make file. It uses various helper functions.
# @param file_path -- the unparsed path to the makefile being created
# @return true on success false on failure
*/
bool make_gen(char* file_path);

/* ...:::get_make_path:::...
# much like get meta path except it returns a path to a makefile instead.
# @param makefile_name -- the path to a file in the cwd
# @return the path to a makefile
*/
char* get_make_path(char* makefile_name);

/* ...:::get_cflags:::...
# This function takes an unparsed list of flags in the format .flag1.flag2.flag3 and
# produces a parsed char* representation of it.
# @param init_flags -- the unparsed list mentioned above.
# @return a ready to concatenate char*
*/
char* get_cflags(char* init_flags);

/* ...:::load_meta:::...
# This function will take a meta file and load it into memory (an array)
# @param list -- a list of strings by reference. This list will be populated when function finishes.
# @param meta_path -- the path to the meta data file
# @param mode -- 0 = don't determine compiler 1 = determine compiler
# @return this function will return "" if mode = 0
# it will return either "gcc" or "g++" otherwise
*/
char* load_meta(char (*list)[max_files][PATH_MAX], char* meta_path, int mode);
#endif