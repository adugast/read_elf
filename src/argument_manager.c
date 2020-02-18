#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "argument_manager.h"


static void print_usage(const char *binary_name)
{
    printf("Usage: %s [params] <elf-file>\n", binary_name);
    printf("Available params:\n");
    printf(" -a, --all              : Equivalent to: -h -l -S\n");
    printf(" -h, --file-header      : Display the ELF file header\n");
    printf(" -l, --program-headers: : Display the program headers\n");
    printf(" -S, --section-headers  : Display the sections headers\n");
    printf(" -H, --help             : Display this help and exit\n");
    printf(" -v, --version          : Show version information\n");
}


static void print_version()
{
    printf("readelf64: version \?.\?.\?\?(\?)-release\n");
    printf("Own version of readelf for 64bit elf files\n");
    printf("Copyright (C) 2018 adugast\n");
    printf("MIT License: <https://opensource.org/licenses/MIT>\n");
    printf("Git Repository: <https://github.com/adugast/readelf64>\n");
    printf("\n");
    printf("This is free software; you are free to change and redistribute it.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n");
}


static void set_default_configuration(struct argument *args)
{
    memset(args->file, 0, FILENAME_SIZE);
    args->ehdr_flag = false;
    args->phdr_flag = false;
    args->shdr_flag = false;
}


void argument_manager(int argc, char *argv[], struct argument *args)
{
    set_default_configuration(args);

    static struct option long_options[] = {
        {"all",             no_argument, 0, 'a'},
        {"file-header",     no_argument, 0, 'h'},
        {"program-headers", no_argument, 0, 'l'},
        {"section-headers", no_argument, 0, 'S'},
        {"help",            no_argument, 0, 'H'},
        {"version",         no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    const char *option_string = "ahlSHv";
    int c;
    while ((c = getopt_long(argc, argv, option_string, long_options, NULL)) != -1) {
        switch (c) {
            case 'a': {
                          args->ehdr_flag = true;
                          args->phdr_flag = true;
                          args->shdr_flag = true;
                          break;
                      }
            case 'h': args->ehdr_flag = true; break;
            case 'l': args->phdr_flag = true; break;
            case 'S': args->shdr_flag = true; break;
            case 'H': print_usage(argv[0]); exit(EXIT_SUCCESS);
            case 'v': print_version(); exit(EXIT_SUCCESS);
            default: print_usage(argv[0]); exit(EXIT_SUCCESS);
        }
    }

    if (argv[optind] != NULL)
        strncpy(args->file, argv[optind], FILENAME_SIZE);
    else {
        print_usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
}

