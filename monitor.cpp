//
// Created by kalesh on 3/28/19.
//

#include "monitor.h"


Node getRootNode(std::string& pathname) {
    Node rootNode;

    // Get the name
    std::string name = pathname;
    int findIdx = name.find_last_of("/");
    if (findIdx != std::string::npos) {
        rootNode.name = name.erase(0, findIdx+1);
    } else {
        rootNode.name = name;
    }

    // Get the full path
    char *realPath = realpath(pathname.c_str(), NULL);
    std::string fullPathStr(realPath);
    rootNode.fullPath = fullPathStr;
    free(realPath);

    // Set the base path (Just the pathname in this case)
    rootNode.basePath = pathname;


    // TODO: Check stat to determine if it is a directory or not
    // NOTE: Might not even need the ItemType enum (but might still be useful in tree traversal) -- IFFY
    // If the root is not a directory then throw an error and exit.

    // Get the stats
    stat(rootNode.fullPath, &(rootNode.statBuffer);

    // Set the path type
    if (S_ISREG(rootNode.statBuffer.st_mode)) {
        rootNode.type = ItemType::DIRECTORY;
    } else {
        rootNode.type = ItemType::FILE;
    }

    // Set the parent
    rootNode.parent = nullptr;

    // Set the children
    rootNode.children = nullptr;

    // Set the children count
    rootNode.childCount = 0;

    std::cout << "Root node name: " << rootNode.name << std::endl;  // TODO: Delete
    std::cout << "Root full path : " << rootNode.fullPath << std::endl;  // TODO: Delete
    std::cout << "Root base path: " << rootNode.basePath << std::endl;  // TODO: Delete

    return rootNode;
}

std::ostream &operator<<(std::ostream &out, const PathType &pathType) {
    switch (pathType) {
        case PathType::FILE:
            out << "FILE";
            break;
        case PathType::DIRECTORY:
            out << "DIRECTORY";
            break;
        default:
            out << "UNKNOWN";
            break;
    }
    return out;
}

