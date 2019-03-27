#ifndef RULES_H_
#define RULES_H_

#define MAX_RULE_NUM 100
#define MAX_RULE_LENGTH 1024


typedef enum{CREATE, MODIFY, DELETE} event_t;

typedef struct
{
    event_t event;
    char* pattern;
    char* action;
} rule_t;

extern rule_t rules[];

rule_t* parse_rules_file(char* rules_file);


#endif // RULES_H_
