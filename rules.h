#ifndef DMON_RULES_H
#define DMON_RULES_H

#include <iostream>
#include "event.h"

typedef struct {
    Event event;
    std::string pattern;
    std::string action;
} Rule;

Rule* parseRuleFile(std::string& ruleFile);

// TODO: Delete
int getNumRules(const std::string& rulesPathname);

#endif //DMON_RULES_H
