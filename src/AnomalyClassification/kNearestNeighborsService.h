#ifndef kNearestNeighborsService_H
#define kNearestNeighborsService_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "DataPoint.h"

class KNearestNeighborsService
{
public:
    std::vector<DataPoint> classify(std::vector<DataPoint> trainingData, std::vector<std::vector<double>> testData, int k);

private:
    double euclideanDistance(const std::vector<double>& p1, const std::vector<double>& p2);
    int classifyKNN(std::vector<DataPoint>& trainingData, DataPoint& testPoint, int k);
};

#endif