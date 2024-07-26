#include "GeometricService.h"

GeometricService::GeometricService(ColorService* colorService)
{
	this->colorService = colorService;
}

int GeometricService::countBlackPixels(CImg<unsigned char>* image)
{
	int pixelArea = 0;

	for (int x = 0; x < image->width() - 1; x++)
	{
		// Durchläuft das Originalbild entlang der y-Achse.
		for (int y = 0; y < image->height() - 1; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color.r < 155)
			{
				pixelArea++;
			}
		}
	}

	return pixelArea;
}

int GeometricService::calculateScope(CImg<unsigned char>* image)
{
	int boarderPixels = 0; 
	const unsigned char* c = this->colorService->rgb2byte(ColorRGB(255, 0, 0));

	for (int x = 0; x < image->width() - 1; x++)
	{
		for (int y = 0; y < image->height() - 1; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if (color.r < 155 && this->isboarderPixel(image, x, y))
			{
				boarderPixels++;
			}
		}
	}

	return boarderPixels;
}

Point2D GeometricService::calculateDefectFocus(CImg<unsigned char>* image)
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

			if(color.r == 0 && color.g == 0 && color.b == 0)
			{
				sumX += x;
				sumY += y;

				blackPixels++;
			}
		}
	}

	return Point2D(sumX/blackPixels, sumY/blackPixels);
}

double GeometricService::calculateRectangularity(CImg<unsigned char>* image)
{
	double totalPixels = image->width() * image->height();
	double blackPixels = this->countBlackPixels(image);
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