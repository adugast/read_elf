#ifndef __ARGUMENT_MANAGER_H__
#define __ARGUMENT_MANAGER_H__


#include <stdbool.h>

#define FILENAME_SIZE 256

struct argument {
    char file[FILENAME_SIZE];
    bool ehdr_flag;
    bool phdr_flag;
    bool shdr_flag;
};


void argument_manager(int argc, char **argv, struct argument *args);


#endif /* __ARGUMENT_MANAGER_H__ */
