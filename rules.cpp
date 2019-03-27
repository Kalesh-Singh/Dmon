#include "rules.h"
#include <fstream>
#include <sstream>

/*
 * Returns a count of the number of rules in the rules file.
 */
int getRulesCount(const std::string& rulesPathname);

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 * @param ruleNum - line num of rule starting at 0
 */
void parseRule(const std::string& ruleStr, Rule* rules, int ruleNum);

/*
 * Prints a Rule
 */
std::ostream &operator<<(std::ostream &out, const Rule& rule) {
    out << "Event: " << rule.event
        << " Pattern: " << rule.pattern
        << " Action: " << rule.action
        << std::endl;
    return out;
}

/*
 * Parses the rule file and returns an array of
 * rule objects.
 */
Rule* parseRulesFile(std::string& rulesPathname) {
    int rulesCount = getRulesCount(rulesPathname);

    // Get the rule strings from the file.
    std::string ruleStrs[rulesCount];
    int ruleStrsIdx = 0;

    std::ifstream infile(rulesPathname);
    for (std::string line; std::getline(infile, line); ) {
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
    Rule* rules = new Rule[rulesCount];

    for (int i = 0; i < rulesCount; i++) {
        parseRule(ruleStrs[i], rules, i);
    }

    return rules;
}

/*
 * Parses the rule string into a Rule object.
 * If parsing fails, exits and prints invalid rule.
 * @param ruleNum - line num of rule starting at 0
 */
void parseRule(const std::string& ruleStr, Rule* rules, int ruleNum) {
    std::stringstream ss;
    ss << ruleStr;

    std::string eventStr;
    std::string patternStr;
    std::string actionStr;

    Rule* rule = rules + ruleNum;

    // Get the event
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
    std::getline(ss, actionStr);
}

/*
 * Returns a count of the number of rules in the rules file.
 */
int getRulesCount(const std::string& rulesPathname) {
    int rulesCount = 0;
    std::ifstream infile(rulesPathname);
    std::string line;

    for (std::string line; std::getline(infile, line); ) {
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


