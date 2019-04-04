#ifndef DMON_EVENT_H
#define DMON_EVENT_H

#include <iostream>
#include "tree.h"

enum class EventType {
    CREATE,
    MODIFY,
    DELETE,
    UNKNOWN
};

struct Event {
    Event(EventType type, TreeNode node) : type(type), node(node) {}

    EventType type;
    TreeNode node;
};

/*
 * Parses the event string and returns the corresponding event.
 */
EventType getEventType(const std::string &eventStr);

/*
 * Prints an event
 */
std::ostream &operator<<(std::ostream &out, const EventType &event);

#endif //DMON_EVENT_H
