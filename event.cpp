#include "event.h"

/*
 * Parses the event string and returns the corresponding event.
 */
EventType getEventType(const std::string &eventStr) {
    if (eventStr == "CREATE") {
        return EventType::CREATE;
    } else if (eventStr == "MODIFY") {
        return EventType::MODIFY;
    } else if (eventStr == "DELETE") {
        return EventType::DELETE;
    } else {
        return EventType::UNKNOWN;
    }
}

/*
 * Prints an event
 */
std::ostream &operator<<(std::ostream &out, const EventType &event) {
    switch (event) {
        case EventType::CREATE:
            out << "CREATE";
            break;
        case EventType::MODIFY:
            out << "MODIFY";
            break;
        case EventType::DELETE:
            out << "DELETE";
            break;
        default:
            out << "UNKNOWN";
            break;
    }
    return out;
}
