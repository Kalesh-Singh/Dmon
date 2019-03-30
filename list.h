//
// Created by kalesh on 3/29/19.
//

#ifndef DMON_LIST_H
#define DMON_LIST_H

#include <iostream>

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

    // Output / Print
    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const List<U>& list);

private:
    void subError();    // Handles memory subscripts out of range

    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

template<typename T>
List<T>::~List() {
    Node<T> *nodePtr = head;
    while (nodePtr != nullptr) {
        Node<T> *nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

template<typename T>
T List<T>::at(const unsigned int position) {
    Node<T> *nodePtr = head;
    if (position < 0 || position >= sz) {
        subError();
    } else {
        for (unsigned int i = 0; i < position; i++) {
            nodePtr = nodePtr->next;
        }
    }
    return nodePtr->value;
}

template<typename T>
T List<T>::operator[](const unsigned int position) {
    return at(position);
}

template<typename T>
void List<T>::push_back(const T value) {
    auto *newNode = new Node<T>(value);
    // If there are no nodes in the list make newNode the first node.
    if (!head) {
        head = newNode;
        tail = newNode;
        // Otherwise, insert newNode at end.
    } else {
        // Insert newNode as the last node.
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    sz++;
}

template<typename T>
void List<T>::push_front(const T value) {
    auto *newNode = new Node<T>(value);
    // If there are no nodes
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    sz++;
}

template<typename T>
void List<T>::pop_back() {
    if (!head) {                            // Empty list
        return;
    } else if (head && tail == head) {      // Remove head
        delete head;
        head = nullptr;
        tail = nullptr;
        sz = 0;
    } else {                                // Remove tail
        Node<T> *nodePtr = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete nodePtr;
        sz--;
    }
}


template<typename T>
void List<T>::pop_front() {
    if (!head) {                            // Empty list
        return;
    } else if (head && tail == head) {      // Remove head
        delete head;
        head = nullptr;
        tail = nullptr;
        sz = 0;
    } else {                                // Remove head
        Node<T>* nodePtr = head;
        head = head->next;
        delete nodePtr;
    }
}

template<typename T>
void List<T>::erase(const unsigned int position) {
    if (sz <= position || head == nullptr) {
        subError();
    }
    Node<T> *nodePtr = head;

    // Erase first element
    if (position == 0) {
        head = head->next;
        delete nodePtr;
        // Otherwise erase element at position
    } else {
        for (unsigned int i = 0; i < position; i++) {
            nodePtr = nodePtr->next;
        }
        nodePtr->prev->next = nodePtr->next;
        nodePtr->next->prev = nodePtr->prev;
        delete nodePtr;
    }
    sz--;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const List<T>& list) {
    Node<T>* nodePtr = list.head;
    out << "[";
    while (nodePtr) {
        if (nodePtr == list.tail) {
            out << nodePtr->value;
        } else {
            out << nodePtr->value << ", ";
        }
        nodePtr = nodePtr->next;
    }
    out << "]";
}

template <typename T>
void List<T>::subError() {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

#endif //DMON_LIST_H
