#include "SdSfService.h"

SdSfService::SdSfService(ClassicSobelOperatorService* classicSobelOperatorService, MathSerivce* mathSerivce, StringSerivce* stringSerivce, ColorService* colorService)
{
	this->classicSobelOperatorService = classicSobelOperatorService;
	this->mathSerivce = mathSerivce;
	this->colorService = colorService;
	this->stringSerivce = stringSerivce;
}

std::map<std::string, int> SdSfService::calculateSdSf(CImg<unsigned char>* sobelImage)
{
	ColorRGB backgroundColor(0, 0, 0);
	std::vector<Point2D> contureList = this->getConture(sobelImage, backgroundColor);

	Point2D centerPoint = this->calculateCenterPoint(contureList, backgroundColor);
	double minDistance = this->getMinDistance (contureList, centerPoint, backgroundColor);
	double maxDistance = this->getMaxDistance (contureList, centerPoint, backgroundColor);

	std::vector<double> distanceList;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->calculateDistanceToCenter(contureList[i], centerPoint);
		double normalicedDistance = (distance - minDistance) / (maxDistance - minDistance);
		
		distanceList.push_back(normalicedDistance);
	}

	std::sort(distanceList.begin(), distanceList.end());

	std::map<std::string, int> distanceHistogram;
	
	for (int i = 0; i < distanceList.size(); i++)
	{
		double distance = distanceList[i];

		double roundedDistance = this->mathSerivce->roundDigits(distance, 4);
		std::string stringDistance = std::format("{:4f}", roundedDistance);

		if (stringDistance.size() < 5)
		{
			stringDistance = stringDistance + ".0000";
		}

		if (distanceHistogram.find(stringDistance) != distanceHistogram.end())
		{
			distanceHistogram[stringDistance]++;
		}
		else
		{
			distanceHistogram.insert(std::pair<std::string, int>(stringDistance, 1));
		}
	}

	return distanceHistogram;
}

double SdSfService::getMinDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor)
{
	double minDistance = 0;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->calculateDistanceToCenter(contureList[i], centerPoint);

		if (distance < minDistance)
		{
			minDistance = distance;
		}
	}

	return minDistance;
}

double SdSfService::getMaxDistance(std::vector<Point2D> contureList, Point2D centerPoint, ColorRGB backgroundColor)
{
	double maxDistance = 0;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->calculateDistanceToCenter(contureList[i], centerPoint);

		if (distance > maxDistance)
		{
			maxDistance = distance;
		}
	
	}

	return maxDistance;
}

Point2D SdSfService::calculateCenterPoint(std::vector<Point2D> contureList, ColorRGB backgroundColor)
{
	double sum_x = 0;
	double sum_y = 0;

	int n = contureList.size();

	for (int i = 0; i < n; i++)
	{
		sum_x += contureList[i].x;
		sum_y += contureList[i].y;
	}

	double i_c = (1.0 / n) * sum_x;
	double j_c = (1.0 / n) * sum_y;

	return Point2D(i_c, j_c);
}

std::vector<Point2D> SdSfService::getConture(CImg<unsigned char>* image, ColorRGB backgroundColor)
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

double SdSfService::calculateDistanceToCenter(Point2D point, Point2D center)
{
	return sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));
}