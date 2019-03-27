//
// Created by Kaleshwar Singh on 2019-03-25.
//

#include "helper.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage() {
    printf("\nUsage: dmon [options] ROOT\n"
           "\n"
           "Options:\n"
           "    -h          Prints this help message\n"
           "    -f RULES    Load rules from this file (default is rules)\n"
           "    -t SECONDS  Time between scans (default is 5 seconds)\n\n");
}

void parse_cmdline(int argc, char* argv[], char** root, int* interval, char** rules) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {           // Help flag
            usage();
            exit(1);
        } else if (!strcmp(argv[i], "-t")) {    // Interval flag
            if (++i == argc) {
                fprintf(stderr, "Excepted value for flag -t\n");
                usage();
                exit(1);
            }
            if ((*interval = (int) strtol(argv[i], NULL, 10)) <= 0) {
                fprintf(stderr, "Invalid interval!\n");
                usage();
                exit(1);
            }
        } else if (!strcmp(argv[i], "-f")) {    // Rules flag
            if (++i == argc) {
                fprintf(stderr, "Expected value for flag -f\n");
                usage();
                exit(1);
            }
            *rules = argv[i];
        } else {                                // Root directory
            *root = argv[i];
        }
    }
}