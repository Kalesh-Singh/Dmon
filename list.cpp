//
// Created by kalesh on 3/29/19.
//

#include "list.h"

template<typename T>
List<T>::~List() {
    Node<T> *nodePtr = head;
    while (nodePtr != nullptr) {
        Node<T> *nextNode = nodePtr->link;
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
            nodePtr = nodePtr->link;
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
    Node<T> *newNode = new Node<T>(value);
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

template <typename T>
void List<T>::pop_back()
{
    if (!head) {                            // Empty list
        return;
    } else if (head && tail == head) {      // Remove head
        delete head;
        head = nullptr;
        tail = nullptr;
        sz = 0;
    } else {                                // Remove tail
        Node<T>* nodePtr = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete nodePtr;
        sz--;
    }
}

template <typename T>
void List<T>::erase(const unsigned int position)
{
    if (sz <= position || head == nullptr) {
        subError();
    }
    Node<T>* nodePtr = head;

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