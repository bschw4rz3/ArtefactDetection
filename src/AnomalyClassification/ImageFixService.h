#ifndef ImageFixService_H
#define ImageFixService_H

#include <vector>
#include <string>

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "GeometricService.h"
#include "ColorService.h"
#include "TempFileNameService.h"
#include "../IrrlichtWrapper/Point2D.h"
#include "../AnomalyClassification/BackgoundResult.h"

class ImageFixService
{
private:
	GeometricService* geometricService;
	ColorService* colorService;
	TempFileNameService* tempFileNameService;

public:
	ImageFixService(GeometricService* geometricService, ColorService* colorService, TempFileNameService* tempFileNameService);

	void fixImage(CImg<unsigned char>* img, std::string outFileName);

private:
	std::vector<Point2D> getPartBorders(CImg<unsigned char>* img);
};

#endif