#include "rules.h"
#include <fstream>
#include <sstream>

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 */
void parseRule(const std::string& ruleStr, Rule* rule) {
    std::stringstream ss;
    ss << ruleStr;

    std::string eventStr;
    std::string patternStr;
    std::string actionStr;

    // Get the event
    ss >> eventStr;
    rule->event = getEvent(eventStr);

    // Get the pattern
    ss >> rule->pattern;

    // Get the action
    std::getline(ss, actionStr);
}

int getNumRules(const std::string& rulesPathname) {
    int rulesCount = 0;
    std::ifstream infile(rulesPathname);
    std::string line;

    while(std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string firstToken;
        if (!(iss >> firstToken) || (firstToken == "#")) {
            continue;
        }
        rulesCount++;
    }
    return rulesCount;
}



