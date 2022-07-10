//
// Created by Vedant Nilabh on 6/15/22.
//
#include "ListNode.h"
#include <iostream>
#ifndef INC_22SU_PA03_LINKEDLIST_H
#define INC_22SU_PA03_LINKEDLIST_H

template<typename T>
class DSLinkedList {
public:
    DSLinkedList();
    ~DSLinkedList();
    DSLinkedList(const DSLinkedList& arg );
    DSLinkedList<T>& operator=(const DSLinkedList& arg);
    void push_front(const T& arg);
    void print();
    void push_back(const T& arg);
    T& at(int location);
    void Insert(const T& arg, int location);
    void Remove(int location);
    int Search(const T& arg);
    int getSize();
    ListNode<T>* getHead();
public:
private:
    ListNode<T>* head;
    int size;

};
template<typename T>
void DSLinkedList<T>::push_front(const T &arg) { // pushes to front of linked list
    ListNode<T>* temp = new ListNode<T>;
    temp->data = arg;
    if(head == nullptr){ // list empty
        head = temp;
    }
    else { // list is not empty
        temp->next = head;
        head = temp;

    }
    size++; // increment size either way
}

template<typename T>
void DSLinkedList<T>::print() { // outputs contents
    if(head == nullptr){
        return; // can't print empty list
    }
    ListNode<T>* curr = head;
    while(curr->next != nullptr){
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << curr->data << std::endl; // last element
}

template<typename T>
void DSLinkedList<T>::push_back(const T &arg) { // push to end of list
    ListNode<T>* temp = new ListNode<T>;
    temp->data = arg;
    if(head == nullptr){ // list is empty
        head = temp;
        size = 1;
        return;
    }
    ListNode<T>* curr = head; // list is not empty
    while(curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = temp;
    temp->prev = curr;
    temp->next = nullptr;
    size++;
    return;
}

template<typename T>
T &DSLinkedList<T>::at(int location) {
    ListNode<T>* curr = head;
    int iter = 0; // checks to see if match to location
    while(curr != nullptr && iter < location){
        iter++;
        curr = curr->next;
    }
    if(iter == location && curr != nullptr){ // some data is at the specified location
        return curr->data;
    }
    throw std::runtime_error("Error, location is not in list bounds"); // throwing error

}

template<typename T>
void DSLinkedList<T>::Insert(const T &arg, int location) {
    if(head == nullptr || location == 0){ // either list empty or inserting at front
        push_front(arg);
        return;
    }
    if(location == size){ // inserting at back
        push_back(arg);
        return;
    }
    int iter = 0; // inserting in middle
    ListNode<T>* curr = head;
    while(curr->next != nullptr){
        if(location - 1 == iter){
            ListNode<T>* temp = new ListNode<T>;
            ListNode<T>* next = curr->next;
            temp->data = arg;
            temp->next = next;
            temp->prev = curr;
            curr->next = temp;
            next->prev = temp;
            size++;
            return;
        }
        curr = curr->next;
        iter++;
    }
    throw std::runtime_error("location not in list bounds");


}

template<typename T>
DSLinkedList<T>::~DSLinkedList() { // destructor
    ListNode<T>* curr = head;
    while(curr != nullptr){
        ListNode<T>* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr; // list now empty
    size = 0;

}

template<typename T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& arg) { // overloaded copy constructor
    if(arg.head == nullptr){ // arg list empty
        head = nullptr;
        size = 0;
    }
    else { // making a deep copy
        head = new ListNode<T>(arg.head->data);
        ListNode<T>* nextNode = arg.head->next;
        ListNode<T>* curr = head;
        while(nextNode != nullptr){
            curr->next = new ListNode<T>(nextNode->data, nullptr, curr);
            curr = curr->next;
            nextNode = nextNode->next;
        }
        size = arg.size;
    }

}

template<typename T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& arg) {
    if(this == &arg){ // checking for self assignment
        return *this;
    }
    if(head != nullptr){ // deallocate memory on heap
        this->~DSLinkedList<T>();
    }
    if(arg.head == nullptr){ // list empty
        head = nullptr;
        size = 0;
        return *this;
    }
    else { // deep copy created
            head = new ListNode<T>(arg.head->data);
            ListNode<T>* nextNode = arg.head->next;
            ListNode<T>* curr = head;
            while(nextNode != nullptr){
                curr->next = new ListNode<T>(nextNode->data, nullptr, curr);
                curr = curr->next;
                nextNode = nextNode->next;
            }
            size = arg.size;
        }


    return *this;
}

template<typename T>
void DSLinkedList<T>::Remove(int location) {
    if(head == nullptr){ // edge case
        return;
    }
    if(size == 1){ // list now empty

        delete head;
        size = 0;
        return;
    }
    if(location == 0){ // removing head node
        ListNode<T>* next = head->next;
        delete head;
        head = next;
        size--;
        return;

    }
    if(location == size - 1){ // removing last node
        ListNode<T>* last = head;
        while(last->next->next != nullptr){
            last = last->next;
        }
        delete last->next;
        last->next = nullptr;
        size--;
        return;
    } // removing node in middle
    int iter = 0;
    ListNode<T>* curr = head;
    while(curr != nullptr){
        if(location - 1 == iter){
            ListNode<T>* next = curr->next;
             curr->next = curr->next->next;
             curr->next->prev = curr;
             delete next;
             size--;
             return;
        }
        curr = curr->next;
        iter++;
    }
    throw std::out_of_range("Error, location passed is not in list bounds");
}

template<typename T>
int DSLinkedList<T>::Search(const T &arg) {
    if(head == nullptr){ // edge case
        return -1;
    }
    ListNode<T>* curr = head;
    int iter = 0;
    while(curr != nullptr){
        if(curr->data == arg){
            return iter;
        }
        iter++;
        curr = curr->next;

    }
    return -1; // if we can't find a location

}

template<typename T>
DSLinkedList<T>::DSLinkedList() { // default constructor
    head = nullptr;
    size = 0;
}

template<typename T>
int DSLinkedList<T>::getSize() { // accessor for size - iteration
    return size;
}

template<typename T>
ListNode<T> *DSLinkedList<T>::getHead() { // accessor for head pointer, used in backtracking to keep track of sublist pointers in a DSVector
    return head;
}


#endif //INC_22SU_PA03_LINKEDLIST_H
