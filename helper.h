#ifndef DMON_HELPER_H
#define DMON_HELPER_H

#include <iostream>

/*
 * Parses the command line and sets the rule, root, and interval.
 */
void parseCmdline(int argc, char **argv, std::string &root, int &interval, std::string &rules);

#endif //DMON_HELPER_H
