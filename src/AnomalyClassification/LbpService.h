#ifndef LbpService_H
#define LbpService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <string>

#include "ColorService.h"
#include "GeometricService.h"
#include "ColorRGB.h"
#include "MathSerivce.h"
#include "LbpResult.h"
#include "LbpHistogramResult.h"

class LbpService
{
private:
	ColorService* colorSerivce;
	GeometricService* geometricService;
	MathSerivce* mathSerivce;

public:
	LbpService(GeometricService* geometricService, MathSerivce* mathSerivce, ColorService* colorSerivce);

public:
	LbpHistogramResult calculateLbpHistogram(CImg<unsigned char>* image, int samplePoints, double pixelRadius);

protected:
	LbpResult calculateLbp(CImg<unsigned char>* image, Point2D centerPosition, int samplePoints, double pixelRadius);

	virtual int functionS(double value);
	virtual Point2D calculatePoint(Point2D center, double radius, int p, int samplePoints);
	virtual std::string getUniformityString(int uniformity);
};

#endif