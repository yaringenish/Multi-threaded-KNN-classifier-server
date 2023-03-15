#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <cstring>
#include <utility>
#ifndef ADV_PROG_ASS2_FILEVALIDATE_H
#define ADV_PROG_ASS2_FILEVALIDATE_H

/**
 * This FV object will play as a DB for the csv content.
 * Each row of the file will be a pair containing string and double vector.
 * the string will be the kind of flower and the double values vector will contain his different sizes.
 * each one of the pairs(rows) will be inside vector of pairs that it will contain the all date.
 */
class FileValidate {
    std:: vector<std::pair< std::string,std:: vector<double>>> vectors;
    std:: vector<std::pair< int,std:: vector<double>>> testVectors;
    bool isValid ;
    int vectorSize;

public:
    FileValidate(std::vector<std::string> trainFileVec,std:: vector<std::string> testFileVec);
    void makingTrainVectors(std:: vector<std::string > trainFileVec );
    void makingTestVectors(std:: vector<std::string > testFileVec );
    std:: vector<std::pair< int,std:: vector<double> > > getTestVectors();
    std:: vector<std::pair< std::string,std:: vector<double> > > getVectors();
    int getVectorSize();
    bool getIsValid();
    void makeTrainPair(const std::string line,std::pair<std::string,std::vector<double>> &pairTemp ,std::vector<double> &vecTemp,
                       const char splitter);
    void makeTestPair(const std::string line,std::pair<int,std::vector<double>> &pairTemp ,std::vector<double> &vecTemp,
                      const char splitter,int index);
    void isVecValid(const std::string buffer,std::vector<double> &vecPtr,const char splitter);
    int checkLength(std::string line);
    ~FileValidate();
};






#endif //ADV_PROG_ASS2_FILEVALIDATE_H
