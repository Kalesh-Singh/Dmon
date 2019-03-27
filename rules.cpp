#include "rules.h"
#include <fstream>
#include <sstream>

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 */
void parseRule(std::string& ruleStr, Rule* rule) {
    std::stringstream ss;
    ss << ruleStr;

    std::string eventStr;
    std::string patternStr;
    std::string actionStr;

}



