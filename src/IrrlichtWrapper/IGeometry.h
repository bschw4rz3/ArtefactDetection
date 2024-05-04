#ifndef IGeometry_H
#define IGeometry_H

#include <vector>
#include "IrrPoint.h"

class IGeometry
{
public:
	virtual bool isOnSurface(IrrPoint point) = 0;
	virtual std::vector<IrrPoint> getContour(double scale) = 0;

	virtual double getMaxY() = 0;
	virtual double getMinY() = 0;
};

#endif