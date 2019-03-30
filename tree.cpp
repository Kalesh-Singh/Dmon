//
// Created by kalesh on 3/29/19.
//

#include "tree.h"

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

/*
 * Prints a Tree Node
 */
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

/*** TreeNode Traversal Functions *****/

void TreeNode::printNode(TreeNode *treeNode) {
    std::cout << *treeNode << std::endl;
}


void TreeNode::freeChildren(TreeNode *treeNode) {
    for (int i  = 0; i < treeNode->children.size(); i++) {
        delete (treeNode->children[i]);
    }
}

/*** TreeNode Constructor ***/
TreeNode::TreeNode(std::string pathname) {
    this->basePath = pathname;
    this->name = getName(pathname);
    this->fullPath = getFullPath(pathname);
    this->type = getType();
    this->timeStats = getTimeStats();
    this->parent = nullptr;
}

/************* TreeNode Public Methods ************/
void TreeNode::addChildren() {
    this->dirCheck();
    std::vector<std::string> paths = getChildrenPaths();
    for (std::string path : paths) {
        addChild(path);
    }
}

void TreeNode::postOrder(void (*visitFunction) (TreeNode* treeNode)) {
    for (int i = 0; i < this->children.size(); i++) {
        if (this->children[i]->type == PathType::DIRECTORY) {
            this->children[i]->postOrder(visitFunction);
        }
    }
    visitFunction(this);
}

/************* TreeNode Private Methods ***********/
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

std::vector<std::string> TreeNode::getChildrenPaths() {
    this->dirCheck();
    std::vector<std::string> paths;
    DIR* dir;
    struct dirent* dirStruct;
    dir = opendir(basePath.c_str());
    if (dir) {
        while ((dirStruct = readdir(dir)) != NULL) {
            std::string name(dirStruct->d_name);
            if ((name != ".") && (name != "..")) {
                paths.push_back(basePath + "/" + std::string(dirStruct->d_name));
            }
        }
        closedir(dir);
    }
    return paths;
}

void TreeNode::addChild(std::string& pathname) {
    this->dirCheck();
    TreeNode *treeNode = new TreeNode(pathname);
    treeNode->parent = this;
    children.push_back(treeNode);
}

/****** Tree Constructor / Destructor *****/
Tree::Tree(std::string pathname) {
    root = new TreeNode(pathname);
    buildSubTree(root);
}

Tree::~Tree() {
    this->postOrder(TreeNode::freeChildren);
    delete this->root;
}

/********* Tree Public Methods ***********/
void Tree::printNodes() {
    this->postOrder(TreeNode::printNode);
}

/********* Tree Private Methods ***********/
void Tree::buildSubTree(TreeNode* node) {
    if (node->type == PathType::DIRECTORY) {
        node->addChildren();

        for (int i = 0; i < node->children.size(); i++) {\
            TreeNode* childNode = node->children[i];
            buildSubTree(childNode);
        }
    }
}

void Tree::postOrder(void (*visitFunction) (TreeNode* treeNode)) {
    this->root->postOrder(visitFunction);
}


void TreeNode::dirCheck() {
    if (type != PathType::DIRECTORY) {
        std::cerr << "Only DIRECTORIES can have children" << std::endl;
        exit(1);
    }
}
