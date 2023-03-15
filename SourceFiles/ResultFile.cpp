//
// Created by yarin on 13/01/2023.
//

#include "ResultFile.h"
/**
 * constructor
 * @param dio default io object
 * @param classifiedVectors vector of the classified vectors based on their line in the test vectors file
 */
ResultFile::ResultFile(DefaultIO* dio, std:: vector<std::pair< int,std::string>>* classifiedVectors) {
    this->dio = dio;
    this->classifiedVectors = classifiedVectors;
}
/**
 * sending the content of the classified vectors line by line
 * where each line made from number of line and the result of the classification of this specific line from test vectors file.
 * @param elements Elements object(description in the class)
 */
void ResultFile::execute(Elements* elements) {
    std:: vector<std::pair< int,std::string>> classifiedVectorsTemp = *(this->classifiedVectors);
    int size = classifiedVectorsTemp.size();
    for(int i = 0; i < size; i++) {
        std::string result = "";
        result += std::to_string(classifiedVectorsTemp.at(i).first);
        result += ",";
        result += classifiedVectorsTemp.at(i).second;
        result += "\n";
        dio->write(result);
    }
    std::string done = "Done.\n";
    dio->write(done);
}
/**
 * default constructor.
 */
ResultFile::ResultFile() {}
/**
 * distractor.
 */
ResultFile::~ResultFile(){}