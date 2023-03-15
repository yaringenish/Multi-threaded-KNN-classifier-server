#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <cstring>
#include <utility>
#ifndef MITKADEM12_KNN_H
#define MITKADEM12_KNN_H
/**
 * Knn will play a role as an abstract class for the different methods of calculating distance ,
 * which each method will be a derived class from Knn abstract class.
 * This way Knn will let us do operations such as compute from his sons classes without even knowing
 * which specific son class we are computing from. More then that this way we can contain
 * different type of knn sons in the same data structure, thing the can be very useful for further
 * complex tasks.
 */
class Knn {
protected:
    std:: vector<double> inputVector;
    std:: vector<std::pair< std::string,std:: vector<double> > > vectors;
    int k;
    int vectorSize;
public:
/**
 * Constructor
 * @param inputVector input vector - double values vector
 * @param vectors The data from the csv file -vector of pairs which each pair contain string and double values vector
 * @param k int - number of wanted closest neighbors.
 * @param vectorSize int - number of double values in each of vector inside each pair in vectors member of Knn.
 */
    Knn(std:: vector<double> inputVector,std:: vector<std::pair< std::string,std:: vector<double> > > vectors, int k,int vectorSize);
/**
 * Getter
 * @return The DB of the csv file - vector of pairs, which each pair made from string and vector of doubles.
 */
    std:: vector<std::pair<std::string,std:: vector<double> > > getVectors();
/**
* Getter
* @return  k
*/
    int getK();

    virtual double compute(std::vector<double> &v1, std::vector<double> &v2) = 0;
    virtual bool greater(std::pair <std::string , std::vector<double> > p1 ,std::pair<std::string ,std::vector<double> > p2) = 0;
    virtual std::string printResult() = 0;

};


#endif //MITKADEM12_KNN_H