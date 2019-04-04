//
// Created by kalesh on 3/28/19.
//

#include "monitor.h"

/*
 * Compares two trees and populates the events vector.
 */
Index detect(TreeNode* prevTree, TreeNode* currTree, std::vector<Event>* events) {
    int prevSize = prevTree->children.size();
    int currSize = currTree->children.size();

    for (int i = 0, j = 0; i < prevSize && j < currSize; i++, j++) {
        Index index = detect(prevTree->children[i], currTree->children[j], events);
        if (index == Index::PREV) { // Only increment prev index (i)
            j--;      // Keep curr index (j) the same
        } else if (index == Index::CURR) {  // Only increment curr index (j)
            i--;      // Keep prev index (i) the same.
        }
        // Else increment both
    }

    // We need to be able to reach into the previous stack and manipulate i and j
    // in order to keep the comparison in sync. This is why detect returns an Index.

    // This is the "Visit Function"

    if (prevTree->name == currTree->name) {         // Same Node
        // Check for modification
        if (prevTree->timeStats.modified < currTree->timeStats.modified) {
            std::cout << "MODIFIED: " << prevTree->fullPath << std::endl;
        }
        return Index::BOTH;
    } else if (prevTree->name < currTree->name) {   // prevTree node deleted
        std::cout << "DELETED: " << prevTree->fullPath << std::endl;
        return Index::PREV;
        // TODO: Handle nesting if DIR
    } else {                                        // currTree node created
        std::cout << "CREATED: " << currTree->fullPath << std::endl;
        return Index::CURR;
        // TODO: Handle nesting if DIR
    }


}

