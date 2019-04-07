//
// Created by kalesh on 3/28/19.
//

#include "monitor.h"

/*
 * Adds all the leaves fo the tree as the event specified to the events list.
 */
void addLeaves(TreeNode *tree, EventType type, std::vector<Event> *events);

/*
 * Compares two trees and populates the events vector.
 */
Index detect(TreeNode *prevTree, TreeNode *currTree, std::vector<Event> *events) {
    // This is the "Visit Function"
    if (prevTree->name == currTree->name) {         // Same Node
        // Check for modification
        // We can skip over the entire subtree if the root node of
        // that subtree does not reflect any modification.
        if (prevTree->type == PathType::DIRECTORY) {
            // We need to be able to reach into the previous stack and manipulate i and j
            // in order to keep the comparison in sync. This is why detect() returns an Index.
            int prevSize = prevTree->children.size();
            int currSize = currTree->children.size();
            int i = 0;
            int j = 0;

            while (i < prevSize && j < currSize) {
                Index index = detect(prevTree->children[i], currTree->children[j], events);
                if (index == Index::PREV) { // Only increment prev index (i)
                    i++;      // Keep curr index (j) the same
                } else if (index == Index::CURR) {  // Only increment curr index (j)
                    j++;      // Keep prev index (i) the same.
                } else {
                    // Else increment both
                    i++;
                    j++;
                }
            }

            // Deletion at the End
            while (i < prevSize) {
                TreeNode *prevNode = prevTree->children[i];
                addLeaves(prevNode, EventType::DELETE, events);
                i++;
            }

            // Creation at the End
            while (j < currSize) {
                TreeNode *currNode = currTree->children[j];
                addLeaves(currNode, EventType::CREATE, events);
                j++;
            }
        } else {
            if (prevTree->timeStats.modified < currTree->timeStats.modified) {
                std::cout << "MODIFIED: " << prevTree->fullPath << std::endl;
            }
        }

        return Index::BOTH;
    } else if (prevTree->name < currTree->name) {   // prevTree node deleted
        addLeaves(prevTree, EventType::DELETE, events);
        return Index::PREV;
    } else {                                        // currTree node created
        addLeaves(currTree, EventType::CREATE, events);
        return Index::CURR;
    }
}

/*
 * Adds all the leaves fo the tree as the event specified to the events list.
 */
void addLeaves(TreeNode *tree, EventType type, std::vector<Event> *events) {
    std::vector<TreeNode *> stack;
    stack.push_back(tree);
    while (stack.size() > 0) {
        TreeNode *node = stack[stack.size() - 1];
        stack.pop_back();
        // If Leaf Node
        if (node->type == PathType::FILE) {
            std::cout << type << ": " << node->fullPath << std::endl;
        } else {
            for (int i = node->children.size() - 1; i >= 0; i--) {
                stack.push_back(node->children[i]);
            }
        }
    }
}
