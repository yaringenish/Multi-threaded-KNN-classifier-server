//
// Created by yarin on 11/01/2023.
//

#include "Upload.h"
#include "DefaultIO.h"
#include "FileValidate.h"
#include "Elements.h"
/**
 * constructor
 * @param dio default io object
 */
Upload::Upload(DefaultIO *dio) {
    this->description = "";
    this->dio = dio;
}
/**
 * receiving file path  if valid reading the file line by line and and inserting to vector of strings,
 * otherwise sending matching message to the client.
 * @param vec vector of strings.
 */
void Upload:: readFile(std:: vector<std::string> &vec){
    std::string s = "";
    std::string finish = "Finish";
    std::string  problem = "problemWithPath";
    s = dio->readByChar();

    if(strcmp(s.c_str(), problem.c_str()) == 0 ) {

        this->isFileOpen = false;
        return;
    }
    while(strcmp(s.c_str(), finish.c_str()) != 0 ) {
        vec.push_back(s);
        //s = "";
        s = dio->readByChar();
    }


}
/**
 * requesting from the client for train file and test file , if both of the files paths are valid and their content are also valid
 * making file validate which includes both of files content , otherwise sending matching message to the client.
 * @param elements Elements object(description in the class).
 */
void Upload::execute(Elements* elements)  {
    this->isFileOpen = true;
    this->trainFileVec.clear();
    this->testFileVec.clear();
    dio->write("Please upload your local train CSV file.\n");
    readFile(this->trainFileVec);
    if(this->isFileOpen) {
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        readFile(this->testFileVec);
        if(this->isFileOpen) {
            dio->write("Upload complete.\n");
        }
        else {

            elements->setIsUpload(false);
            return;
        }
    }
    else {
        elements->setIsUpload(false);
        return;
    }


    FileValidate* fv1 = new FileValidate(this->trainFileVec,this->testFileVec);
    if(!fv1->getIsValid()) {
        elements->setIsUpload(false);
        this->dio->write("invalid files\n");
        return;
    }

    this->dio->write("aaa\n");


    this->fv = fv1;

    elements->setFile(this->fv);
    elements->setIsUpload(true);
    elements->setMaxK(this->fv->getVectors().size());
}

/**
 * Getter
 * @return File validate object.
 */
FileValidate* Upload::getFV(){
    return this->fv;
}
/**
 * This is the destructor of the upload class.
 */
Upload::~Upload(){
//    delete(this->fv);
}