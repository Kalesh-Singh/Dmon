#ifndef RULES_H_
#define RULES_H_


enum Event{CREATE, MODIFY, DELETE, UNKNOWN};

typedef struct
{
    Event event;
    char* pattern;
    char* action;
} Rule;

Rule[] parse_file(char* rules_file);


#endif // RULES_H_
