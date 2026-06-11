#ifndef HistogramValueService_H
#define HistogramValueService_H

#include <vector>
#include <map>

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <math.h>

#include "ColorService.h"
#include "../IrrlichtWrapper/Point2D.h"
#include "KeyValuePair.h"

class HistogramValueService
{
private:
	static int lastImageX;
	static int lastImageY;

	ColorService* colorService;

public:
	HistogramValueService(ColorService* colorService);

public:
	double getMean(CImg<unsigned char>* image);
	double getVariance(CImg<unsigned char>* image);
	double getSkewness(CImg<unsigned char>* image);
	double getKurtosis(CImg<unsigned char>* image);
	double getPower(CImg<unsigned char>* image);
	double getEntropy(CImg<unsigned char>* image);

private:
	std::map<ColorRGB, double> getHistogram(CImg<unsigned char>* image);
};

#endif