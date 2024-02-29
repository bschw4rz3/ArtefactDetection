#ifndef PixelPosition_H
#define PixelPosition_H

class PixelPosition
{
public:
	PixelPosition()
	{
		this->x = 0;
		this->y = 0;
	}

	PixelPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

public:
	int x;
	int y;
};

#endif
