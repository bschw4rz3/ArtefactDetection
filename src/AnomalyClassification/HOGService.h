#ifndef HOGService_H
#define HOGService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <math.h>
#include <map>

#include "ClassicSobelOperatorService.h"
#include "CImgService.h"
#include "MathSerivce.h"

#include "../IrrlichtWrapper/Point2D.h"
#include "ColorRGB.h"
#include "HogCellResult.h"

class HOGService
{
private:
	ClassicSobelOperatorService* sobelService;
	CImgService* cImgService;
	MathSerivce* mathService;

public:
	HOGService(ClassicSobelOperatorService* sobelService, CImgService * cImgService, MathSerivce* mathService);

	std::vector<double> calculate(const CImg<unsigned char>* image, int blockSize = 3, int maxPixelLengthPerCell = 8, int bins = 9);

private:
	std::vector<double> calculateGradientenMagnitude(const CImg<unsigned char>* partImage, const std::vector<double>& degreeBins);
	HogCellResult calculateCells(const CImg<unsigned char>* image, int maxPixelLengthPerBlock, int bins);

	double calculateGradientX(const CImg<unsigned char>* partImage, int x, int y);
	double calculateGradientY(const CImg<unsigned char>* partImage, int x, int y);

	std::vector<double> getDegreeBins(int binCount);
	int getBin(double degree, const std::vector<double>& degreeBins);

	std::vector<double> norm(const std::vector<double>& blockHistogram);
};

#endif