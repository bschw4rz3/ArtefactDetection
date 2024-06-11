#ifndef GeometricService_H
#define GeometricService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ColorService.h"

class GeometricService
{
private:
	ColorService* colorService;

public:
	GeometricService(ColorService* colorService);

	int countBlackPixels(CImg<unsigned char> img);


};

#endif