#include "Point2D.h"

Point2D::Point2D()
{
	this->x = 0;
	this->y = 0;
}

Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Point2D::operator==(Point2D a)
{
	return this->x == a.x && this->y == a.y;
}