#ifndef DMON_RULES_H
#define DMON_RULES_H

#include <iostream>
#include "event.h"


typedef struct {
    Event event;
    std::string pattern;
    std::string action;
} Rule;

/*
 * Parses the rule file and returns an array of
 * rule objects.
 */
Rule* parseRulesFile(std::string& rulesPathname);

/*
 * Prints a Rule
 */
std::ostream &operator<<(std::ostream &out, const Rule& rule);

#endif //DMON_RULES_H
