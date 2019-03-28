#include "event.h"

/*
 * Parses the event string and returns the corresponding event.
 */
Event getEvent(const std::string &eventStr) {
    if (eventStr == "CREATE") {
        return Event::CREATE;
    } else if (eventStr == "MODIFY") {
        return Event::MODIFY;
    } else if (eventStr == "DELETE") {
        return Event::DELETE;
    } else {
        return Event::UNKNOWN;
    }
}

/*
 * Prints an event
 */
std::ostream &operator<<(std::ostream &out, const Event &event) {
    switch (event) {
        case Event::CREATE:
            out << "CREATE";
            break;
        case Event::MODIFY:
            out << "MODIFY";
            break;
        case Event::DELETE:
            out << "DELETE";
            break;
        default:
            out << "UNKNOWN";
            break;
    };
    return out;
}
