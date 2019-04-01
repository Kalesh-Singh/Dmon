//
// Created by kalesh on 3/28/19.
//

#ifndef DMON_MONITOR_H
#define DMON_MONITOR_H

//#include <iostream>
//#include <sys/stat.h>       // struct stat, stat
//#include <sys/types.h>      // opendir
//#include <dirent.h>         // opendir
//#include <limits.h>         // realpath
//#include <stdlib.h>         // realpath

//enum class PathType {
//    DIRECTORY,
//    FILE
//};

/*
 * Prints a path type
 */
//std::ostream &operator<<(std::ostream &out, const PathType &pathType);

/*

struct Node {
    std::string name;
    std::string basePath;
    std::string fullPath;
    PathType type;
    struct stat statBuffer;
    struct Node* parent;
    struct Node* children;
    int childCount;
};

//typedef struct Node Node;
*/
/*
 * Create and return Node for the given pathname.
 * NOTE: This cannot be used to get the root node.
 */
//Node getNode(std::string& pathname);

/*
 * Create and return the root node.
 * The pathname is expected to be the directory that dmon is monitoring.
 */
//Node getRootNode(std::string& pathname);



#endif //DMON_MONITOR_H
