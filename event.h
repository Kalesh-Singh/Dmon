#ifndef DMON_EVENT_H
#define DMON_EVENT_H

#include <iostream>

enum class EventType {
    CREATE,
    MODIFY,
    DELETE,
    UNKNOWN
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
