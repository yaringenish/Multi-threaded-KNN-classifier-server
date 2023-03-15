#include <algorithm>
#include "FileValidate.h"
/**
 * Constructor
 * if somewhere along checking the validation of content in the csv file and the input vector
 * we will find validation error we will update the boolean member of the FileValidate object into
 * False and print the right message based of the validation error , to let know the main and the user that
 * something is wrong with the input.
 * @param file fstream file
 * @param inputVectorString string
 */


void FileValidate::makingTestVectors(std:: vector<std::string > testFileVec ){
    this->isValid = true;
    bool stoper = true;
    int index = 0;
    while (stoper && this->isValid) { // doing the same process described above on the other rows of the file till there no rows.
    std::pair<int, std::vector<double>> pairTemp;
    std::vector<double> vecTemp;
    makeTestPair(testFileVec.at(index), pairTemp, vecTemp, ',',index+1);
    if(this->isValid) {
        this->testVectors.push_back(pairTemp);
    }
    index++;
    if(stoper && vecTemp.size()!= this->vectorSize) {
        this->isValid = false;
         continue;
    }
    if(index == testFileVec.size()){
//            this->testVectors.push_back(pairTemp);
            stoper = false;
     }
    }

}
/**
    making pairs from each line of the test file
 * @param line string which is specific line we want to create from her
 * @param pairTemp pair of int which is the number of the line and vector of doubles which is the values of the vector of the line
 * @param vecTemp the vector we put inside the pair which contains double values from line .
 * @param splitter the char ','
 * @param index number of the line from the file
 */
void FileValidate::makeTestPair(const std::string line,std::pair<int,std::vector<double>> &pairTemp ,std::vector<double> &vecTemp,
                                const char splitter, int index) {
    std::stringstream stream(line);
    std::string str;

    int testSize = checkLength(line) + 1;

    for(int i = 0; i < testSize ; i++) {
        getline(stream, str, splitter);
        if(i == testSize -1) {
            std::string temp = "";
            for(int k = 0; k < str.length()-1; k++) {
                temp += str.at(k);
            }
            isVecValid(temp,vecTemp,splitter);
        }
        else {
            isVecValid(str,vecTemp,splitter);
        }
        if(!this->isValid){
//            std::cout << "The file is invalid because its containing vectors with invalid values" << std::endl;
            return;
        }
    }

    /// check if its really string and not number
    pairTemp.first = index;
    pairTemp.second = vecTemp;
}

/**
 * putting all the lines from train file in vector of strings.
 * @param testFileVec vector of strings
 */
void FileValidate::makingTrainVectors(std::vector<std::string >trainFileVec ){
    // first we will take the first row of the csv file and based on it we will know that
    // the size of the others line should be.
    this->isValid = true;
    std::string firstVecStr = trainFileVec.front();
    this->vectorSize = checkLength(firstVecStr); // geting the number of the char ',' in string.
    bool stoper = true;
    std::pair<std::string, std::vector<double>> pairFirst;
    std::vector<double> vecFirst;
    // the FileValide will store the csv content in vector of pairs
    // in here we are making the first pair from the first row.
    makeTrainPair(firstVecStr,pairFirst,vecFirst,',');
    if(this->isValid){ // if the first row is valid
        this->vectors.push_back(pairFirst);
        int index = 1;
        while (stoper && this->isValid) {// doing the same process described above on the other rows of the file till there no rows.
            std::pair<std::string, std::vector<double>> pairTemp;
            std::vector<double> vecTemp;
//            insertTrainPair(pairTemp,vecTemp,trainFileVec.at(index),stoper);
            makeTrainPair(trainFileVec.at(index), pairTemp, vecTemp, ',');
            if(this->isValid) {
                this->vectors.push_back(pairTemp);
            }
            index++;
            if(stoper && vecTemp.size()!= this->vectorSize) {
                this->isValid = false;
                //std::cout << "The file is invalid because its containing vectors with different length" << std::endl;
                continue;
            }
            if(index == trainFileVec.size()){
//                this->vectors.push_back(pairTemp);
                stoper = false;
            }
        }
    }
}

/**
    making pairs from each line of the train file
 * @param line string which is specific line we want to create from her
 * @param pairTemp pair of int which is the number of the line and vector of doubles which is the values of the vector of the line
 * @param vecTemp the vector we put inside the pair which contains double values from line .
 * @param splitter the char ','
 */
