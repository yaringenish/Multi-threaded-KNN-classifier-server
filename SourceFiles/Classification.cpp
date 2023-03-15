//
// Created by yarin on 12/01/2023.
//

#include "Classification.h"
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
#include "CLI.h"
#include "Elements.h"
#include <vector>



/**
 * constructor
 * @param dio default io
 * @param fv file validate object including train and test vectors
 * @param distType string of distance method
 * @param k int as number of wanted neighbors
 */
Classification::Classification(DefaultIO* dio,FileValidate* fv,std::string distType,int k ){
    this->description = "";
    this->dio = dio;
    this->fv = fv;
    this->distType = distType;
    this->k = k;
}
/**
 * This method creates a knn type according to the client's choose and inserting the classified
 * vectors into pairs based on their line from test file.
 * @param choose std::string type, represents the client's distance calculation choose.
 * @param fv FileValidate type.
 * @param k int type.
 */
void Classification::knnSwitch(std::string choose, FileValidate* fv, int k){
    if (std::strcmp(choose.c_str(), "AUC") == 0) {

        int size = this->fv->getTestVectors().size();
        for(int index = 1;index <= size; index++){


            std:: vector<double> currVec = this->fv->getTestVectors().at(index-1).second;
            KnnEuclidean knn =  KnnEuclidean(currVec,this->fv->getVectors(),this->k,this->fv->getVectorSize());
            std::string result = knn.printResult();
            std::pair< int,std::string> pair;
            pair.first = index;
            pair.second = result;
            this->classifiedVectors.push_back(pair);
        }

    }
    if (std::strcmp(choose.c_str(), "MAN") == 0) {
        int size = this->fv->getTestVectors().size();
        for(int index = 1;index <= size; index++){
            std:: vector<double> currVec = this->fv->getTestVectors().at(index-1).second;
            KnnManhattan knn = KnnManhattan(currVec,this->fv->getVectors(),this->k,this->fv->getVectorSize());
            std::string result = knn.printResult();
            std::pair< int,std::string> pair;
            pair.first = index;
            pair.second = result;
            this->classifiedVectors.push_back(pair);
        }
    }
    if (std::strcmp(choose.c_str(), "CHB") == 0) {
        int size = this->fv->getTestVectors().size();
        for(int index = 1;index <= size; index++){
            std:: vector<double> currVec = this->fv->getTestVectors().at(index-1).second;
            KnnChebyshev knn = KnnChebyshev(currVec,this->fv->getVectors(),this->k,this->fv->getVectorSize());
            std::string result = knn.printResult();
            std::pair< int,std::string> pair;
            pair.first = index;
            pair.second = result;
            this->classifiedVectors.push_back(pair);
        }
    }
    if (std::strcmp(choose.c_str(), "CAN") == 0) {
        int size = this->fv->getTestVectors().size();
        for(int index = 1;index <= size; index++){
            std:: vector<double> currVec = this->fv->getTestVectors().at(index-1).second;
            KnnCanberra knn = KnnCanberra(currVec,this->fv->getVectors(),this->k,this->fv->getVectorSize());
            std::string result = knn.printResult();
            std::pair< int,std::string> pair;
            pair.first = index;
            pair.second = result;
            this->classifiedVectors.push_back(pair);
        }
    }
    if (std::strcmp(choose.c_str(), "MIN") == 0) {
        int size = this->fv->getTestVectors().size();
        for (int index = 1; index <= size; index++) {
            std:: vector<double> currVec = this->fv->getTestVectors().at(index-1).second;
            KnnMinkowski knn = KnnMinkowski(currVec, this->fv->getVectors(), this->k, this->fv->getVectorSize());
            std::string result = knn.printResult();
            std::pair < int, std::string> pair;
            pair.first = index;
            pair.second = result;
            this->classifiedVectors.push_back(pair);
        }
    }
}

/**
 * classification of the test vectors.
 * @param elements Elements object(description in the class)
 */
void Classification:: execute(Elements* elements){
    this->classifiedVectors.clear();
    knnSwitch(this->distType,this->fv,this->k);
    this->dio->write("classifying data complete\n");
    elements->setClassifiedVectors(&(this->classifiedVectors));
}
/**
 * default constructor
 */
Classification::Classification() {}
/**
 * constructor
 */
Classification::~Classification(){}