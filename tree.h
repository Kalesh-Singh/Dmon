//
// Created by kalesh on 3/29/19.
//

#ifndef DMON_TREE_H
#define DMON_TREE_H

#include <iostream>
#include <sys/stat.h>   // struct stat, stat()
#include <sys/types>    // opendir()
#include <dirent.h>     // opendir()
#include <climits>      // realpath()
#include <cstdlib>      // realpath()

enum class PathType {
    DIRECTORY,
    FILE
};

/*
 * Prints a PathType
 */
std::ostream& operator<<(std::ostream &out, const PathType &pathType);


#endif //DMON_TREE_H
