//
// Created by Roi on 10/01/2023.
//

#include "CommandBegin.h"

/**
 * This is the constructor of the CommandBegin class. It initializes the members of the class.
 * @param dio DefaultIO* type.
 */
CommandBegin::CommandBegin(DefaultIO* dio){
    std::string s1 = "Welcome to the KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n";
    std::string s2 = "2. algorithm settings\n3. classify data\n4. display results\n5. download results\n8. exit";
    std::string s = s1+s2;
    this->description = s;
    this->dio = dio;
}

/**
 * This functions sends to the client the menu of the program.
 * @param elements Elements* type.
 */
void CommandBegin::execute(Elements* elements)  {
    this->dio->write(this->description);
}

/**
 * This function is the destructor of the CommandBegin class.
 */
CommandBegin::~CommandBegin(){}
