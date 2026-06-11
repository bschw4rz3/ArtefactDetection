#ifndef BackgroundResult_H
#define BackgroundResult_H

#include <vector>

#include "ColorService.h"
#include "../IrrlichtWrapper/Point2D.h"

class BackgroundResult
{
public:
	std::vector<Point2D> pointList;
	std::vector<ColorRGB> colorList;

	BackgroundResult(std::vector<Point2D> pointList, std::vector<ColorRGB> colorList)
	{
		this->pointList = pointList;
		this->colorList = colorList;
	}
};

#endif