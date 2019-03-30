#include <iostream>
#include "helper.h"
#include "rules.h"
#include "monitor.h"
#include "list.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    std::string rootPathname = ".";         // Root directory
    int interval = 5;                       // Seconds
    std::string rulesPathname = "rules";    // Rules pathname

    parseCmdline(argc, argv, rootPathname, interval, rulesPathname);

    std::cout << "Root directory: " << rootPathname << std::endl;
    std::cout << "Scan Interval: " << interval << std::endl;
    std::cout << "Rules pathname: " << rulesPathname << std::endl;

    RulesData rulesData = parseRulesFile(rulesPathname);

    std::cout << "Rules:" << std::endl;
    for (int i = 0; i < rulesData.count; i++) {
        std::cout << rulesData.rules[i] << std::endl;
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

    treeNode.addChildren();
    TreeNode* childNode = treeNode.children[0];
    std::cout << *childNode << std::endl;
    std::cout << "Num children: " << treeNode.children.size() << std::endl;

    Tree myTree = Tree(rootPathname);
    myTree.printNodes();


    delete [] rulesData.rules;

    return 0;
}