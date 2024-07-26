#ifndef GeometricService_H
#define GeometricService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ColorService.h"
#include "../IrrlichtWrapper/Point2D.h"

class GeometricService
{
private:
	ColorService* colorService;

public:
	GeometricService(ColorService* colorService);

	int countBlackPixels(CImg<unsigned char>* image);
	int calculateScope(CImg<unsigned char>* image);
	Point2D calculateDefectFocus(CImg<unsigned char>* image);
	double calculateRectangularity(CImg<unsigned char>* image);

private:
	bool isboarderPixel(CImg<unsigned char>* image, int x, int y);
};

#endif