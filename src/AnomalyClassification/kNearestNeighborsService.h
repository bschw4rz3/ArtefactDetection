#ifndef kNearestNeighborsService_H
#define kNearestNeighborsService_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

struct DataPoint {
    std::vector<double> features;  // Merkmale
    int label;                // Klassenlabel
};

class KNearestNeighborsService
{
public:
    std::vector<DataPoint> classify(std::vector<DataPoint> trainingData, std::vector<std::vector<double>> testData, int k);

private:
    double euclideanDistance(const std::vector<double>& p1, const std::vector<double>& p2);
    int classifyKNN(const std::vector<DataPoint>& trainingData, const DataPoint& testPoint, int k);
};

#endif