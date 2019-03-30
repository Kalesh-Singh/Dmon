#ifndef DMON_ACTIONS_H
#define DMON_ACTIONS_H

#include <iostream>

/*
 * MAX_ARGS must be 1 greater than allowed number of ARGS to accomodate the ending
 * nullptr.
 */
#define MAX_ARGS 128

enum class ParseActionReturn {
    FG,
    BG,
    EMPTY,
    ERROR
};

typedef struct {
    std::string text;
    std::string delimJoinedText;
    std::string filepath;
    int argc;                 // Number of arguments
    char *argv[MAX_ARGS];     // Arguments list
    std::string infile;
    std::string outfile;
} Action;

/*
 * Parses the action string and fill out the Action object. Also, valid actions
 * are executed while invalid ones are reported to the user.
 */
int parseAction(const std::string &filepath,
                const std::string &actionStr,
                Action *action);

#endif //DMON_ACTIONS_H
