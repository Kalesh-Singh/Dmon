#ifndef DMON_EVENT_H
#define DMON_EVENT_H

#include <iostream>

enum class Event {
    CREATE,
    MODIFY,
    DELETE,
    UNKNOWN
};

/*
 * Parses the event string and returns the corresponding event.
 */
Event getEvent(const std::string& eventStr);

/*
 * Prints an event
 */
std::ostream &operator<<(std::ostream &out, const Event& event);

#endif //DMON_EVENT_H
