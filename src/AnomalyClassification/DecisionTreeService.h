#ifndef DecisionTreeService_H
#define DecisionTreeService_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "DataPoint.h"
#include "PythonExecuter.h"


class DecisionTreeService : PythonExecuter
{
public:
    DecisionTreeService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) : PythonExecuter(stringService, tempFileNameService, fileSerivce)
    {

    }

    std::vector<DataPoint> classify(std::vector<DataPoint>& trainingsData, std::vector<std::vector<double>>& testData);
    
protected:
    std::vector<int> classify(std::vector<std::vector<std::complex<double>>> trainingsFeatures, std::vector<std::vector<std::complex<double>>> testFeatures, std::vector< std::complex<double>> classes);

    std::string getScriptName();

private:
    std::vector<std::vector<std::complex<double>>> toComplex(std::vector<std::vector<double>>& testData);
    std::vector<std::vector<std::complex<double>>> getFeature(std::vector<DataPoint>& trainingData);
    std::vector<std::complex<double>> getLabels(std::vector<DataPoint>& trainingData);
  
};

#endif // !DecisionTreeService_H
