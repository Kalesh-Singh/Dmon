#include "helper.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    char* root = ".";       // Root directory
    int interval = 5;       // Seconds
    char* rules = "rules";  // Rules

    parse_cmdline(argc, argv, &root, &interval, &rules);

    printf("Root directory: %s\n", root);
    printf("Scan interval: %d seconds\n", interval);
    printf("Rules pathname: %s\n", rules);

    return 0;
}