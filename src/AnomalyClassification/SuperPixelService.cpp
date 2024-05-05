#include "SuperPixelService.h"

SuperPixelService::SuperPixelService(ColorService* colorService)
{
	this->colorService = colorService;
}

std::vector<std::vector<SuperPixelEntry>> SuperPixelService::process(int maxCluster, CImg<unsigned char>& image, double m, double E)
{
	double residualError = INT32_MAX;

	std::vector<std::vector<SuperPixelEntry>> colorMatrix = this->imageToMatrix(image);
	Point2D pixelDimensions(image.width(), image.height());

	int pixelSizeN = image.width() * image.height();
	double S = sqrt(pixelSizeN / maxCluster);

	if (m == 0)
	{
		m = S;
	}

	std::vector<Point2D> unoptimicedClusterCenters = this->initializeClusterCenters(S, pixelDimensions);

	if (unoptimicedClusterCenters.size() > maxCluster)
	{
		throw "Zu wenig Cluster!";
	}

	std::vector<Point2D> clusterCenters = this->optimiceClusterCenters(colorMatrix, unoptimicedClusterCenters, 3);
	
	int realClusterAmout = clusterCenters.size();

	while(residualError > E)
	{
		for (int k = 0; k < clusterCenters.size(); k++)
		{
			Point2D currentCenter = clusterCenters[k];

			int minX = currentCenter.x - S >= 0 ? currentCenter.x - S : 0;
			int minY = currentCenter.y - S >= 0 ? currentCenter.y - S : 0;
			int maxX = currentCenter.x + S < colorMatrix.size() ? currentCenter.x + S : colorMatrix.size() - 1;
			int maxY = currentCenter.y + S < colorMatrix[0].size() ? currentCenter.y + S : colorMatrix[0].size() - 1;

			SuperPixelEntry currentCluster = colorMatrix[currentCenter.x][currentCenter.y];

			for (int x = minX; x < maxX; x++)
			{
				for (int y = minY; y < maxY; y++)
				{
					double dc = this->calculateDc(currentCluster.color, colorMatrix[x][y].color);
					double ds = this->calculateDs(currentCluster.position, colorMatrix[x][y].position);

					double distance = sqrt(pow( dc/m, 2) + pow( ds/S, 2));

					if (distance < colorMatrix[x][y].distance)
					{
						colorMatrix[x][y].distance = distance;
						colorMatrix[x][y].label = k;
					}
				}
			}
		}

		std::vector<std::vector<SuperPixelEntry>> clusterDataPoints = this->sortByLabels(colorMatrix, realClusterAmout);

		std::vector<Point2D> newClusterCenters = this->caluclateNewPoints(clusterDataPoints);
		residualError = this->caluclateResidualError(clusterCenters, newClusterCenters);

		clusterCenters = newClusterCenters;
	}

	return this->sortByLabels(colorMatrix, realClusterAmout);
}

std::vector<Point2D> SuperPixelService::initializeClusterCenters(double distanceOfClusters, Point2D dimensions)
{
	std::vector<Point2D> result;

	int timesX = ((double) dimensions.x) / distanceOfClusters;
	int timesY = ((double) dimensions.y) / distanceOfClusters;

	double beginX = (dimensions.x - (((double)timesX) * distanceOfClusters));
	double beginY = (dimensions.y - (((double)timesY) * distanceOfClusters));

	for (double x = beginX; x < dimensions.x; x += distanceOfClusters)
	{
		for (double y = beginY; y < dimensions.y; y += distanceOfClusters)
		{
			result.push_back(Point2D(round(x), round(y)));			
		}
	}

	return result;
}

std::vector<Point2D> SuperPixelService::optimiceClusterCenters(const std::vector<std::vector<SuperPixelEntry>> &colorMatrix, const std::vector<Point2D> &centers, double naborPixelRadius)
{
	std::vector<Point2D> result;

	for (int i = 0; i < centers.size(); i++)
	{
		Point2D currentCluster = centers[i];
		int minX = currentCluster.x - naborPixelRadius >= 0 ? currentCluster.x - naborPixelRadius : 0;
		int minY = currentCluster.y - naborPixelRadius >= 0 ? currentCluster.y - naborPixelRadius : 0;
		int maxX = currentCluster.x + naborPixelRadius < colorMatrix.size() ? currentCluster.x + naborPixelRadius : colorMatrix.size() - 1;
		int maxY = currentCluster.y + naborPixelRadius < colorMatrix[0].size() ? currentCluster.y + naborPixelRadius : colorMatrix[0].size() - 1;

		std::vector<double> gradientList;
		std::vector<Point2D> points;

		if (this->calculateGradientof(currentCluster, colorMatrix) == 0)
		{
			result.push_back(currentCluster);
			continue;
		}

		for (int x = minX; x < maxX; x++)
		{
			for (int y = minY; y < maxY; y++)
			{
				Point2D position(x, y);

				points.push_back(position);
				gradientList.push_back(this->calculateGradientof(position, colorMatrix));
			}
		}

		int minIndex = -1;
		double minGradient = INT32_MAX;

		for (int i = 0; i < points.size(); i++)
		{
			if (minGradient > gradientList[i])
			{
				minGradient = gradientList[i];
				minIndex = i;
			}
		}

		result.push_back(points[minIndex]);
	}

	return result;
}

