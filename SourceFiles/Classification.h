//
// Created by yarin on 12/01/2023.
//

#ifndef ADV_PROG_ASS4_CLASSIFICATION_H
#define ADV_PROG_ASS4_CLASSIFICATION_H
#include "FileValidate.h"
#include "Command.h"
#include "Elements.h"
#include <vector>




/**
 * Third command of the CLI
 */
class Classification: public Command{
    public:
        FileValidate* fv;
        std::string distType;
        int k;
        std:: vector<std::pair< int,std::string>> classifiedVectors;
    public:
        Classification();
        Classification(DefaultIO* dio,FileValidate* fv,std::string distType,int k);
        void knnSwitch(std::string choose, FileValidate* fv, int k);
        void execute(Elements* elements);
        ~Classification();
};


#endif //ADV_PROG_ASS4_CLASSIFICATION_H
