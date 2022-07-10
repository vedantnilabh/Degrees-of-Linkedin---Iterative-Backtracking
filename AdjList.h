//
// Created by Vedant Nilabh on 6/15/22.
//

#ifndef INC_22SU_PA03_ADJLIST_H
#define INC_22SU_PA03_ADJLIST_H

#include "Person.h"
class AdjList {
public:
    AdjList();
    DSLinkedList<Person> adjacencyList; // the adjacency list - linked list of person objects
};


#endif //INC_22SU_PA03_ADJLIST_H
