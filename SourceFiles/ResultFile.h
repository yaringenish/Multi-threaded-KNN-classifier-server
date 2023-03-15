//
// Created by yarin on 13/01/2023.
//

#ifndef ADV_PROG_ASS4_RESULTFILE_H
#define ADV_PROG_ASS4_RESULTFILE_H
#include "Command.h"
#include <vector>
/**
 * Fifth command on the CLI object.
 */
class ResultFile :public Command {
private:
    std:: vector<std::pair< int,std::string>>* classifiedVectors;
public:
    ResultFile();
    ResultFile(DefaultIO* dio, std:: vector<std::pair< int,std::string>>* classifiedVectors);
    void execute(Elements* elements);
    ~ResultFile();
};


#endif //ADV_PROG_ASS4_RESULTFILE_H



