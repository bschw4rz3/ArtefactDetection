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
#include "GeometricService.h"
#include "../IrrlichtWrapper/Point2D.h"

class SdSfService
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	ColorService* colorService;
	MathSerivce* mathSerivce;
	StringSerivce* stringSerivce;
	GeometricService* geometricService;

public:
	SdSfService(ClassicSobelOperatorService* classicSobelOperatorService, GeometricService* geometricService, MathSerivce* mathSerivce, StringSerivce* stringSerivce, ColorService* colorService);

	std::map<std::string, int> calculateSdSf(CImg<unsigned char>* image);

private:
	Point2D calculateCenterPoint(std::vector<Point2D> contureList, ColorRGB backgroundColor);
};

#endif