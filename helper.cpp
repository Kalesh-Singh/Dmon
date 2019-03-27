//
// Created by kalesh on 3/26/19.
//

#include "helper.h"

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

/*
 * Parses the command line and sets the rule, root, and interval.
 */
void parse_cmdline(int argc, char* argv[], std::string& root, int& interval, std::string& rules) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);   // Convert the char* arg to a std::string arg
        if (arg == "-h") {          // Help flag
            usage();
            exit(1);
        } else if (arg == "-t") {   // Interval flag
            if (++i == argc) {
                std::cerr << "Expected value following -t flag" << std::endl;
                usage();
                exit(1);
            }
            interval = std::stoi(argv[i], nullptr, 10);
            if (interval <= 0) {
                std::cerr << "Invalid interval - must be an integer >= 1" << std::endl;
                usage();
                exit(1);
            }
        } else if (arg == "-f") {   // Rules flag
            if (++i == argc) {
                std::cerr << "Expected value following -f flag" << std::endl;
                usage();
                exit(1);
            }
            rules = argv[i];
        } else {                    // Root directory
            root = argv[i];
        }
    }
}
