//
// Created by kalesh on 3/29/19.
//

#ifndef DMON_LIST_H
#define DMON_LIST_H

template<typename T>
struct Node {
    Node() : prev(nullptr), next(nullptr), value(0) {}

    Node(const T val) : prev(nullptr), next(nullptr), value(val) {}

    Node(const Node<T> *node) : prev(node->prev), next(node->next), value(node->value) {}

    Node<T> *prev;
    Node<T> *next;
    T value;
};

templete<typename T>
class List {
public:
    // Constructors
    List() : head(nullptr), taile(nullptr), size(0) {}
    List(const int size);
    List(const List& rhs);
    ~List();

    // Equality
private:
    void subError();    // Handles memory subscripts out of range

    Node<T> *head;
    Node<T> *tail;
    unsigned int size;
};

#endif //DMON_LIST_H
