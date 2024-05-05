#ifndef ColorService_H
#define ColorService_H

#include "math.h"

#include "ColorRGB.h"
#include "ColorLib.h"

class ColorService
{
public:
	ColorLib rgb2lab(ColorRGB color);

private:
	double rgb2lab_normalizeRgbChannel(double channel);
	double rgb2lab_normalizeXyzChannel(double channel);
};

#endif