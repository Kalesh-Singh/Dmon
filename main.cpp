#include <iostream>
#include "helper.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string root = ".";                 // Root directory
    int interval = 5;                       // Seconds
    std::string rules = "rules";            // Rules pathname

    std::cout << "Root directory: " << root << std::endl;
    std::cout << "Scan Interval: " << interval << std::endl;
    std::cout << "Rules pathname: " << rules << std::endl;

    usage();

    return 0;
}