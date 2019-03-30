//
// Created by kalesh on 3/29/19.
//

#ifndef DMON_TREE_H
#define DMON_TREE_H

#include <iostream>
#include <sys/stat.h>   // struct stat, stat()
//#include <sys/types.h>  // opendir()
#include <dirent.h>     // opendir()
//#include <climits>      // realpath()
#include <cstdlib>      // realpath()
#include <ctime>        // time_t
#include <vector>       // vector
#include "list.h"       // List

enum class PathType {
    DIRECTORY,
    FILE
};

/*
 * Prints a PathType
 */
std::ostream &operator<<(std::ostream &out, const PathType &pathType);

struct TimeStats {
    time_t accessed;
    time_t modified;
    time_t created;
};

class TreeNode {
public:
    // Constructors
    TreeNode(std::string pathname);

    // Destructor -- Tree class will handle destruction

    // Modifiers
    void addChildren();     // Only if DIR

    // Output
    friend std::ostream &operator<<(std::ostream &out, const TreeNode &treeNode);


    // Member variables
    std::string name;           // Name of file of directory
    std::string basePath;       // Path from execution
    std::string fullPath;       // Absolute path
    PathType type;              // Type (FIlE or DIRECTORY)
    TimeStats timeStats;        // Accessed, Modified, Created
    TreeNode *parent;           // Parent directory
    List<TreeNode *> children;    // Should be empty for FILE
private:
    std::string getName(std::string &pathname);
    std::string getFullPath(std::string &pathname);
    PathType getType();         // Expected to be called after full path is set
    TimeStats getTimeStats();   // Expected to be called after full path is set
    void addChild(std::string& pathname);           // Only if DIR
    std::vector<std::string> getChildrenPaths();    // Only if DIR

};


#endif //DMON_TREE_H
