//
// Created by kalesh on 3/28/19.
//

#include "monitor.h"

/*
 * Compares two trees and populates the events vector.
 */
Index detect(TreeNode *prevTree, TreeNode *currTree, std::vector <Event> *events) {
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
                // TODO: Change this from pre to post order.
                // Get all the leaf nodes of prevNode
                std::vector<TreeNode *> stack;
                stack.push_back(prevNode);
                while (stack.size() > 0) {
                    TreeNode *node = stack[stack.size() - 1];
                    stack.pop_back();
                    // If Leaf Node
                    if (node->type == PathType::FILE) {
                        std::cout << "DELETED: " << node->fullPath << std::endl;
                    } else {
                        for (int i = node->children.size() - 1; i >= 0; i--) {
                            stack.push_back(node->children[i]);
                        }
                    }
                }
                i++;
            }

            // Creation at the End
            while (j < currSize) {
                TreeNode *currNode = currTree->children[j];
                // TODO: Change this from pre to post order.
                // Get all the leaf nodes of currNode
                std::vector<TreeNode *> stack;
                stack.push_back(currNode);
                while (stack.size() > 0) {
                    TreeNode *node = stack[stack.size() - 1];
                    stack.pop_back();
                    // If Leaf Node
                    if (node->type == PathType::FILE) {
                        std::cout << "CREATED: " << node->fullPath << std::endl;
                    } else {
                        for (int i = node->children.size() - 1; i >= 0; i--) {
                            stack.push_back(node->children[i]);
                        }
                    }
                }
                j++;
            }
        } else {
            if (prevTree->timeStats.modified < currTree->timeStats.modified) {
                std::cout << "MODIFIED: " << prevTree->fullPath << std::endl;
            }
        }

        return Index::BOTH;
    } else if (prevTree->name < currTree->name) {   // prevTree node deleted
        // TODO: Change this from pre to post order
        // Get all the leaf nodes of prevTree
        std::vector<TreeNode *> stack;
        stack.push_back(prevTree);
        while (stack.size() > 0) {
            TreeNode *node = stack[stack.size() - 1];
            stack.pop_back();
            // If Leaf Node
            if (node->type == PathType::FILE) {
                std::cout << "DELETED: " << node->fullPath << std::endl;
            } else {
                for (int i = node->children.size() - 1; i >= 0; i--) {
                    stack.push_back(node->children[i]);
                }
            }
        }

        return Index::PREV;
    } else {                                        // currTree node created
        // TODO: Change this from pre to post order.
        // Get all the leaf node of currTree
        std::vector<TreeNode *> stack;
        stack.push_back(currTree);
        while (stack.size() > 0) {
            TreeNode *node = stack[stack.size() - 1];
            stack.pop_back();
            // If Leaf Node
            if (node->type == PathType::FILE) {
                std::cout << "CREATED: " << node->fullPath << std::endl;
            } else {
                for (int i = node->children.size() - 1; i >= 0; i--) {
                    stack.push_back(node->children[i]);
                }
            }
        }

        return Index::CURR;
    }
}

