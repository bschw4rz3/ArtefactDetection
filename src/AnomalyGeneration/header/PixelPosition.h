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

public:
	bool operator==(PixelPosition other) noexcept
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(PixelPosition other) noexcept
	{
		return this->x != other.x && this->y != other.y;
	}
	
	bool operator>(PixelPosition other) noexcept
	{
		return this->x > other.x && this->y > other.y;
	}
	
	bool operator<(PixelPosition other) noexcept
	{
		return this->x < other.x && this->y < other.y;
	}
	
	bool operator>=(PixelPosition other) noexcept
	{
		return this->x >= other.x && this->y >= other.y;
	}
	
	bool operator<=(PixelPosition other) noexcept
	{
		return this->x <= other.x && this->y <= other.y;
	}
};

#endif