double SuperPixelService::calculateGradientof(Point2D position, const std::vector<std::vector<SuperPixelEntry>>& colorMatrix)
{
	int minX = position.x - 1 >= 0 ? position.x - 1 : 0;
	int minY = position.y - 1 >= 0 ? position.y - 1 : 0;
	int maxX = position.x + 1 < colorMatrix.size() ? position.x + 1 : colorMatrix.size() - 1;
	int maxY = position.y + 1 < colorMatrix[0].size() ? position.y + 1 : colorMatrix[0].size() - 1;

	ColorLib currentColor = colorMatrix[position.x][position.y].color;

	std::vector<double> gradientList;
	std::vector<Point2D> points;

	double value = 0;

	for (int x = minX; x < maxX; x++)
	{
		for (int y = minY; y < maxY; y++)
		{
			ColorLib selectedColor = colorMatrix[x][y].color;
			value += pow(currentColor.a - selectedColor.a, 2) + pow(currentColor.b - selectedColor.b, 2) + pow(currentColor.l - selectedColor.l, 2);
		}
	}

	return value;
}

std::vector<std::vector<SuperPixelEntry>> SuperPixelService::imageToMatrix(CImg<unsigned char>& image)
{
	std::vector<std::vector<SuperPixelEntry>> result;

	int width = image.width();
	int height = image.height();

	for (int x = 0; x < width; x++)
	{
		std::vector<SuperPixelEntry> line;

		for (int y = 0; y < height; y++)
		{
			unsigned char* ptr = image.data(x, y);

			unsigned char r = ptr[0];
			unsigned char g = ptr[0 + width * height];
			unsigned char b = ptr[0 + 2 * width * height];

			ColorLib colorLib = this->colorService->rgb2lab(ColorRGB(r, g, b));

			line.push_back(SuperPixelEntry(colorLib, Point2D(x, y)));
		}

		result.push_back(line);
	}

	return result;
}

double SuperPixelService::calculateDc(ColorLib clusterPixel, ColorLib other)
{
	return sqrt(
		pow(clusterPixel.l - other.l, 2) +
		pow(clusterPixel.a - other.a, 2) +
		pow(clusterPixel.b - other.b, 2)
	);
}

double SuperPixelService::calculateDs(Point2D clusterPixel, Point2D other)
{
	return sqrt(
		pow((double)clusterPixel.x - (double)other.x, 2) +
		pow((double)clusterPixel.y - (double)other.y, 2)
	);
}

std::vector<Point2D> SuperPixelService::caluclateNewPoints(std::vector<std::vector<SuperPixelEntry>> clusterDataPoints)
{
	std::vector<Point2D> result;

	for (int k = 0; k < clusterDataPoints.size(); k++)
	{
		std::vector<SuperPixelEntry> pointsOfCluster = clusterDataPoints[k];

		double sumX = 0;
		double sumY = 0;

		for (int i = 0; i < pointsOfCluster.size(); i++)
		{
			sumX += pointsOfCluster[i].position.x;
			sumY += pointsOfCluster[i].position.y;
		}

		double amoutOfPoints = pointsOfCluster.size();

		result.push_back(Point2D(round(sumX / amoutOfPoints), round(sumY / amoutOfPoints)));
	}

	return result;
}

double SuperPixelService::caluclateResidualError(std::vector<Point2D> oldPoints, std::vector<Point2D> newPoints)
{
	double sumE = 0;

	for (int k = 0; k < oldPoints.size(); k++)
	{
		sumE += sqrt(pow(oldPoints[k].x - newPoints[k].x, 2) + pow(oldPoints[k].y - newPoints[k].y, 2));
	}

	return sumE / ((double)oldPoints.size());
}

std::vector<std::vector<SuperPixelEntry>> SuperPixelService::sortByLabels(std::vector<std::vector<SuperPixelEntry>> colorMatrix, int maxK)
{
	std::vector<std::vector<SuperPixelEntry>> result;

	for (int k = 0; k < maxK; k++)
	{
		result.push_back(std::vector<SuperPixelEntry>());
	}

	for (int x = 0; x < colorMatrix.size(); x++)
	{
		for (int y = 0; y < colorMatrix[x].size(); y++)
		{
			int label = colorMatrix[x][y].label;

			if (label != -1)
			{
				result[label].push_back(colorMatrix[x][y]);
			}
		}
	}

	return result;
}