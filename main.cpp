#include <iostream>
#include "helper.h"
#include "rules.h"
#include "monitor.h"
#include "list.h"
#include "tree.h"
#include "actions.h"
#include <unistd.h>

#define MICROSECONDS_CONST 1000000

// Macros for testing serializing/deserialization tree

#define SERIALIZE
#define DESERIALIZE


int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;


    std::string rootPathname = ".";         // Root directory
    int interval = 5;                       // Seconds
    std::string rulesPathname = "rules";    // Rules pathname

    parseCmdline(argc, argv, rootPathname, interval, rulesPathname);
/*
    std::cout << "Root directory: " << rootPathname << std::endl;
    std::cout << "Scan Interval: " << interval << std::endl;
    std::cout << "Rules pathname: " << rulesPathname << std::endl;

    std::vector<Rule> rules = parseRulesFile(rulesPathname);

    std::cout << "Rules:" << std::endl;
    for (int i = 0; i < rules.size(); i++) {
        std::cout << rules[i] << std::endl;
    }

    List<int> myList = List<int>();
    std::cout << myList << std::endl;
    myList.pop_front();
    std::cout << myList << std::endl;
    myList.pop_back();
    std::cout << myList << std::endl;

    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);

    std::cout << myList << std::endl;
    myList.pop_back();
    std::cout << myList << std::endl;
    myList.push_back(4);
    std::cout << myList << std::endl;
    myList.pop_front();
    std::cout << myList << std::endl;
    myList.push_front(1);
    std::cout << myList << std::endl;
    std::cout << myList[0] << std::endl;

    TreeNode treeNode = TreeNode(rootPathname);
    std::cout << treeNode << std::endl;

    Tree myTree = Tree(rootPathname);
    myTree.printNodes();

    std::string a = "/bin/echo path = ${FULLPATH}";
    Action *newaction = new Action();
    parseAction("temp.cpp", a, newaction);


    std::string b = "/bin/cat ${FULLPATH}";
    Action *newaction2 = new Action();
    parseAction("main.cpp", b, newaction2);
    */

    TreeNode* prevTree = nullptr;
    TreeNode* currTree = nullptr;

    Tree* ruelTree = new Tree(rootPathname);

    std::vector<Event> events;

    while (true) {
        currTree = (new Tree(rootPathname))->getRoot();
        if (prevTree != nullptr) {
            detect(prevTree, currTree, &events);
            delete prevTree;
        }
        // usleep takes microseconds, not milliseconds thus constant 
        // to multiply is 10^6 not 10^3
        // usleep(interval * 1000);
        usleep(interval * MICROSECONDS_CONST);
        prevTree = currTree;

        #if defined(SERIALIZE)
            // Just to clear the contents of the file before
            std::ofstream outFile;
            outFile.open("../tree.txt", std::ios::out);
            outFile.close();
            ruelTree->serialize();
        #endif

        #if defined(DESERIALIZE)
            // deserialize(prevTree) Something like this
            TreeNode* ruelTreeNode = nullptr;
            ruelTreeNode = deSerialize();
            Tree* testTree = new Tree(ruelTreeNode);
            testTree->printBases();
        #endif


    }
    return 0;
}
