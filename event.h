#ifndef DMON_EVENT_H
#define DMON_EVENT_H

#include <string>

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

#endif //DMON_EVENT_H
