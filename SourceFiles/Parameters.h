//
// Created by Roi on 11/01/2023.
//

#ifndef ADV_PROG_ASS4_PARAMETERS_H
#define ADV_PROG_ASS4_PARAMETERS_H
#include "Command.h"
#include "Elements.h"
class Parameters: public Command{
private:
    int k;
    std::string dstType;
    bool isKValid;
    bool isMetricValid;

public:
    /**
 * constructor method to initiate the Parameters class.
 * @param dio  DefaultIO* type.
 */
    Parameters(DefaultIO* dio);

    /**
 * This is a getter method to get the k member.
 * @return current k, int type.
 */
    int getK();

    /**
 * This is a getter method to get the current destType member.
 * @return the current destType, string type.
 */
    std::string getDestType();

    /**
 * This function splits the client's input for k and metric and checks that they are valid.
 * it checks that the input for k is an integer anf the input gor metric is one of the five options.
 * @param str the user's full input.
 * @param k int type.
 * @param dstType string type.
 * @param isKValid an indicator if the k is valid.
 * @param isMetricValid an indicator if the metric is valid.
 * @param elements Elements* type.
 * @return true if the user's input is valid, else otherwise.
 */
    bool fromString(std::string str, int &k, std::string &dstType, bool &isKValid, bool &isMetricValid, Elements* elements);

    /**
 * This method gets from the client the user's input and checks that the input is valid using fromString method.
 * If the input is valid it changes the current k and metric to the new values, else it doesn't change the k
 * and metric and sends the client what was the problem.
 * @param elements Elements* type.
 */
    void execute(Elements* elements);

    /**
 * destructor method for Parameters class.
 */
    ~Parameters();

};


#endif //ADV_PROG_ASS4_PARAMETERS_H
