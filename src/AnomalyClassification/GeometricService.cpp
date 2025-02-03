#include "GeometricService.h"

GeometricService::GeometricService(ColorService* colorService)
{
	this->colorService = colorService;
}

BackgroundResult GeometricService::getBackgroundList(CImg<unsigned char>* image)
{
	std::vector<Point2D> backgroundPositions({
		Point2D(0, 0), Point2D(image->width() - 1, 0), 
		Point2D(0, image->height() - 1), 
		Point2D(image->width() - 1, image->height() - 1), 
		Point2D(image->width() - 1, image->height() / 2), 
		Point2D(image->width() / 2, image->height() - 1), 
		Point2D(0, image->height() / 2), 
		Point2D(image->width() / 2, 0) });

	std::vector<ColorRGB> colors;

	for (Point2D position : backgroundPositions)
	{
		const unsigned char* bytePixel = image->data(position.x, position.y);
		ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());
		colors.push_back(color);
	}

	return BackgroundResult(backgroundPositions, colors);
}

ColorRGB GeometricService::getBackgroundColor(CImg<unsigned char>* image)
{
	std::vector<ColorRGB> colors;
	std::map<ColorRGB, int> colorCounter;
	
	BackgroundResult backgroundResult = this->getBackgroundList(image);

	for (ColorRGB color : backgroundResult.colorList)
	{
		if (colorCounter.find(color) != colorCounter.end())
		{
			colorCounter[color]++;
		}
		else
		{
			colorCounter.insert(std::pair<ColorRGB, int>(color, 1));
			colors.push_back(color);
		}
	}

	ColorRGB maxColor(255, 255, 255);
	int maxColorCounter = 0;

	for (ColorRGB color : colors)
	{
		if (colorCounter[color] > maxColorCounter)
		{
			maxColor = color;
			maxColorCounter = colorCounter[color];
		}
	}
	
	return maxColor;
}

int GeometricService::countDefectPixels(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	int pixelArea = 0;

	for (int x = 0; x < image->width() - 1; x++)
	{
		// Durchläuft das Originalbild entlang der y-Achse.
		for (int y = 0; y < image->height() - 1; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color != backgroundColor)
			{
				pixelArea++;
			}
		}
	}

	return pixelArea;
}

int GeometricService::calculateScope(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	int boarderPixels = 0; 
	const unsigned char* c = this->colorService->rgb2byte(ColorRGB(255, 0, 0));

	for (int x = 0; x < image->width() - 1; x++)
	{
		for (int y = 0; y < image->height() - 1; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color != backgroundColor && this->isboarderPixel(image, x, y))
			{
				boarderPixels++;
			}
		}
	}

	return boarderPixels;
}

Point2D GeometricService::calculateCentroid(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	long double partPixels = 0;

	long double sumX = 0;
	long double sumY = 0;

	for (int x = 0; x < image->width() - 1; x++)
	{
		for (int y = 0; y < image->height() - 1; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if(color != backgroundColor)
			{
				sumX += x;
				sumY += y;

				partPixels++;
			}
		}
	}

	return Point2D(sumX/partPixels, sumY/partPixels);
}

double GeometricService::calculateRectangularity(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	double totalPixels = image->width() * image->height();
	double blackPixels = this->countDefectPixels(image, backgroundColor);
	double withePixels = totalPixels - blackPixels;

	return withePixels / totalPixels;
}

bool GeometricService::isboarderPixel(CImg<unsigned char>* image, int x, int y)
{
	for (int w = -1; w <= 1; w++)
	{
		for (int h = -1; h <= 1; h++)
		{
			int px = x + w;
			int py = y + h;

			if (px <= 0 || px >= image->width())
			{
				return true;
			}

			if (py <= 0 || py >= image->height())
			{
				return true;
			}

			const unsigned char* bytePixel = image->data(px, py);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color.r > 210)
			{
				return true;
			}
		}
	}

	return false;
}

Point2D GeometricService::getRoiLength(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	std::vector<Point2D> anomaliePixels = this->getConturePixelPositions(image, backgroundColor);

	double minWidth = INT8_MAX;
	double maxWidth = 0;
	double minHeight = INT8_MAX;
	double maxHeight = 0;

	for (int i = 0; i < anomaliePixels.size(); i++)
	{
		if (minWidth > anomaliePixels[i].x)
		{
			minWidth = anomaliePixels[i].x;
		}
		else if (maxWidth < anomaliePixels[i].x)
		{
			maxWidth = anomaliePixels[i].x;
		}

		if (minHeight > anomaliePixels[i].y)
		{
			minHeight = anomaliePixels[i].y;
		}
		else if (maxHeight < anomaliePixels[i].y)
		{
			maxHeight = anomaliePixels[i].y;
		}
	}

	return Point2D(maxWidth-minWidth, maxHeight-minHeight);
}

std::vector<Point2D> GeometricService::getConturePixelPositions(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	std::vector<Point2D> contureList;

	for (int x = 0; x < image->width(); x++)
	{
		for (int y = 0; y < image->height(); y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color != backgroundColor)
			{
				contureList.push_back(Point2D(x, y));
			}
		}
	}

	return contureList;
}

double GeometricService::getPixelPositionWithMinDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor)
{
	double minDistance = 0;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->calculateDistance(contureList[i], centerPoint);

		if (distance < minDistance)
		{
			minDistance = distance;
		}
	}

	return minDistance;
}

double GeometricService::getPixelPositionWithMaxDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor)
{
	double maxDistance = 0;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->calculateDistance(contureList[i], centerPoint);

		if (distance > maxDistance)
		{
			maxDistance = distance;
		}
	
	}

	return maxDistance;
}

double GeometricService::calculateDistance(Point2D point, Point2D center)
{
	return sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));
}