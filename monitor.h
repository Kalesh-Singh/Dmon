//
// Created by kalesh on 3/28/19.
//

#ifndef DMON_MONITOR_H
#define DMON_MONITOR_H

#include <iostream>
#include <sys/stat.h>

enum class ItemType {
    DIRECTORY,
    FILE
};

struct Node {
    std::string name;
    std::string basePath;
    std::string absPath;
    ItemType type;
    struct stat statBuffer;
    struct Node* children;
    int childCount;
};

typedef struct Node Node;


#endif //DMON_MONITOR_H
