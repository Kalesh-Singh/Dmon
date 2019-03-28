//
// Created by kalesh on 3/28/19.
//

#include "monitor.h"

Node getRootNode(std::string& pathname) {
    Node rootNode;

    std::string name = pathname;
    int findIdx = name.find_last_of("/");
    if (findIdx != std::string::npos) {
        rootNode.name = name.erase(0, findIdx+1);
    } else {
        rootNode.name = name;
    }

    std::cout << "Root node name: " << rootNode.name << std::endl;  // TODO: Delete

    return rootNode;
}
