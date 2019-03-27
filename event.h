#ifndef DMON_EVENT_H
#define DMON_EVENT_H

#include <iostream>

enum class Event {
    CREATE,
    MODIFY,
    DELETE
};

/*
 * Parses the event string and returns the corresponding event.
 */
Event getEvent(const std::string& eventStr);

#endif //DMON_EVENT_H