void FileValidate::makeTrainPair(const std::string line,std::pair<std::string,std::vector<double>> &pairTemp ,std::vector<double> &vecTemp,
                                 const char splitter) {
    std::stringstream stream(line);
    std::string str;
    for(int i = 0; i < this->vectorSize+1 ; i++) {
        getline(stream, str, splitter);
        if (i != this->vectorSize) {
            // check if the str value is valid for vector values.
            // if it is valid inserting it to vecTemp.
            isVecValid(str,vecTemp,splitter);
            if(!this->isValid){
                //std::cout << "The file is invalid because its containing vectors with invalid values" << std::endl;
                return;
            }
        }
        else
            /// check if its really string and not number
            pairTemp.first = str;
    }
    pairTemp.second = vecTemp;
}

/**
 * constructor
 * @param trainFileVec strings vector of the train file
 * @param testFileVec strings vector of the test file
 */
FileValidate::FileValidate(std:: vector<std::string > trainFileVec,std:: vector<std::string > testFileVec){
        makingTrainVectors(trainFileVec);
        if(this->isValid){
            makingTestVectors(testFileVec);
            }
}

/**
 * The func will iterate over the string buffer and divide him by the char splitter.
 * If the divided string has double values the func will convert it to double and insert it to vec,
 * otherwise well turn isValid boolean member of FileValidate object to false and will finish the func.
 * @param buffer string
 * @param vec  vector
 * @param splitter char (commonly ',' or ' ' )
 */
void FileValidate::isVecValid(const std::string buffer,std::vector<double> &vec,
                          const char splitter) {
    std::stringstream stream(buffer);
    std::string str;
    while (std::getline(stream, str, splitter)) {
        bool isDot = false;
        for (int i = 0; i < str.length(); i++) {
            // if there are two dots
            if(str[i] == '.' && isDot) {
                this->isValid = false;

                std::cout << "1\n";

                return;
            }
            //if there is the char 'e' or 'E' without '-' or '+' after
            if (isdigit(str[i]) == false && i + 2 <= str.length() && (str[i] == 'E' || str[i] == 'e')
                && !(str[i+1] == '+' || str[i+1] == '-')){
                this->isValid = false;
                std::cout << "2\n";
                return;
            }
            // if there is the char '-' or '+' without 'e' or 'E' before
            if (i!= 0 && isdigit(str[i]) == false && i + 1 <= str.length() && (str[i] == '-' || str[i] == '+')
                && !(str[i-1] == 'E' || str[i-1] == 'e')){
                this->isValid = false;
                std::cout << "3\n";
                return;
            }
            // if there is a char that shouldn't be in the vector
            if(isdigit(str[i]) == false && str[i] != '.' && str[i] != '-' && str[i] != 'E'
                && str[i] != 'e' && str[i]!= '+') {
                this->isValid = false;
                return;
            }
            // if current char is dot , turn isDot flag on for the check of the next char.
            if (str[i] == '.')
                isDot = true;
        }
        // if the string after splitting him is not empty insert the value of the string
        // as double type into the vector.
        if(str != "") {
            isDot = false;
            try{
                char *c;
                char temp[str.size() + 1];
                strcpy(temp, str.c_str());
                double num = strtod(reinterpret_cast<const char *>(&temp), &c);
                vec.push_back(num);
            }
            catch(std::exception& e) {
                this->isValid = false;
                return;
            }
        }
    }
}

/**
 *
 * @return The DB of the csv file - vector of pairs, which each pair made from string and vector of doubles.
 */
std::vector<std::pair< std::string,std:: vector<double>>> FileValidate::getVectors(){
    return this->vectors;
}

std::vector<std::pair< int,std:: vector<double>>> FileValidate::getTestVectors(){
    return this->testVectors;
}
/**
 * Getter
 * @return boolean - indicating if till now the DB and the input vector are valid.
 */
bool FileValidate::getIsValid() {
    return this->isValid;
}
/**
 * Getter
 * @return int - number of double values should be in each vector.
 */
int FileValidate::getVectorSize(){
    return this->vectorSize;
}
/**
 *
 * @param line string
 * @return count - number of ',' chars in the line.
 */
int FileValidate::checkLength(std::string line){
    int count = 0;
    for (int i = 0; i < line.size(); i++)
        if (line[i] == ',')
            count++;
    return count;
}
/**
 * distractor
 */
FileValidate::~FileValidate() {}


