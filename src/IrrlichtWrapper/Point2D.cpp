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

bool Point2D::operator==(const Point2D& a) const
{
	return this->x == a.x && this->y == a.y;
}

bool Point2D::operator<(const Point2D& a) const
{
	if(this->x < a.x && this->y < a.y)
	{
		return true;
	}
	else if(this->x > a.x && this->y > a.y)
	{
		return false;
	}

	double thisDistance = sqrt(pow(this->x,2)+pow(this->y,2));
	double otherDistance = sqrt(pow(a.x,2)+pow(a.y,2));

	return thisDistance < otherDistance;
}