//
// Created by yarin on 12/01/2023.
//

#ifndef ADV_PROG_ASS4_ELEMENTS_H
#define ADV_PROG_ASS4_ELEMENTS_H
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "Knn.h"
#include "KnnEuclidean.h"
#include "KnnManhattan.h"
#include "KnnChebyshev.h"
#include "KnnCanberra.h"
#include "KnnMinkowski.h"
#include "FileValidate.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include <thread>

class Elements {
private:
    FileValidate* fv;
    int k;
    std::string distType;
    std:: vector<std::pair< int,std::string>>* classifiedVectors;
    int maxK;
    bool isUpload;
public:
    /**
 * This method is the constructor of the Elements class.
 * It initializes the the class members.
 */
    Elements();

    /**
 * This is a setter method to set the maxK member. It represents the number of the rows in the
 * train vectors file.
 * @param maxK int type.
 */
    void setMaxK(int maxK);

    /**
 * This is a setter method to set the fv member.
 * @param fv FileValidate* type.
 */
    void setFile(FileValidate* fv);

    /**
 * This is a method to set the k member of the class.
 * @param k int type.
 */
    void setK(int k);

    /**
 * This is a setter method to set the distType.
 * @param distType string type.
 */
    void setDistType(std::string distType);

    /**
 * This is a setter method to set the classifiedVectors.
 * @param classifiedVectors std::vector <std::pair<int, std::string>>* type.
 */
    void setClassifiedVectors(std:: vector<std::pair< int,std::string>>* classifiedVectors);

    /**
 * This is a getter method to get the fv member.
 * @return FileValidate* type.
 */
    FileValidate* getFv();

    /**
 * This is a getter method to get the current k.
 * @return int type.
 */
    int getK();

    /**
 * This is getter method to get the maxK
 * @return int type.
 */
    int getMaxK();

    /**
 * This is a getter method to get the current distType.
 * @return distType string type.
 */
    std::string getDistType();

    /**
 * This is a getter method to get the ClassifiedVectors.
 * @return classifiedVectors member, std:: vector<std::pair< int,std::string>>* type.
 */
    std:: vector<std::pair< int,std::string>>* getClassifiedVectors();

    /**
 * This is a setter method to set the isUpload member.
 * @param val , bool type.
 */
    void setIsUpload(bool val);

    /**
 * This is a getter method to get the isUpload member.
 * @return isUpload, bool type.
 */
    bool getIsUpload();

    /**
 * This method is the destructor of the Elements class.
 */
    ~Elements();
};


#endif //ADV_PROG_ASS4_ELEMENTS_H
