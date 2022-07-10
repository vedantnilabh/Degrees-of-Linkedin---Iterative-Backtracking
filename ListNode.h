//
// Created by Vedant Nilabh on 6/15/22.
//

#ifndef INC_22SU_PA03_LISTNODE_H
#define INC_22SU_PA03_LISTNODE_H

template<typename T>
class ListNode {
public:
    T data;
    ListNode* next; // doubly linked
    ListNode* prev;
    ListNode();
    ListNode(T& arg, ListNode* n = nullptr, ListNode* p = nullptr);




};
// default constructor
template<typename T>
ListNode<T>::ListNode() {
    next = nullptr;
    prev = nullptr;
}
// overloaded constructor
template<typename T>
ListNode<T>::ListNode(T &arg, ListNode* n, ListNode* p) {
    data = arg;
    next = n;
    prev = p;
}


#endif //INC_22SU_PA03_LISTNODE_H
