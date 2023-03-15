//
// Created by yarin on 11/01/2023.
//

#ifndef ADV_PROG_ASS4_UPLOAD_H
#define ADV_PROG_ASS4_UPLOAD_H
#include "FileValidate.h"
#include "Command.h"
#include "Elements.h"
/**
 * First command on the CLI object.
 */
class Upload : public Command {
public:
        FileValidate* fv;
        std:: vector<std::string > trainFileVec;
        std:: vector<std::string > testFileVec;
        bool isFileOpen;
    public:
        Upload(DefaultIO* dio);
        void readFile(std:: vector<std::string> &vec);
        void execute(Elements* elements);
        FileValidate* getFV();
        ~Upload();
};


#endif //ADV_PROG_ASS4_UPLOAD_H
