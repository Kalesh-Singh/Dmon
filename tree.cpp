//
// Created by kalesh on 3/29/19.
//

#include "tree.h"
#include <algorithm>
#include <deque>

#define TREESERIALIZE
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
    for (int i = 0; i < treeNode->children.size(); i++) {
        delete (treeNode->children[i]);
    }
}

void TreeNode::serialize(TreeNode *treeNode) {
    if ( treeNode == nullptr ) {
        std::cout << "treeNode is null\n";
        return;
    }

    // Store to file here
    std::ofstream outFile;
    outFile.open("../tree.txt", std::ios::app);
    if ( outFile.is_open() ) {
        outFile << treeNode->basePath << std::endl;
        outFile.close();
        return;
    }

    puts("Error opening file!\n");
    return;

    /*
    FILE* fp = fopen("../tree.txt", "a");
    if ( fp == nullptr ) {
        puts("Could not open file\n");
        return;
    }
    fprintf(fp, "%s\n", treeNode->fullPath.c_str());
    fclose(fp);
    */
}

void TreeNode::printBasePath(TreeNode* treeNode) {
    std::cout << treeNode->basePath << std::endl;
    return;
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

// Overloaded Constructor so that I can create a node from received data from the 
// file
TreeNode::TreeNode(std::string location, TreeNode* parent) {
    this->basePath = location;
    this->parent = parent;
}

/************* TreeNode Public Methods ************/
void TreeNode::addChildren() {
    this->dirCheck();
    std::vector<std::string> paths = getChildrenPaths();
    for (std::string path : paths) {
        addChild(path);
    }
}

void TreeNode::postOrder(void (*visitFunction)(TreeNode *treeNode)) {
    for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->postOrder(visitFunction);
    }
    visitFunction(this);
}

// For the serialization
void TreeNode::preOrder(void (*visitFunction)(TreeNode* treeNode)) {
    visitFunction(this);
    for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->preOrder(visitFunction);
    }
    #if defined(TREESERIALIZE)
        // write the marker to denote that this node has no more children
        std::ofstream outFile;
        outFile.open("../tree.txt", std::ios::app);
        outFile << ")\n";
        return;
    #endif
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
/*
 * Returns the children paths in lexicographical order.
 */
std::vector<std::string> TreeNode::getChildrenPaths() {
    this->dirCheck();
    std::vector<std::string> paths;
    DIR *dir;
    struct dirent *dirStruct;
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
    // Ensure that the paths are sorted so that
    // the tree will be ordered
    std::sort(paths.begin(), paths.end());

    return paths;
}

void TreeNode::addChild(std::string &pathname) {
    TreeNode *treeNode = new TreeNode(pathname);
    treeNode->parent = this;
    children.push_back(treeNode);
}

void TreeNode::dirCheck() {
    if (type != PathType::DIRECTORY) {
        std::cerr << "Only DIRECTORIES can have children" << std::endl;
        exit(1);
    }
}

/****** Tree Constructor / Destructor *****/
Tree::Tree(std::string pathname) {
    root = new TreeNode(pathname);
    buildSubTree(root);
}

// Overload
Tree::Tree(TreeNode* thisRoot) {
    root = thisRoot;
}

Tree::~Tree() {
    this->postOrder(TreeNode::freeChildren);
    delete this->root;
}

/********* Tree Public Methods ***********/
void Tree::printNodes() {
    this->postOrder(TreeNode::printNode);
}

// For testing -> RUEL
void Tree::printBases() {
    this->preOrder(TreeNode::printBasePath);
}

void Tree::serialize() {
    this->preOrder(TreeNode::serialize);
}

/********* Tree Private Methods ***********/
void Tree::buildSubTree(TreeNode *node) {
    if (node->type == PathType::DIRECTORY) {
        node->addChildren();

        for (int i = 0; i < node->children.size(); i++) {
            TreeNode *childNode = node->children[i];
            buildSubTree(childNode);
        }
    }
}

void Tree::postOrder(void (*visitFunction)(TreeNode *treeNode)) {
    this->root->postOrder(visitFunction);
}

void Tree::preOrder(void (*visitFunction)(TreeNode* treeNode)) {
    this->root->preOrder(visitFunction);
}

// root is the root of the new tree being built
TreeNode* deSerialize() {

    std::ifstream inFile;
    inFile.open("../tree.txt", std::ios::in);

    
    FILE* fp = fopen("../tree.txt", "r");
    if ( fp == nullptr ) {
        puts("Could not open file\n");
        return nullptr;
    }

    TreeNode* root = nullptr;
    bool rootNull = true;
    TreeNode* currentNode = nullptr;

    std::string basePath;

    
    while ( inFile ) {
        inFile >> basePath;
        if ( basePath.compare(")") != 0 ) {
            if ( rootNull ) {
                rootNull = false;
                root = new TreeNode(basePath, nullptr);
                currentNode = root;
            }
            else {
                TreeNode* newNode = new TreeNode(basePath, currentNode);
                currentNode->children.push_back(newNode);
                currentNode = newNode;
            }
        }
        else {
            if ( currentNode->parent != nullptr ) {
                currentNode = currentNode->parent;
            }
        }
    }
    inFile.close();
    return root;
}