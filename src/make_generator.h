#ifndef MAKE_GENERATOR_H
#define MAKE_GENERATOR_H

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

bool correct_type(char* meta_data, char* filename);
void add_meta(char* meta_data, char* filename); 

#endif