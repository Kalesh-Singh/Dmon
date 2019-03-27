#include "event.h"

/*
 * Parses the event string and returns the corresponding event.
 */
Event getEvent(const std::string& eventStr) {
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
