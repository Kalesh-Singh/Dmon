#include "rules.h"
#include <fstream>
#include <sstream>


/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 */
Rule parseRule(const std::string &ruleStr);

/*
 * Prints a Rule
 */
std::ostream &operator<<(std::ostream &out, const Rule &rule) {
    out << "EVENT: " << rule.event
        << "\t\tPATTERN: " << rule.pattern
        << "\t\tACTION: " << rule.action;
    return out;
}

/*
 * Parses the rule file and returns a vector of
 * rule objects.
 */
std::vector<Rule> parseRulesFile(std::string &rulesPathname) {
    std::vector<Rule> rules;
    std::ifstream infile(rulesPathname);
    for (std::string line; std::getline(infile, line);) {
        std::istringstream iss(line);
        std::string firstToken;

        // Don't get any empty line or comments
        if (!(iss >> firstToken) || (firstToken[0] == '#')) {
            continue;
        }

        Rule rule = parseRule(line);
        rules.push_back(rule);
    }

    return rules;
}

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 */
Rule parseRule(const std::string &ruleStr) {
    std::stringstream ss;
    ss << ruleStr;
    Rule rule;

    // Get the event
    std::string eventStr;
    ss >> eventStr;
    rule.event = getEvent(eventStr);
    if (rule.event == Event::UNKNOWN) {
        std::cerr << "Invalid Event: " << eventStr << std::endl;
        exit(1);
    }

    // Get the pattern
    ss >> rule.pattern;

    // Get the action
    std::string actionStr;
    std::getline(ss, actionStr);
    // NOTE: getline will also return the space(s) or tab(s) delimiting pattern and action.
    actionStr.erase(0, actionStr.find_first_not_of(" \t"));   // Remove trailing spaces / tabs
    rule.action = actionStr;

    return rule;
}
