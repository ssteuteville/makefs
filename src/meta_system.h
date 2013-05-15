#ifndef META_SYSTEM_H
#define META_SYSTEM_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAX_FILE_NAME 35
#define MAX_FILES 30

/* ...:::add_meta:::...
# add_meta will add the file name at the end of a path to the meta data file.
# Expected format for both parameters dir/dir/dir/filename
# @param meta_path -- the path of the meta data.
# @param file_path -- the path to the file being added to meta data.
*/
void add_meta(char* meta_path, char* file_path);

/* ...:::change_filename:::...
# change_file name will take a path and change the file name that is at the end of it.
# This function is intended to make manipulating paths within makefs more bearable.
# @param path -- path to be edited. (dir/dir/dir/old_filename)
# @param filename  -- the name we are changing the filename to. (this isn't a path!)
# @return          -- the new path (dir/dir/dir/new_filename)
*/
char* change_filename(char* path, char* filename);

/* ...:::load_meta:::...
# This function will load the contents of the meta file into memory.
# @param list      -- The address of the array that the meta data will be loaded into.
# @param meta_path -- The path to the meta data. (dir/dir/dir/.files.txt)
# @return          -- The number of files loaded.
*/
int load_meta(char (*list)[MAX_FILES][PATH_MAX], char* meta_path);

/* ...:::remove_meta:::...
# This function will remove an entry from the meta data.
# @param meta_path    -- The path to the meta data.
# @param file_removed -- The file name to be removed from meta data.
*/
void remove_meta(char* meta_path, char* file_removed);

/* ...:::rename_meta:::...
# This function will change one of the entries in the meta data.
# @param meta_path    -- The path to the meta data.
# @param file_removed -- This is the entry that is going to be replaced.
# @param file_renamed -- This is what will replace file_removed.
*/
void rename_meta(char* meta_path, char* file_removed, char* file_renamed);

#endif META_SYSTEM_H