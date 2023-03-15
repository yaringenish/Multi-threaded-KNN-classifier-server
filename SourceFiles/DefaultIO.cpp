//
// Created by yarin on 09/01/2023.
//

#include "DefaultIO.h"

/**
 * This is the constructor of the DefaultIO class.
 * @param clientID int type.
 */
DefaultIO::DefaultIO(int clientID) {
    this->clientID = clientID;
}

/**
 * This method gets a char* array and converts it to a string.
 * @param a the char* array.
 * @param size the size of the array, int type.
 * @return string type, the result of the conversion.
 */
std::string DefaultIO::convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

/**
 *This method reads from the user each byte every read, concat all the chars to a string
 * and returns the result of the concat.
 * @return the result, string type.
 */
std::string DefaultIO::readByChar(){
    return "";
}

/**
 * This is the destructor of the DefaultIO class.
 */
DefaultIO::~DefaultIO() {}