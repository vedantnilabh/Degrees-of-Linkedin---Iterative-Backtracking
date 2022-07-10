
// Vedant Nilabh
/**
 * Linked List Tests
 */

#include "catch.hpp"
#include "LinkedList.h"
#include "DSString.h"

TEST_CASE("Linked List of integers - push back"){
    DSLinkedList<int> emptyList;
    DSLinkedList<int> testList;
    testList.push_back(10);
    testList.push_back(20);
    SECTION("check empty list is empty"){
        REQUIRE(emptyList.getSize() == 0);
        REQUIRE(testList.getSize() != 0);
    }
    SECTION("Testing 10 at first pos and 20 at second") {
        REQUIRE(testList.at(0) == 10);
        REQUIRE(testList.at(1) == 20);
    }

    SECTION("Testing that after pushing back a new element, it is in pos 3") {
        testList.push_back(30);
        REQUIRE(testList.at(2) == 30);
    }

    SECTION("Push back 30 from above is not in test vector in new section") {
        REQUIRE(testList.at(1) == 20);
        REQUIRE(testList.getSize() == 2);
    }
}
TEST_CASE("Testing DSLinkedList Copy Constructor and Push Front"){
    SECTION("check copy constructor for integers"){
        DSLinkedList<int> intList;
        intList.push_front(3);
        intList.push_front(2);
        intList.push_front(1);
        DSLinkedList<int> intList2 = intList;
        REQUIRE(intList2.at(0) == 1);
        REQUIRE(intList2.at(0) == intList2.at(0));
        REQUIRE(intList2.at(1) == 2);
        REQUIRE(intList2.at(1) == intList.at(1));
        REQUIRE(intList2.at(2) == 3);
        REQUIRE(intList2.at(2) == intList.at(2));
        intList.Remove(1);
        REQUIRE(intList2.getSize() != intList.getSize());
        REQUIRE(intList2.at(1) != intList.at(1));
    }
    SECTION("check on DSString objects"){
        DSLinkedList<DSString> stringList;
        stringList.push_front("this");
        stringList.push_front("is");
        stringList.push_front("a test");
        DSLinkedList<DSString> testList = stringList;
        REQUIRE(stringList.at(0) == testList.at(0));
        REQUIRE(stringList.at(1) == testList.at(1));
        REQUIRE(stringList.at(2) == testList.at(2));
        REQUIRE(stringList.getSize() == testList.getSize());
        stringList.Remove(0);
        REQUIRE(stringList.at(0) != testList.at(0));
    }

}
TEST_CASE("Testing DSLinkedList overloaded assignment operator and Push Front"){
    SECTION("check overloaded assignment for integers"){
        DSLinkedList<int> intList;
        intList.push_front(3);
        intList.push_front(2);
        intList.push_front(1);
        DSLinkedList<int> intList2;
        intList2 = intList;
        REQUIRE(intList2.at(0) == 1);
        REQUIRE(intList2.at(0) == intList2.at(0));
        REQUIRE(intList2.at(1) == 2);
        REQUIRE(intList2.at(1) == intList.at(1));
        REQUIRE(intList2.at(2) == 3);
        REQUIRE(intList2.at(2) == intList.at(2));
        intList.Remove(1);
        REQUIRE(intList2.getSize() != intList.getSize());
        REQUIRE(intList2.at(1) != intList.at(1));
    }
    SECTION("check on DSString objects"){
        DSLinkedList<DSString> stringList;
        stringList.push_front("this");
        stringList.push_front("is");
        stringList.push_front("a test");
        DSLinkedList<DSString> testList;
        testList = stringList;
        REQUIRE(stringList.at(0) == testList.at(0));
        REQUIRE(stringList.at(1) == testList.at(1));
        REQUIRE(stringList.at(2) == testList.at(2));
        REQUIRE(stringList.getSize() == testList.getSize());
        stringList.Remove(0);
        REQUIRE(stringList.at(0) != testList.at(0));
    }

}

