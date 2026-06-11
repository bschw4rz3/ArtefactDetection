#ifndef SuperPixelEntry_h
#define SuperPixelEntry_h

#include "ColorLib.h"
#include "../IrrlichtWrapper/Point2D.h"

class SuperPixelEntry
{
public:
	ColorLib color;
	Point2D position;

	double distance;

	int label;
	int subregionLabel;

	SuperPixelEntry(ColorLib color, Point2D position) {
		this->color = color;
		this->position = position;

		this->distance = INT32_MAX;

		this->label = -1;
		this->subregionLabel = -1;
	}
};

#endif