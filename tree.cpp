//
// Created by kalesh on 3/29/19.
//

#include "tree.h"

/*
 * Prints a PathType
 */
std::ostream& operator<<(std::ostream &out, const PathType &pathType) {
    switch (pathType) {
        case PathType::FILE:
            out << "FILE";
            break;
        case PathType::DIRECTORY:
            out << "DIRECTORY";
            break;
        default:
            out << "UNKNOWN";
    }
    return out;
}
