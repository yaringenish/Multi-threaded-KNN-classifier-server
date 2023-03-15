

#ifndef ADV_PROG_ASS2_KNNCANBERRA_H
#define ADV_PROG_ASS2_KNNCANBERRA_H
#include "Knn.h"

/**
 * This is the Knn Canberra class, it finds the k closest vectors to the input vector
 * using the Canberra distance calculate method.
 */
class KnnCanberra : public Knn{
public:
    /**
     * Constructor method to initiate the KnnCanberra object.
     * @param inputVector std:: vector<double> type
     * @param vectors std:: vector<double> type
     * @param k int type
     * @param vectorSize int type
     */
    KnnCanberra(std:: vector<double> inputVector,std:: vector<std::pair< std::string,
            std:: vector<double> > > vectors, int k,int vectorSize);
    /**
     * This method calculates the distance using the Canberra calculation.
     * @param v1 std:: vector<double> type
     * @param v2 std:: vector<double> type
     * @return the result of the calculation, double type.
     */
    double compute(std::vector<double> &v1, std::vector<double> &v2);
    /**
     * This is a comparator function, the generic sort method from stl library
     * gets this method and uses it to sort according to the shortest distance.
     * @param p1 std::vector<double> type
     * @param p2 std::vector<double> type
     * @return returns true if v1 distance is shorter, returns false if v2 distance is shorter.
     */
    bool greater(std::pair <std::string , std::vector<double> > p1 ,std::pair<std::string ,std::vector<double> > p2);
    /**
     * This method prints the type of the input vector after calculating the k closest vectors
     * and checking the most common vector type in the k closest vectors.
     */
    std::string printResult();
    /**
     * This method checks which type is the most common type in the k closest vectors.
     * @return the result as string.
     */
    std::string mostTimes ();
};


#endif //ADV_PROG_ASS2_KNNCANBERRA_H
