#ifndef SdSfService_H
#define SdSfService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <vector>
#include <map>
#include <string>
#include <format>

#include "ClassicSobelOperatorService.h"
#include "ColorService.h"
#include "MathSerivce.h"
#include "StringSerivce.h"
#include "../IrrlichtWrapper/Point2D.h"

class SdSfService
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	ColorService* colorService;
	MathSerivce* mathSerivce;
	StringSerivce* stringSerivce;

public:
	SdSfService(ClassicSobelOperatorService* classicSobelOperatorService, MathSerivce* mathSerivce, StringSerivce* stringSerivce, ColorService* colorService);

	std::map<std::string, int> calculateSdSf(CImg<unsigned char>* image);

private:
	double getMinDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor);
	double getMaxDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor);

	Point2D calculateCenterPoint(std::vector<Point2D> contureList, ColorRGB backgroundColor);
	double calculateDistanceToCenter(Point2D point, Point2D center);

	std::vector<Point2D> getConture(CImg<unsigned char>* image, ColorRGB backgroundColor);
};

#endif