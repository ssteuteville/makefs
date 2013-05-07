#ifndef _PARAMS_H_
#define _PARAMS_H_

#define FUSE_USE_VERSION 26
#define _XOPEN_SOURCE 500

#include <limits.h>
#include <stdio.h>
//create a data type the fuses private data will hold
struct make_state {
    char *root_dir;
};
//Define MAKE_DATA as athe file systems private data
#define MAKE_DATA ((struct make_state *) fuse_get_context()->private_data)

#endif