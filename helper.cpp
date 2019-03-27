//
// Created by kalesh on 3/26/19.
//

#include "helper.h"
#include <iostream>

/*
 * Prints the usage of dmon
 */

void usage() {
    std::cout << "\nUsage: dmon [options] ROOT\n"
                 "\n"
                 "Options:\n"
                 "    -h          Prints this help message\n"
                 "    -f RULES    Load rules from this file (default is rules)\n"
                 "    -t SECONDS  Time between scans (default is 5 seconds)\n\n";
}
