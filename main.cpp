#include <iostream>
#include "helper.h"
#include "rules.h"
#include "actions.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    std::string root = ".";                 // Root directory
    int interval = 5;                       // Seconds
    std::string rulesPathname = "rules";    // Rules pathname

    parseCmdline(argc, argv, root, interval, rulesPathname);

    std::cout << "Root directory: " << root << std::endl;
    std::cout << "Scan Interval: " << interval << std::endl;
    std::cout << "Rules pathname: " << rulesPathname << std::endl;

    RulesData rulesData = parseRulesFile(rulesPathname);

    std::cout << "Rules:" << std::endl;
    for (int i = 0; i < rulesData.count; i++) {
        std::cout << rulesData.rules[i] << std::endl;
    }

//    delete rulesData.rules;         // Free the memory allocated for rules
    std::string a = "/bin/echo path = ${FULLPATH}";
    Action *newaction = new Action();
    parseAction("temp.cpp", a, newaction);

    std::string b = "/bin/cat ${FULLPATH}";
    Action *newaction2 = new Action();
    parseAction("main.cpp", b, newaction2);
    return 0;
}
