#include "LbpService.h"

LbpService::LbpService(GeometricService* geometricService, MathSerivce* mathSerivce, ColorService* colorSerivce)
{
	this->geometricService = geometricService;
	this->colorSerivce = colorSerivce;
	this->mathSerivce = mathSerivce;
}

LbpHistogramResult LbpService::calculateLbpHistogram(CImg<unsigned char>* image, int samplePoints, double pixelRadius)
{
	std::map<int, int> lbpHistogram;
	std::map<std::string, int> uniformityHistogram;

	for(int x = 0; x < image->width(); x++)
	{
		for(int y = 0; y < image->height(); y++)
		{
			LbpResult lbpResult = this->calculateLbp(image, Point2D(x, y), samplePoints, pixelRadius);

			int lbp = lbpResult.getLbp();
			int uniformity = lbpResult.getUniformity();
			std::string uniformityString = this->getUniformityString(uniformity);

			if(lbpHistogram.find(lbp) == lbpHistogram.end())
			{
				lbpHistogram.insert(std::pair<int, int>(lbp, 1));
			}
			else
			{
				lbpHistogram[lbp]++;
			}

			if(uniformityHistogram.find(uniformityString) == uniformityHistogram.end())
			{
				uniformityHistogram.insert(std::pair<std::string, int>(uniformityString, 1));
			}
			else
			{
				uniformityHistogram[uniformityString]++;
			}
		}
	}

	return LbpHistogramResult(lbpHistogram, uniformityHistogram);
}

LbpResult LbpService::calculateLbp(CImg<unsigned char>* image, Point2D centerPosition, int samplePoints, double pixelRadius)
{
	// Result of LBP
	double sumLbp = 0;
	// Result of uniformity
	double sumUniformity = 0;
	// Map of uniformity
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

		sumLbp += diffFactor * pow(2, i);
		distanceToCenter.insert(std::pair<int, double>(i, diffFactor));
	}

	sumUniformity += abs(distanceToCenter[samplePoints-1] - distanceToCenter[0]);

	for(int i = 0; i < samplePoints;i++)
	{
		sumUniformity += abs(distanceToCenter[i] - distanceToCenter[i-1]);
	}

	return LbpResult(sumLbp, sumUniformity);
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

std::string LbpService::getUniformityString(int uniformity)
{
	if(uniformity <= 0)
	{
		return "0";
	}
	else if(uniformity == 1)
	{
		return "1";
	}
	else if(uniformity == 2)
	{
		return "2";
	}

	return "P+1";
}