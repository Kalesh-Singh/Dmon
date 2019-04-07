//
// Created by kalesh on 3/28/19.
//

#ifndef DMON_MONITOR_H
#define DMON_MONITOR_H


#include "tree.h"
#include "event.h"
#include <vector>

/*
 * Compares two trees and populates the events vector.
 */

enum class Index {
    BOTH,
    PREV,
    CURR
};

Index detect(TreeNode* prevTree, TreeNode* currTree, std::vector<Event>* events);

#endif //DMON_MONITOR_H
