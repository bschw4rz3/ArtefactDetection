#include "../header/CalculationService.h"

PixelPosition CalculationService::rotation(PixelPosition position, double radiantAngel)
{
	double x = position.x;
	double y = position.y;

	double angledX = round(x * cos(radiantAngel) - y * sin(radiantAngel));
    double angledY = round(x * sin(radiantAngel) + y * cos(radiantAngel));

	return PixelPosition(angledX, angledY);
}

double CalculationService::toRadiant(double degree)
{
	double anglePI = degree / 180 * M_PI;
	return anglePI;
}

