//
// Created by yarin on 09/01/2023.
//

#ifndef ADV_PROG_ASS4_DEFAULTIO_H
#define ADV_PROG_ASS4_DEFAULTIO_H
#include <string>
#include <stdio.h>

class DefaultIO {
protected:
    int clientID;
public:
    /**
 * This is the constructor of the DefaultIO class.
 * @param clientID int type.
 */
    DefaultIO(int clientID);
    virtual void write(std::string scl) = 0;
    virtual std::string read() = 0;
    /**
 * This method gets a char* array and converts it to a string.
 * @param a the char* array.
 * @param size the size of the array, int type.
 * @return string type, the result of the conversion.
 */
    std::string convertToString(char* a, int size);

    /**
 *This method reads from the user each byte every read, concat all the chars to a string
 * and returns the result of the concat.
 * @return the result, string type.
 */
    virtual std::string readByChar();


    /**
 * This is the destructor of the DefaultIO class.
 */
    virtual ~DefaultIO() ;
};


#endif //ADV_PROG_ASS4_DEFAULTIO_H
