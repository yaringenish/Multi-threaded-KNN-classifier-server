//
// Created by Roi on 12/01/2023.
//

#ifndef ADV_PROG_ASS4_PREPAREDVECTORS_H
#define ADV_PROG_ASS4_PREPAREDVECTORS_H
#include "Command.h"
#include <vector>

/**
 * Forth command on the CLI object.
 */
class PreparedVectors : public Command{
private:
    std:: vector<std::pair< int,std::string>>* classifiedVectors;

public:
    PreparedVectors();
    PreparedVectors(DefaultIO* dio, std:: vector<std::pair< int,std::string>>* classifiedVectors);
    void execute(Elements* elements);
    ~PreparedVectors();
};


#endif //ADV_PROG_ASS4_PREPAREDVECTORS_H
