#ifndef DMON_RULES_H
#define DMON_RULES_H

#include <iostream>
#include <vector>
#include "event.h"


typedef struct {
    EventType event;
    std::string pattern;
    std::string action;
} Rule;

/*
 * Parses the rule file and returns a vector
 * rule objects.
 */
std::vector<Rule> parseRulesFile(std::string &rulesPathname);

/*
 * Prints a Rule
 */
std::ostream &operator<<(std::ostream &out, const Rule &rule);

#endif //DMON_RULES_H
