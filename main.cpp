#include <iostream>
#include "helper.h"
#include "rules.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    std::string root = ".";                 // Root directory
    int interval = 5;                       // Seconds
    std::string rules = "rules";            // Rules pathname

    parseCmdline(argc, argv, root, interval, rules);

    std::cout << "Root directory: " << root << std::endl;
    std::cout << "Scan Interval: " << interval << std::endl;
    std::cout << "Rules pathname: " << rules << std::endl;

    std::cout << "Rules count: " << getNumRules("rules") << std::endl;
    std::cout << "Get event: " << (int) getEvent("CREATE") << std::endl;

    return 0;
}