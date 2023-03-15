#include "Knn.h"
#include <vector>
#include <string>
/**
 * Constructor
 * @param inputVector input vector - double values vector
 * @param vectors The data from the csv file -vector of pairs which each pair contain string and double values vector
 * @param k int - number of wanted closest neighbors.
 * @param vectorSize int - number of double values in each of vector inside each pair in vectors member of Knn.
 */
    Knn::Knn(std:: vector<double> inputVector,std:: vector<std::pair< std::string,std:: vector<double>>> vectors, int k,int vectorSize){
        this->inputVector = inputVector;
        this->vectors = vectors;
        this->k = k;
        this->vectorSize = vectorSize;
    }
/**
* Getter
* @return  k
*/    
    int Knn::getK(){
        return this->k;
    }
/**
 * Getter
 * @return The DB of the csv file - vector of pairs, which each pair made from string and vector of doubles.
 */
    std::vector<std::pair<std::string,std:: vector<double>>>  Knn::getVectors(){
        return this->vectors;
    }







