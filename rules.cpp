#include "rules.h"
#include <fstream>
#include <sstream>

/*
 * Returns a count of the number of rules in the rules file.
 */
int getRulesCount(const std::string &rulesPathname);

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 * @param ruleNum - line num of rule starting at 0
 */
void parseRule(const std::string &ruleStr, Rule *rules, int ruleNum);

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
 * Parses the rule file and returns an array of
 * rule objects.
 */
RulesData parseRulesFile(std::string &rulesPathname) {
    int rulesCount = getRulesCount(rulesPathname);

    // Get the rule strings from the file.
    std::string ruleStrs[rulesCount];
    int ruleStrsIdx = 0;

    std::ifstream infile(rulesPathname);
    for (std::string line; std::getline(infile, line);) {
        std::istringstream iss(line);
        std::string firstToken;

        // Don't get empty lines and comments
        if (!(iss >> firstToken) || (firstToken[0] == '#')) {
            continue;
        }
        ruleStrs[ruleStrsIdx] = line;
        ruleStrsIdx++;
    }

    // Create the rule objects.
    Rule *rules = new Rule[rulesCount];

    for (int i = 0; i < rulesCount; i++) {
        parseRule(ruleStrs[i], rules, i);
    }

    return {rules, rulesCount};
}

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 * @param ruleNum - line num of rule starting at 0
 */
void parseRule(const std::string &ruleStr, Rule *rules, int ruleNum) {
    std::stringstream ss;
    ss << ruleStr;


    Rule *rule = rules + ruleNum;

    // Get the event
    std::string eventStr;
    ss >> eventStr;
    rule->event = getEvent(eventStr);

    if (rule->event == Event::UNKNOWN) {
        std::cerr << "Invalid Event: " << eventStr << std::endl;
        delete rules;   // Free memory for rules
        exit(1);
    }

    // Get the pattern
    ss >> rule->pattern;

    // Get the action
    std::string actionStr;
    std::getline(ss, actionStr);
    // NOTE: getline will also return the space(s) delimiting pattern and action.
    actionStr.erase(0, actionStr.find_first_not_of(" "));   // Remove trailing spaces
    rule->action = actionStr;
}

/*
 * Returns a count of the number of rules in the rules file.
 */
int getRulesCount(const std::string &rulesPathname) {
    int rulesCount = 0;
    std::ifstream infile(rulesPathname);
    std::string line;

    for (std::string line; std::getline(infile, line);) {
        std::istringstream iss(line);
        std::string firstToken;
        // Don't count empty lines and comments
        if (!(iss >> firstToken) || (firstToken[0] == '#')) {
            continue;
        }
        rulesCount++;
    }

    return rulesCount;
}
