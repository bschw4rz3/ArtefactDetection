#ifndef HogCellResult_H
#define HogCellResult_H

#include <map>
#include <vector>

#include "../IrrlichtWrapper/Point2D.h"

class HogCellResult
{
public:
	std::map<Point2D, std::vector<double>> cellResults;
	Point2D lastPoint;

	HogCellResult(std::map<Point2D, std::vector<double>> cellResults, Point2D lastPoint)
	{
		this->cellResults = cellResults;
		this->lastPoint = lastPoint;
	}
};

#endif