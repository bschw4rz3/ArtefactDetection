#include "GeometricService.h"

GeometricService::GeometricService(ColorService* colorService)
{
	this->colorService = colorService;
}

ColorRGB GeometricService::getBackgroundColor(CImg<unsigned char>* image)
{
	std::vector<ColorRGB> colors;
	std::map<ColorRGB, int> colorCounter;
	Point2D backgroundPositions[] = { Point2D(0, 0), Point2D(image->width(), 0), Point2D(0, image->height()), Point2D(image->width(), image->height()), Point2D(image->width(), image->height()/2), Point2D(image->width()/2, image->height()), Point2D(0, image->height()/2), Point2D(image->width()/2, 0) };

	for (Point2D position : backgroundPositions)
	{
		const unsigned char* bytePixel = image->data(position.x, position.y);
		ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

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

Point2D GeometricService::calculateDefectFocus(CImg<unsigned char>* image, ColorRGB backgroundColor)
{
	double blackPixels = 0;

	double sumX = 0;
	double sumY = 0;

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

				blackPixels++;
			}
		}
	}

	return Point2D(sumX/blackPixels, sumY/blackPixels);
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