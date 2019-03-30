#include "actions.h"
#include <unistd.h>
#include <sstream>
#include <stdio.h>
#include <string.h>


/*
 * Executes valid actions and informs users of invalid ones.
 */
void executeAction(Action *action);

/*
 * Prints an action
 */
std::ostream &operator<<(std::ostream &out, const Action &action) {
    out << "Executing action \"" << action.text
        << "\" on \"" << action.filepath << "\"";
}

int parseAction(const std::string &filepath,
                const std::string &actionStr,
                Action *action) {
    // Copy the action string and filepath into the Action object.
    action->text = actionStr;
    action->delimJoinedText = actionStr;
    action->filepath = filepath;
    
    // Initialize ActionTokens default values.
    action->argc = 0;
    action->infile = "";
    action->outfile = "";
    
    // Declaring variables to be used for parsing.
    const char delims[] = " \t\r\n"; // white-space delimiters
    char *buf;                       // ptr to traverse the action string
    char *next;                      // ptr to the end of current arg
    char *endbuf;                    // ptr to end of action string

    char* actionText = const_cast<char*>(action->delimJoinedText.c_str());
    buf = actionText;
    endbuf = actionText + strlen(actionText);

    while (buf < endbuf) {
        // Skip the white-spaces.
        buf += strspn(buf, delims);
        if (buf >= endbuf) break;

        if (*buf == '\'' || *buf == '\"') {
            // Detect quoted tokens.
            buf++;
            next = strchr(buf, *(buf-1));
        } else {
            // Find next delimiter.
            next = buf + strcspn(buf, delims);
        }

        if (next == NULL) {
            // Means the closing quote was not found; Returned by strchr().
            std::cerr << "Unmatched " << *(buf-1) << ".\n";
            exit(1);
        }

        // Terminate the token.
        *next = '\0';
        
        // Record the token as next argument.
        if (strcmp(buf, "${FULLPATH}") == 0) {
            action->argv[action->argc] =
            const_cast<char*>(action->filepath.c_str());    
        } else {
            action->argv[action->argc] = buf;
        }
        (action->argc)++;

        // Check if argv is full. The last argument must be a NULL pointer. If
        // the argc is >= MAX_ARGS, there are more than allowed number of tokens
        // in the action string, thus exiting the process.
        if (action->argc >= MAX_ARGS) {
            std::cerr << "Action \"" << actionStr
                      << "\" has too many arguments";
            delete action; // Free memory for action.
            exit(1);
        }

        buf = next + 1;
    }

    action->argv[action->argc] = nullptr;
    executeAction(action);
}

void executeAction(Action *action) {
    int pid;
    pid = fork();
    if (pid == 0) {
        if (execve(action->argv[0], action->argv, environ) < 0) {
            perror("Error occurred!");
            std::cerr << "Action execution failed for \""
                      << action->filepath << "\"\n";
        }
        delete action; // Free memory for action.
        exit(1);
    }
}

