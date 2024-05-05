#ifndef SuperPixelEntry_h
#define SuperPixelEntry_h

#include "ColorLib.h"
#include "../IrrlichtWrapper/Point2D.h"

class SuperPixelEntry
{
public:
	ColorLib color;
	Point2D position;

	int label;
	double distance;

	SuperPixelEntry(ColorLib color, Point2D position) {
		this->color = color;
		this->position = position;

		this->label = -1;
		this->distance = INT32_MAX;
	}
};

#endif