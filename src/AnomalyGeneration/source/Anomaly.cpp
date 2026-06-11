#include "../header/Anomaly.h"

Anomaly::Anomaly(std::vector<PixelPosition> pixels, AnomalyType anomalyType)
{
	auto last = std::unique(pixels.begin(), pixels.end());
	pixels.erase(last, pixels.end());
	this->pixelList = pixels;

	this->anomalyType = anomalyType;
}

bool Anomaly::IsInImage(PixelPosition imageFrom, PixelPosition imageTo)
{
	for(int i = 0;i<this->pixelList.size();i++)
	{
		if(imageFrom.x <= this->pixelList[i].x && imageFrom.y <= this->pixelList[i].y &&
		   imageTo.x >= this->pixelList[i].x && imageTo.y >= this->pixelList[i].y)
		{
			return true;
		}
	}

	return false;
}

PixelPosition Anomaly::getFrom()
{
	int x = this->getMinX();
	int y = this->getMinY();

	return PixelPosition(x, y);
}

PixelPosition Anomaly::getTo()
{
	int x = this->getMaxX();
	int y = this->getMaxY();

	return PixelPosition(x, y);
}

int Anomaly::getMaxX()
{
	int maxX = INT16_MIN;

	for(int i = 0;i<pixelList.size();i++)
	{
		if(maxX < pixelList[i].x)
		{
			maxX = pixelList[i].x;
		}
	}

	return maxX;
}

int Anomaly::getMaxY()
{
	int maxY = INT16_MIN;

	for(int i = 0;i<pixelList.size();i++)
	{
		if(maxY < pixelList[i].y)
		{
			maxY = pixelList[i].y;
		}
	}

	return maxY;
}

int Anomaly::getMinX()
{
	int minX = INT16_MAX;

	for(int i = 0;i<pixelList.size();i++)
	{
		if(minX > pixelList[i].x)
		{
			minX = pixelList[i].x;
		}
	}

	return minX;
}

int Anomaly::getMinY()
{
	int minY = INT16_MAX;

	for(int i = 0;i<pixelList.size();i++)
	{
		if(minY > pixelList[i].y)
		{
			minY = pixelList[i].y;
		}
	}

	return minY;
}