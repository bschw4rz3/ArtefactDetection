#ifndef ColorService_H
#define ColorService_H

#include "math.h"

#include "ColorRGB.h"
#include "ColorLib.h"

class ColorService
{
public:
	ColorLib rgb2lab(ColorRGB color);
	ColorRGB byte2rgb(const unsigned char* ptr, int imageWidth, int imageHeight);
	const unsigned char* rgb2byte(ColorRGB color);

private:
	double rgb2lab_normalizeRgbChannel(double channel);
	double rgb2lab_normalizeXyzChannel(double channel);
};

#endif