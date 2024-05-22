#ifndef SobelOperator_H
#define SobelOperator_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <math.h>
#include <map>

#include "ColorService.h"
#include "ColorRGB.h"
#include "KeyValuePair.h"

class ImprovedSobelOperatorService
{
private:
	ColorService* colorService;

public:
	ImprovedSobelOperatorService(ColorService* colorService);

	CImg<unsigned char> getGradientImage(const CImg<unsigned char>& image);

private:
	void setPixel(CImg<unsigned char>& image, int x, int y, ColorRGB color);
	ColorRGB getPixel(const CImg<unsigned char>& image, int x, int y);
};

#endif