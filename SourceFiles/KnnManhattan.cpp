#include "KnnManhattan.h"
#include "Knn.h"
#include <algorithm>
/**
 * Constructor method to initiate the KnnManhattan object.
 * @param inputVector std:: vector<double> type
 * @param vectors std:: vector<double> type
 * @param k int type
 * @param vectorSize int type
 */
KnnManhattan::KnnManhattan(std:: vector<double> inputVector,std:: vector<std::pair< std::string,
        std:: vector<double>>> vectors, int k,int vectorSize): Knn(inputVector,vectors,k,vectorSize){}
/**
 * This method calculates the distance using the Manhattan calculation.
 * @param v1 std:: vector<double> type
 * @param v2 std:: vector<double> type
 * @return the result of the calculation, double type.
 */
double KnnManhattan::compute(std::vector<double> &v1, std::vector<double> &v2){
    double dist = 0;
    int length = v1.size();
    for (int i = 0; i < length; i++) {
        double temp = std::abs(v1.at(i) - v2.at(i));
        dist = dist + temp;
    }
    return dist;
}
/**
 * This is a comparator function, the generic sort method from stl library
 * gets this method and uses it to sort according to the shortest distance.
 * @param p1 std::vector<double> type
 * @param p2 std::vector<double> type
 * @return returns true if v1 distance is shorter, returns false if v2 distance is shorter.
 */
bool KnnManhattan::greater(std::pair <std::string , std::vector<double>> p1 ,std::pair<std::string ,std::vector<double>> p2){
    double v1Dist = compute(p1.second, this->inputVector);
    double v2Dist = compute(p2.second, this->inputVector);
    return (v1Dist < v2Dist);
}
/**
 * This method checks which type is the most common type in the k closest vectors.
 * @return the result as string.
 */
std::string KnnManhattan::mostTimes () {
    std::vector<std::pair<std::string, int>> arr;
    bool isInside = false;
    ///Iterates over the first k vectors in the vectors db and counts each type.
    for(int i = 0; i < this->k; i++) {
        for(int j = 0; j < arr.size(); j ++) {
            if(std::strcmp(arr.at(j).first.c_str(), this->vectors.at(i).first.c_str()) == 0 ) {
                arr.at(j).second += 1;
                isInside = true;
            }
        }
        /// adds the type to the counters vector if it is not already inside.
        if(!isInside) {
            std::pair<std::string, int> temp;
            temp.first = this->vectors.at(i).first;
            temp.second = 1;
            arr.push_back(temp);
        }
    }
    std::string result = "";
    int max = 0;
    /// checks which type has the max counter.
    for(int i = 0; i < arr.size(); i++) {
        if(arr.at(i).second > max) {
            max = arr.at(i).second;
            result = arr.at(i).first;
        }
    }
    return result;
}
/**
 * This method prints the type of the input vector after calculating the k closest vectors
 * and checking the most common vector type in the k closest vectors.
 */
std::string KnnManhattan::printResult(){
    /// sort the vectors using compute and greater methods.
    sort(this->vectors.begin(),this->vectors.end(), [this] (std::pair <std::string , std::vector<double>> a,
                                                std::pair <std::string , std::vector<double>> b) {
        return greater(a, b); });
    /// using mostTimes method to check which type is the most common type in the k closest vectors.
    return(mostTimes());
}


void KnnManhattan::setInputVector(std:: vector<double> inputVector){
    this->inputVector = inputVector;
}