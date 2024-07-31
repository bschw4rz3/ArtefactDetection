#include "LbpService.h"

LbpService::LbpService(GeometricService* geometricService, MathSerivce* mathSerivce, ColorService* colorSerivce)
{
	this->geometricService = geometricService;
	this->colorSerivce = colorSerivce;
	this->mathSerivce = mathSerivce;
}

std::map<int, int> LbpService::calculateLbpHistogram(CImg<unsigned char>* image, int samplePoints, double pixelRadius)
{
	std::map<int, int> histogram;

	for(int x = 0; x < image->width(); x++)
	{
		for(int y = 0; y < image->height(); y++)
		{
			int lbp = this->calculateLbp(image, Point2D(x, y), samplePoints, pixelRadius);

			if(histogram.find(lbp) == histogram.end())
			{
				histogram.insert(std::pair<int, int>(lbp, 1));
			}
			else
			{
				histogram[lbp]++;
			}
		}
	}

	return histogram;
}

int LbpService::calculateLbp(CImg<unsigned char>* image, Point2D centerPosition, int samplePoints, double pixelRadius)
{
	double sum = 0;

	unsigned char* pixelByte = image->data(centerPosition.x, centerPosition.y);
	ColorRGB centerColorRgb = this->colorSerivce->byte2rgb(pixelByte, image->width(), image->height());

	for(int i = 0; i < samplePoints;i++)
	{
		Point2D position = this->calculatePoint(centerPosition, pixelRadius, i, samplePoints);

		if(position.x < 0 || position.x > image->width() || position.y < 0 || position.y > image->height())
		{
			continue;
		}

		unsigned char* pixelByte = image->data(position.x, position.y);
		ColorRGB colorRgb = this->colorSerivce->byte2rgb(pixelByte, image->width(), image->height());

		int diff = colorRgb.r - centerColorRgb.r;
		double diffFactor = this->functionS(diff);

		sum += diffFactor * pow(2, i);
	}

	return sum;
}

int LbpService::calculateUniform(CImg<unsigned char>* image, Point2D centerPosition, int samplePoints, double pixelRadius)
{
	double sum = 0;

	std::map<int, double> distanceToCenter;

	unsigned char* pixelByte = image->data(centerPosition.x, centerPosition.y);
	ColorRGB centerColorRgb = this->colorSerivce->byte2rgb(pixelByte, image->width(), image->height());

	for(int i = 0; i < samplePoints;i++)
	{
		Point2D position = this->calculatePoint(centerPosition, pixelRadius, i, samplePoints);

		if(position.x < 0 || position.x > image->width() || position.y < 0 || position.y > image->height())
		{
			continue;
		}

		unsigned char* pixelByte = image->data(position.x, position.y);
		ColorRGB colorRgb = this->colorSerivce->byte2rgb(pixelByte, image->width(), image->height());

		int diff = colorRgb.r - centerColorRgb.r;
		double diffFactor = this->functionS(diff);

		distanceToCenter.insert(std::pair<int, double>(i, diffFactor));
	}

	sum += abs(distanceToCenter[samplePoints-1] - distanceToCenter[0]);

	for(int i = 0; i < samplePoints;i++)
	{
		sum += abs(distanceToCenter[i] - distanceToCenter[i-1]);
	}

	return sum;
}

int LbpService::functionS(double value)
{
	return value >= 0 ? 1 : 0;
}

Point2D LbpService::calculatePoint(Point2D center, double radius, int p, int samplePoints)
{
	double x = center.x + (radius * cos((2 * M_PI * ((double)p))/samplePoints));
	double y = center.y + (radius * sin((2 * M_PI * ((double)p))/samplePoints));

	double roundX = this->mathSerivce->roundDigits(x, 0);
	double roundY = this->mathSerivce->roundDigits(y, 0);

	return Point2D(roundX, roundY);
}