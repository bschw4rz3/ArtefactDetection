#ifndef DefectGenerationService_H
#define DefectGenerationService_H

#pragma warning(disable:4146)
#pragma warning(disable:4996)

#define cimg_use_png

#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <regex>
#include <conio.h>
#include <direct.h>
#include <iostream>
#include <fstream>

#include <format>
#include <iostream>
#include <chrono>
#include <string> 
#include "header/DrawCalculations.h"
#include "header/RandomService.h"
#include "header/DrawBumpCalculations.h"
#include "header/Anomaly.h"


class DefectGenerationService
{
public:
	void generateAnomalieDirectories(std::string dirPath, int iterationCount, int countOfAnomalies = -1, int cutImageSize = -1);

private:
	bool contains(std::vector<AnomalyType> list, AnomalyType type);
	bool containsWithePixels(CImg<unsigned char> &tmp);
	std::string getTestdataImagePath(std::vector<AnomalyType> anomalyTypeList, int index, std::string path);
	std::string saveImage(CImg<unsigned char>& tmp, int wx, int hy, int size_z, int size_c, std::vector<AnomalyType>& anomalyTypeList, int& index, std::string dirPath);
	void cutSubPics(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int w, int h, int size_z, int size_c, std::string dirPath);
	void cutAnomalies(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int w, int h, int size_z, int size_c, std::string dirPath);
	void cutAnomaliesWithSize(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int size_z, int size_c, int cutImageSize, std::string dirPath);
};

#endif