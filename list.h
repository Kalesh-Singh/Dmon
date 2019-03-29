//
// Created by kalesh on 3/29/19.
//

#ifndef DMON_LIST_H
#define DMON_LIST_H

template<typename T>
struct Node {
    Node() : prev(nullptr), value(0), next(nullptr) {}

    Node(Node<T> *prev, const T val) : prev(prev), value(val) {}

    Node(const T val, Node<T> *next) : value(val), next(next) {}

    Node(Node<T> *prev, const T val, Node<T> *next) : prev(prev), value(val), next(next) {}

    Node(const T val) : prev(nullptr), value(val), next(nullptr) {}

    Node<T> *prev;
    Node<T> *next;
    T value;
};

template<typename T>
class List {
public:
    // Constructors
    List() : head(nullptr), tail(nullptr), sz(0) {}

    ~List();

    // Element access:
    T at(const unsigned int position);

    T operator[](const unsigned int position);

    // Modifiers:
    void push_front(const T value);

    void pop_front();

    void push_back(const T value);

    void pop_back();

    void erase(const unsigned int position);

    // Capacity:
    unsigned int size() const { return size; }

private:
    void subError();    // Handles memory subscripts out of range

    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

#endif //DMON_LIST_H
