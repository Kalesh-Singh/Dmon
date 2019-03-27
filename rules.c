#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"


rule_t rules[MAX_RULE_NUM];

int parse_rule(char* rule, rule_t* rule_obj);

rule_t* parse_rules_file(char* rules_file) {
    FILE *fptr;
    char rule[MAX_RULE_LENGTH];

    if ((fptr = fopen(rules_file, "r")) == NULL) {
        printf("Error opening rules file!");
        exit(1);
    }

    int rule_idx = 0;
    while (fgets(rule, MAX_RULE_LENGTH, fptr) != NULL) {
        parse_rule(rule, rules + rule_idx);
        rule_idx++;
    }

    fclose(fptr);
    return rules;
} 

// Parse the read rule into tokens that make up a rule_t object. If parsing
// fails, halt the program informing the user of the invalid rule.
int parse_rule(char* rule, rule_t* rule_obj) {
    char *token = strtok(rule, " ");

    // Parse the event token.
    if (strcmp(token, "CREATE") == 0) {
        rule_obj->event = CREATE;
    } else if (strcmp(token, "MODIFY") == 0) {
        rule_obj->event = MODIFY;
    } else if (strcmp(token, "DELETE") == 0) {
        rule_obj->event = DELETE;
    } else {
        // TODO: print the invalid rule.
        exit(1);    
    }

    // Parse the pattern token.
    char *pattern = strtok(NULL, " ");
    // TODO: print invalid rule if bad regex.
    rule_obj->pattern = pattern;

    // Parse the action token.
    char *action = strtok(NULL, "");
    // TODO: invalid action can be checked in the actions module.
    rule_obj->action = action;
    
    return 0;
}

