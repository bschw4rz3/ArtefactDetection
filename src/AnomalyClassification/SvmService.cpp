#include "SvmService.h"

std::vector<DataPoint> SvmService::classify(std::vector<DataPoint>& trainingsData, std::vector<std::vector<double>>& testData)
{
    std::vector<DataPoint> result;

    std::vector<std::vector<std::complex<double>>> trainingsFeature = this->getFeature(trainingsData);
    std::vector<std::vector<std::complex<double>>> testFeature = this->toComplex(testData);
    std::vector<std::complex<double>> trainingsLabel = this->getLabels(trainingsData);

    std::vector<int> testLabel = this->classify(trainingsFeature, testFeature, trainingsLabel);

    for (int i = 0 ; i < testLabel.size(); i++)
    {
        DataPoint dataPoint;

        dataPoint.features = testData[i];
        dataPoint.label = testLabel[i];

        result.push_back(dataPoint);
    }

    return result;
}

std::vector<int> SvmService::classify(std::vector<std::vector<std::complex<double>>> trainingsFeatures, std::vector<std::vector<std::complex<double>>> testFeatures, std::vector< std::complex<double>> classes)
{
    std::string trainingsJson = this->tempFileNameService->generateFileNameJson();
    std::string testJson = this->tempFileNameService->generateFileNameJson();
    std::string targetJson = this->tempFileNameService->generateFileNameJson();

    std::string trainingsFeatureParameter = this->getParameter(trainingsFeatures);
    this->fileSerivce->saveFile(trainingsFeatureParameter, trainingsJson);

    std::string testFeature = this->getParameter(testFeatures);
    this->fileSerivce->saveFile(testFeature, testJson);

    std::string classeParameter = this->getParameter(classes);
    this->fileSerivce->saveFile(classeParameter, targetJson);

    std::string scriptName = this->getScriptName();
    std::string comand = "python " + this->directoryPath + scriptName + " " + trainingsJson + " " + testJson + " " + targetJson;
    //std::string comand = "dir";

    std::string consoleResult = this->exec(comand.c_str());

    std::vector<char> symbols = { '[', ']' };
    this->stringService->trim(consoleResult, symbols);

    std::vector<int> intClassVector;
    std::vector<std::string> classVector = this->stringService->split(consoleResult, ',');

    for (std::string stdClass : classVector)
    {
        std::vector<char> symbols = { '\'' };
        this->stringService->trim(stdClass, symbols);

        int intClass = this->stringService->toInt(stdClass);
        intClassVector.push_back(intClass);
    }

    std::remove(trainingsJson.c_str());
    std::remove(testJson.c_str());
    std::remove(targetJson.c_str());

    //return this->toList(resultJson);
    return intClassVector;
}

std::vector<std::vector<std::complex<double>>> SvmService::getFeature(std::vector<DataPoint>& trainingData)
{
    std::vector<std::complex<double>> classes;
    std::vector<std::vector<std::complex<double>>> features;

    for (int i = 0; i < trainingData.size(); i++)
    {
        DataPoint testPoint = trainingData[i];

        std::vector<std::complex<double>> complexFeature;

        for (double value : testPoint.features)
        {
            complexFeature.push_back(value);
        }
        features.push_back(complexFeature);
        classes.push_back(testPoint.label);
    }

    return features;
}

std::vector<std::complex<double>> SvmService::getLabels(std::vector<DataPoint>& trainingData)
{
    std::vector<std::complex<double>> classes;
    std::vector<std::vector<std::complex<double>>> features;

    for (int i = 0; i < trainingData.size(); i++)
    {
        DataPoint testPoint = trainingData[i];

        std::vector<std::complex<double>> complexFeature;

        for (double value : testPoint.features)
        {
            complexFeature.push_back(value);
        }
        features.push_back(complexFeature);
        classes.push_back(testPoint.label);
    }

    return classes;
}

std::vector<std::vector<std::complex<double>>> SvmService::toComplex(std::vector<std::vector<double>>& testData)
{
    std::vector<std::vector<std::complex<double>>> result;

    for (std::vector<double> testLine : testData)
    {
        std::vector<std::complex<double>> complexLine;

        for (double testValue : testLine)
        {
            complexLine.push_back(std::complex<double>(testValue));
        }

        result.push_back(complexLine);
    }

    return result;
}

std::string SvmService::getScriptName()
{
    return "trainSVM.py";
}