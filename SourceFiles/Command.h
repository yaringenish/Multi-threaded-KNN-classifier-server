//
// Created by Roi on 10/01/2023.
//

#ifndef ADV_PROG_ASS4_COMMAND_H
#define ADV_PROG_ASS4_COMMAND_H
#include <string.h>
#include "DefaultIO.h"
#include "Elements.h"
class Command {
protected:
    std::string description;
    DefaultIO* dio;
public:
    /**
     * This is the destructor of the Command class.
     */
    virtual ~Command();
    /**
     * This is an abstract method that all the the sub-classes of Command implements
     * each sub class implements it according to their role in the program.
     * @param elements object that has all the shared members.
     */
    virtual void execute(Elements* elements) = 0;
};



#endif //ADV_PROG_ASS4_COMMAND_H
