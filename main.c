#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* root = ".";       // Root directory
    int interval = 5;       // Seconds
    char* rules = "rules";  // Rules

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {           // Help flag
            // TODO: Print usage
            printf("Usage: .... TODO\n");
            exit(1);
        } else if (!strcmp(argv[i], "-t")) {    // Interval flag
            if ((interval = (int) strtol(argv[++i], NULL, 10)) <= 0) {
                // TODO: Invalid interval
                printf("Invalid interval!\n");
                exit(1);
            }
        } else if (!strcmp(argv[i], "-f")) {    // Rules flag
            rules = argv[++i];
        } else {                                // Root directory
            root = argv[i];
        }
    }

    printf("Root directory: %s\n", root);
    printf("Scan interval: %d seconds\n", interval);
    printf("Rules pathname: %s\n", rules);

    return 0;
}