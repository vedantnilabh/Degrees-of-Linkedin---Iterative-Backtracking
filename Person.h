//
// Created by Vedant Nilabh on 6/15/22.
//

#ifndef INC_22SU_PA03_PERSON_H
#define INC_22SU_PA03_PERSON_H

#include "LinkedList.h"
#include "DSString.h"
class Person {
public:
    DSString name; // name of person (node)
    DSLinkedList<DSString> connections; // all the people that we can get to from that person/node
    Person(); // default constructor
    Person(DSString name); // overloaded constructor
    bool operator== (const Person&) const; // overloaded == operator - useful for comparison in backtracking
};


#endif //INC_22SU_PA03_PERSON_H
