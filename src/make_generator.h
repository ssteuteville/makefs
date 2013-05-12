#ifndef MAKE_GENERATOR_H
#define MAKE_GENERATOR_H

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#define max_files 50

bool correct_type(char* meta_path, char* file_path);
void add_meta(char* meta_path, char* file_path); 
char* get_meta_path(char* new_file_path);
bool make_gen(char* file_path);
char* get_make_path(char* makefile_name);
char* get_cflags(char* init_flags);
char* load_meta(char (*list)[max_files][PATH_MAX], char* meta_path, int mode);
#endif