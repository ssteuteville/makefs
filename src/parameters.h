#ifndef _PARAMS_H_
#define _PARAMS_H_

#define FUSE_USE_VERSION 26
#define _XOPEN_SOURCE 500

#include <limits.h>
#include <stdio.h>
struct make_state {
    char *root_dir;
};
#define MAKE_DATA ((struct make_state *) fuse_get_context()->private_data)

#endif