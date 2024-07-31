#ifndef GeometricService_H
#define GeometricService_H

#include <map>
#include <vector>

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

	ColorRGB getBackgroundColor(CImg<unsigned char>* image);

	int countDefectPixels(CImg<unsigned char>* image, ColorRGB backgroundColor);
	int calculateScope(CImg<unsigned char>* image, ColorRGB backgroundColor);
	Point2D calculateDefectFocus(CImg<unsigned char>* image, ColorRGB backgroundColor);
	double calculateRectangularity(CImg<unsigned char>* image, ColorRGB backgroundColor);

	std::vector<Point2D> getConturePixelPositions(CImg<unsigned char>* image, ColorRGB backgroundColor);
	double getPixelPositionWithMinDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor);
	double getPixelPositionWithMaxDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor);
	double calculateDistance(Point2D point, Point2D center);

private:
	bool isboarderPixel(CImg<unsigned char>* image, int x, int y);
};

#endif