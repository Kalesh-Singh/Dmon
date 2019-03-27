//
// Created by kalesh on 3/26/19.
//

#ifndef DMON_HELPER_H
#define DMON_HELPER_H

#include <iostream>

/*
 * Prints the usage of dmon
 */
void usage();

/*
 * Parses the command line and sets the rule, root, and interval.
 */
void parse_cmdline(int argc, char* argv[], std::string& root, int& interval, std::string& rules);

#endif //DMON_HELPER_H
