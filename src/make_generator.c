#include "make_generator.h"

bool correct_type(char* meta_data, char* filename) 
{
    /*
    char file_in_meta[PATH_MAX];
    while (fgets(file_in_meta, PATH_MAX, meta_data) != NULL)
        compare file_in_meta (each file in .files.txt) with filename
        i.e. "touch abc.c" compare with foo.c -- since both are .c files
        break, call add_meta (back from makefs.c), and return true. Upon 
        first occurance of a .cpp compared with a .c, return false.
    }
    if EOF and no .c/.cpp file is found, return true. Call add_meta 
    (back from makefs.c)     
    */
}

void add_meta(char* meta_data, char* filename) 
{
    /* 
    Function to append (use mode "a") filename to meta-data
    */
}
