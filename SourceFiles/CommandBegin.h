//
// Created by Roi on 10/01/2023.
//

#ifndef ADV_PROG_ASS4_COMMANDBEGIN_H
#define ADV_PROG_ASS4_COMMANDBEGIN_H
#include "Command.h"
#include "Elements.h"
class CommandBegin: public Command {
public:
    /**
 * This is the constructor of the CommandBegin class. It initializes the members of the class.
 * @param dio DefaultIO* type.
 */
    CommandBegin(DefaultIO* dio);

    /**
 * This functions sends to the client the menu of the program.
 * @param elements Elements* type.
 */
    void execute(Elements* elements);

    /**
 * This function is the destructor of the CommandBegin class.
 */
    ~CommandBegin();
};


#endif //ADV_PROG_ASS4_COMMANDBEGIN_H
