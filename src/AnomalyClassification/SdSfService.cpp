#include "SdSfService.h"

SdSfService::SdSfService(ClassicSobelOperatorService* classicSobelOperatorService, GeometricService* geometricService, MathSerivce* mathSerivce, StringSerivce* stringSerivce, ColorService* colorService)
{
	this->classicSobelOperatorService = classicSobelOperatorService;
	this->mathSerivce = mathSerivce;
	this->colorService = colorService;
	this->stringSerivce = stringSerivce;
	this->geometricService = geometricService;
}

std::map<std::string, int> SdSfService::calculateSdSf(CImg<unsigned char>* sobelImage)
{
	ColorRGB backgroundColor(0, 0, 0);
	std::vector<Point2D> contureList = this->geometricService->getConturePixelPositions(sobelImage, backgroundColor);

	Point2D centerPoint = this->calculateCenterPoint(contureList, backgroundColor);
	double minDistance = this->geometricService->getPixelPositionWithMinDistance(contureList, centerPoint, backgroundColor);
	double maxDistance = this->geometricService->getPixelPositionWithMaxDistance(contureList, centerPoint, backgroundColor);

	std::vector<double> distanceList;

	for (int i = 0; i < contureList.size(); i++)
	{
		double distance = this->geometricService->calculateDistance(contureList[i], centerPoint);
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