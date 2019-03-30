//
// Created by kalesh on 3/29/19.
//

#include "tree.h"
#include <cstring>      // strcmp()

/****** Traversal Functions ***********/

void TreeNode::printNode(TreeNode *treeNode) {
    std::cout << *treeNode << std::endl;
}
/*void printNode(TreeNode* treeNode);
void freeChildren(TreeNode* treeNode);


void TreeNode::printNode(TreeNode* treeNode) {
    std::cout << *treeNode << std::endl;
}

void freeChildren(TreeNode* treeNode);

/*
 * Prints a PathType
 */
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
    }
    return out;
}

// TreeNode Methods

TreeNode::TreeNode(std::string pathname) {
    this->basePath = pathname;
    this->name = getName(pathname);
    this->fullPath = getFullPath(pathname);
    this->type = getType();
    this->timeStats = getTimeStats();
    this->parent = nullptr;
}

std::string TreeNode::getName(std::string &pathname) {
    std::string name = pathname;
    int findIdx = name.find_last_of("/");
    if (findIdx != std::string::npos) {
        name.erase(0, findIdx + 1);
    }
    return name;
}

std::string TreeNode::getFullPath(std::string &pathname) {
    char *realPath = realpath(pathname.c_str(), NULL);
    std::string fullPath(realPath);
    free(realPath);
    return fullPath;
}

PathType TreeNode::getType() {
    struct stat statBuffer;
    stat(fullPath.c_str(), &statBuffer);
    if (S_ISDIR(statBuffer.st_mode)) {
        return PathType::DIRECTORY;
    } else {
        return PathType::FILE;
    }
}

TimeStats TreeNode::getTimeStats() {
    struct stat statBuffer;
    stat(fullPath.c_str(), &statBuffer);
    return {statBuffer.st_atime, statBuffer.st_mtime, statBuffer.st_ctime};
}


void TreeNode::addChild(std::string& pathname) {
    if (type != PathType::DIRECTORY) {
        std::cerr << "Only DIRECTORIES can have children" << std::endl;
        exit(1);
    }
    TreeNode *treeNode = new TreeNode(pathname);
    treeNode->parent = this;
    children.push_back(treeNode);
}


std::ostream &operator<<(std::ostream &out, const TreeNode &treeNode) {
    out << "-------------------- Tree Node --------------------" << std::endl
        << "Name: " << treeNode.name << std::endl
        << "Base Path: " << treeNode.basePath << std::endl
        << "Full Path: " << treeNode.fullPath << std::endl
        << "Type: " << treeNode.type << std::endl
        << "Last Accessed: " << treeNode.timeStats.accessed << std::endl
        << "Last Modified: " << treeNode.timeStats.created << std::endl
        << "Created: " << treeNode.timeStats.created << std::endl
        << "---------------------------------------------------" << std::endl;
}

std::vector<std::string> TreeNode::getChildrenPaths() {
    std::vector<std::string> paths;
    DIR* dir;
    struct dirent* dirStruct;
    dir = opendir(basePath.c_str());
    if (dir) {
        while ((dirStruct = readdir(dir)) != NULL) {
            if (strcmp(dirStruct->d_name, ".") && strcmp(dirStruct->d_name, "..")) {
                paths.push_back(basePath + "/" + std::string(dirStruct->d_name));
            }
        }
        closedir(dir);
    }
    return paths;
}

void TreeNode::addChildren() {
    std::vector<std::string> paths = getChildrenPaths();
    for (std::string path : paths) {
        addChild(path);
    }
}

void Tree::buildSubTree(TreeNode* node) {
    if (node->type == PathType::DIRECTORY) {
        node->addChildren();

        for (int i = 0; i < node->children.size(); i++) {\
            TreeNode* childNode = node->children[i];
            buildSubTree(childNode);
        }
    }
}

Tree::Tree(std::string pathname) {
    root = new TreeNode(pathname);
    buildSubTree(root);
}

Tree::~Tree() {
    // TODO: Implementation

}

void TreeNode::postOrder(void (*visitFunction) (TreeNode* treeNode)) {
    for (int i = 0; i < this->children.size(); i++) {
        if (this->children[i]->type == PathType::DIRECTORY) {
            this->children[i]->postOrder(visitFunction);
        }
    }
    visitFunction(this);
}


void Tree::postOrder(void (*visitFunction) (TreeNode* treeNode)) {
    this->root->postOrder(visitFunction);
}

void Tree::printNodes() {
    this->postOrder(TreeNode::printNode);
}

