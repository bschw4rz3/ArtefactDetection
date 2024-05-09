#ifndef Point2D_H
#define Point2D_H

class Point2D
{
public:
	int x;
	int y;

	Point2D();
	Point2D(int x, int y);

	bool operator==(Point2D a);
};

#endif