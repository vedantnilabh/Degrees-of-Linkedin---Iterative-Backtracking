//
// Created by Vedant Nilabh on 6/15/22.
//

#include "Person.h"

Person::Person(DSString name) {
    this->name = name;

}

bool Person::operator==(const Person& arg) const {
    if(this->name == arg.name){
        return true;
    }
    else {
        return false;
    }
}

Person::Person() {

}

