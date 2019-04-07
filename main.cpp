#include <iostream>
#include "helper.h"
#include "rules.h"
#include "monitor.h"
#include "list.h"
#include "tree.h"
#include "actions.h"
#include <unistd.h>

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

    while (true) {
        currTree = (new Tree(rootPathname))->getRoot();
        if (prevTree != nullptr) {
            std::vector<Event> events;
            detect(prevTree, currTree, &events);
            for (Event event : events) {
                std::cout << event << std::endl;
            }
            delete prevTree;
        }
        usleep(interval * 1000);
        prevTree = currTree;
    }

    return 0;
}
