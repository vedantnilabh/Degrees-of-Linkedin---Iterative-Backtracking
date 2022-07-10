//
// Created by Vedant Nilabh on 6/19/22.
//

#ifndef INC_22SU_PA03_DEGREESOFLINKEDIN_H
#define INC_22SU_PA03_DEGREESOFLINKEDIN_H
#include <stack>
#include <fstream>
#include <iostream>
#include "LinkedList.h"
#include "DSVector.h"
#include "DSString.h"
#include "AdjList.h"
class DegreesofLinkedin {
public:
    DegreesofLinkedin(char** argv);
    void ReadFile();
    void CreateAdjList();
    void Backtracking();
    void MinPaths();
    void OutputToFile();
    void ExecuteProgram();
private:
    char* linksFilePath;
    char* outputFilePath;
    AdjList LinkedinConnections;
    DSVector<DSString> leftSide;
    DSVector<DSString> rightSide;
    DSVector<DSString> leftPath;
    DSVector<DSString> rightPath;
    DSVector<DSVector<stack<Person>>> allPaths;
    DSVector<int> minPathSize;


};


#endif //INC_22SU_PA03_DEGREESOFLINKEDIN_H