TEST_CASE("check Remove function - DSLinkedList") {
    SECTION("check with ints") {
        DSLinkedList<int> intList;
        intList.push_back(5);
        intList.push_back(4);
        intList.push_back(3);
        intList.Remove(0);
        REQUIRE(intList.at(0) == 4);
        REQUIRE(intList.at(1) == 3);
        REQUIRE(intList.at(0) != 5);
    }

    SECTION("check with DSString") {
        DSLinkedList<DSString> stringList;
        stringList.push_back("this");
        stringList.push_back("is");
        stringList.push_back("a test");
        stringList.Remove(2);
        REQUIRE(stringList.at(0) == "this");
        REQUIRE(stringList.at(1) == "is");
        REQUIRE(stringList.getSize() == 2);
    }
}

TEST_CASE("check Insert function - DSLinkedList"){
    SECTION("check with ints"){
        DSLinkedList<int> intList;
        intList.push_back(5);
        intList.push_back(4);
        intList.push_back(3);
        intList.Insert(0, 0);
        REQUIRE(intList.at(0) == 0);
        REQUIRE(intList.at(1) == 5);
        REQUIRE(intList.at(2) == 4);
        REQUIRE(intList.at(3) == 3);
        REQUIRE(intList.getSize() == 4);

    }
    SECTION("check with DSString"){
        DSLinkedList<DSString> stringList;
        stringList.push_back("this");
        stringList.push_back("is");
        stringList.push_back("a test");
        stringList.Insert( "for insert", 3);
        REQUIRE(stringList.at(0) == "this");
        REQUIRE(stringList.at(1) == "is");
        REQUIRE(stringList.at(2) == "a test");
        REQUIRE(stringList.at(3) == "for insert");
        REQUIRE(stringList.getSize() == 4);
        stringList.Insert("insert middle", 3);
        REQUIRE(stringList.at(3) == "insert middle");
        REQUIRE(stringList.getSize() == 5);
    }
}

TEST_CASE("check search function - DSLinkedList"){
    SECTION("check with ints"){
        DSLinkedList<int> intList;
        intList.push_back(5);
        intList.push_back(4);
        intList.push_back(3);
        REQUIRE(intList.Search(3) == 2);
        REQUIRE(intList.Search(4) == 1);
        REQUIRE(intList.Search(5) == 0);

    }

    SECTION("check with DSString"){
        DSLinkedList<DSString> stringList;
        stringList.push_back("this");
        stringList.push_back("is");
        stringList.push_back("a test");
        REQUIRE(stringList.Search("this") == 0);
        REQUIRE(stringList.Search("is") == 1);
        REQUIRE(stringList.Search("a test") == 2);

    }
}

TEST_CASE("check at function - DSLinkedList") {
    SECTION("check with ints") {
        DSLinkedList<int> intList;
        intList.push_back(5);
        intList.push_back(4);
        intList.push_back(3);
        REQUIRE(intList.at(0) == 5);
        REQUIRE(intList.at(1) == 4);
        REQUIRE(intList.at(2) == 3);
        REQUIRE(intList.getSize() == 3);

    }
    SECTION("check with DSString") {
        DSLinkedList<DSString> stringList;
        stringList.push_back("this");
        stringList.push_back("is");
        stringList.push_back("a test");
        REQUIRE(stringList.at(0) == "this");
        REQUIRE(stringList.at(1) == "is");
        REQUIRE(stringList.at(2) == "a test");
        REQUIRE(stringList.getSize() == 3);
    }
}
TEST_CASE("check get head function and iterating through list (using at and size)"){
        DSLinkedList<int> intList;
        intList.push_back(3);
        intList.push_back(4);
        intList.push_back(5);
        ListNode<int>* theHead = intList.getHead();
        int size = 0;
        while(theHead != nullptr){
            theHead = theHead->next;
            size++;
        }
        REQUIRE(size == intList.getSize());
        for(int i = 0; i < intList.getSize(); i++){
            cout << intList.at(i) << "  ";
        }
        REQUIRE(intList.at(0) == 3);
        REQUIRE(intList.at(1) == 4);
        REQUIRE(intList.at(2) == 5);

    }

TEST_CASE("check the print function") {
    DSLinkedList<int> intList;
    intList.push_back(3);
    intList.push_back(4);
    intList.push_back(5);
    intList.print();
    REQUIRE(intList.at(0) == 3);
    REQUIRE(intList.at(1) == 4);
    REQUIRE(intList.at(2) == 5);

}







