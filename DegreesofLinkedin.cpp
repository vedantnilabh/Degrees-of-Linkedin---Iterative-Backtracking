//
// Created by Vedant Nilabh on 6/19/22.
//

#include "DegreesofLinkedin.h"

DegreesofLinkedin::DegreesofLinkedin(char** argv) {
    // Constructor for command line arguements
    linksFilePath = argv[1];
    outputFilePath = argv[2];
}

void DegreesofLinkedin::ReadFile() {
    ifstream file_links(linksFilePath);
    if(!file_links.is_open()){
        cout << "error opening file" << endl;
    }
    // reading in file
    char buffer[500];
    file_links.getline(buffer, 10);
    int connections = atoi(buffer);
    for(int i = 0; i < connections; i++){
        file_links.getline(buffer, 499, '|');
        DSString person1(buffer);
        person1 = person1.substring(0, person1.getLength() - 1); // space at end
        leftSide.pushBack(person1); // left connections in file
        file_links.getline(buffer, 499);
        DSString person2(buffer);
        person2 = person2.substring(1, person2.getLength() - 1); // space at start
        rightSide.pushBack(person2); // right connections in file
    }
    file_links.getline(buffer, 2);
    int findPaths = atoi(buffer);
    for(int i = 0; i < findPaths; i++){
        file_links.getline(buffer, 499, '|');
        DSString person1(buffer);
        person1 = person1.substring(0, person1.getLength() - 1);
        leftPath.pushBack(person1); // starting node for path
        file_links.getline(buffer, 499);
        DSString person2(buffer);
        person2 = person2.substring(1, person2.getLength() - 1);
        rightPath.pushBack(person2); // ending node for path
    }
    file_links.close();
}

void DegreesofLinkedin::CreateAdjList() {
    for(int i = 0; i < leftSide.getSize(); i++) {
        if (LinkedinConnections.adjacencyList.Search(Person(leftSide[i])) < 0) { // means that person on leftside does not exist in adjacency list
            Person newPerson(leftSide[i]);
            newPerson.connections.push_back(rightSide[i]); // connected to right side at same index
            LinkedinConnections.adjacencyList.push_back(newPerson); // push to adjacency list

        }
        else if (LinkedinConnections.adjacencyList.Search(Person(leftSide[i])) >= 0){ // person is in adjacency list
            int loc = LinkedinConnections.adjacencyList.Search(leftSide[i]); // location of person in adjacency list
            LinkedinConnections.adjacencyList.at(loc).connections.push_back(rightSide[i]); // push new person to sublist
        }

        if (LinkedinConnections.adjacencyList.Search(Person(rightSide[i])) < 0) { // same as left side but for right side
            Person newPerson(rightSide[i]);
            newPerson.connections.push_back(leftSide[i]);
            LinkedinConnections.adjacencyList.push_back(newPerson);

        }
        else if (LinkedinConnections.adjacencyList.Search(Person(rightSide[i])) >= 0){
            int loc = LinkedinConnections.adjacencyList.Search(Person(rightSide[i]));
            LinkedinConnections.adjacencyList.at(loc).connections.push_back(leftSide[i]);
        }

    }
}

void DegreesofLinkedin::Backtracking() { // the algorithm
    for(int i = 0; i < leftPath.getSize(); i++){ // number of shortest paths we need to find
        DSVector<ListNode<DSString>*> adjListPtrs; // pointers to each sublist within adjacency list
        for(int i = 0; i < LinkedinConnections.adjacencyList.getSize(); i++){
            adjListPtrs.pushBack(LinkedinConnections.adjacencyList.at(i).connections.getHead()); // gets head pointers
        }
        DSVector<stack<Person>> Paths; // paths for each separation request
        stack<Person> IterationStack; // stack we will use to implement iterative backtracking
        DSVector<Person> stackVector; // vector that will mimic stack so that we can ensure we don't revist what's already on the stack
        Person startNode(leftPath[i]); // we can do this because we overloaded person's '==' operator
        Person endNode(rightPath[i]);
        IterationStack.push(startNode); // push start node to stack
        stackVector.pushBack(IterationStack.top());
        while(!IterationStack.empty()){
            if(IterationStack.top() == endNode) { // found a path
                Paths.pushBack(IterationStack); // push to vector of stacks
                IterationStack.pop(); // popping off stack
                stackVector.Remove(stackVector.getSize() - 1);
            }
            else {
                int index = LinkedinConnections.adjacencyList.Search(IterationStack.top()); // index of current node within adjacency list
                if(adjListPtrs[index] == nullptr){ // means we have explored every path from the current node
                    IterationStack.pop(); // pop off stack
                    stackVector.Remove(stackVector.getSize() - 1);
                    adjListPtrs[index] = LinkedinConnections.adjacencyList.at(index).connections.getHead(); // reset pointers for node we popped
                }
                else if(stackVector.Search(Person(adjListPtrs[index]->data)) >= 0) { // means that current pointer for node pointers to person already on stack
                    adjListPtrs[index] = adjListPtrs[index]->next; // increment pointer to next person in list
                }
                else { // otherwise, we can push the next person within the node's sublist to the stack
                    int index = LinkedinConnections.adjacencyList.Search(IterationStack.top());
                    IterationStack.push(Person(adjListPtrs[index]->data));
                    stackVector.pushBack(IterationStack.top());
                    adjListPtrs[index] = adjListPtrs[index]->next;

                }

            }
        }
        allPaths.pushBack(Paths);
    }
}

void DegreesofLinkedin::MinPaths() {
    // vector of integers for shortest path distance for each request
    for(int i = 0; i < allPaths.getSize(); i++){
        int min = 1000000;
        for(int j = 0; j < allPaths.at(i).getSize(); j++){
            if(allPaths.at(i).at(j).size() < min){
                min = allPaths.at(i).at(j).size();
            }
        }
        minPathSize.pushBack(min);
    }
}

void DegreesofLinkedin::OutputToFile() {
    ofstream file_out(outputFilePath);
    if(!file_out.is_open()){
        cout << "file is not open" << endl;
        exit(1);
    }
    for(int i = 0; i < allPaths.getSize();i++){
        // each degrees of separation request
        file_out << leftPath[i] << " | " << rightPath[i] << " : " << endl;
        cout << leftPath[i] << " | " << rightPath[i] << " : " << endl;
        for(int j = 0; j < allPaths.at(i).getSize(); j++){
            if(allPaths.at(i).at(j).size() == minPathSize.at(i)){ // if the current stack matches the min path value for that request
                DSVector<DSString> Pathnames;
                for(int k = 0; allPaths.at(i).at(j).size(); k++){
                    Pathnames.pushBack(allPaths.at(i).at(j).top().name); // push stack contents to vector to make outputting easier
                    allPaths.at(i).at(j).pop();
                }
                for(int l = 0; l < Pathnames.getSize() - 1; l++){
                    file_out << Pathnames.at(Pathnames.getSize() - 1 - l) << " > ";
                    cout << Pathnames.at(Pathnames.getSize() - 1 - l) << " > ";
                }
                file_out << Pathnames.at(0) << endl;
                cout << Pathnames.at(0) << endl;
                // prints in reverse order (Stack is LIFO so top is end node)

            }
        }
    }

    file_out.close();
}

void DegreesofLinkedin::ExecuteProgram() {
    // calls all other member functions to execute program
    ReadFile();
    CreateAdjList();
    Backtracking();
    MinPaths();
    OutputToFile();
}

