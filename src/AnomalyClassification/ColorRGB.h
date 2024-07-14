#ifndef ColorRGB_H
#define ColorRGB_H

class ColorRGB
{
public:
	int r;
	int g;
	int b;

	ColorRGB(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	bool operator==(const ColorRGB other) const
	{
		return other.r == this->r && other.g == this->g && other.b == this->b;
	}

	bool operator!=(const ColorRGB other) const
	{
		return !this->operator==(other);
	}

	bool operator<(const ColorRGB other) const
	{
		return this->getGrayValue() < other.getGrayValue();
	}

	bool operator>(const ColorRGB other) const
	{
		return this->getGrayValue() > other.getGrayValue();
	}

	int getGrayValue() const
	{
		return 0.299 * ((double)this->r) + 0.587 * ((double)this->g) + 0.114 * ((double)this->b);
	}
};

#endif