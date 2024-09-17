#ifndef SuperPixelService_H
#define SuperPixelService_H

#include <math.h>
#include <vector>

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "SuperPixelEntry.h"
#include "ColorService.h"
#include "MathSerivce.h"
#include "SuperPixelResult.h"
#include "SubregionResult.h"
#include "KeyValuePair.h"

class SuperPixelService
{
private:
	ColorService* colorService;
	MathSerivce* mathSerivce;

public:
	SuperPixelService(ColorService* colorService, MathSerivce* mathSerivce);

	SubregionResult calculateSuperPixelsAndSubregions(CImg<unsigned char>* image, int maxCluster, double m = 0, double E = 0, double L = 0, double T = 1);
	SuperPixelResult calculateSuperPixels(CImg<unsigned char>* image, int maxCluster, double m = 0, double E = 0);

private:
	SuperPixelResult calculateSuperPixel(std::vector<std::vector<SuperPixelEntry>> colorMatrix, Point2D pixelDimensions, int maxCluster, double m, double E);

	double calculateDc(ColorLib clusterPixel, ColorLib other);
	double calculateDs(Point2D clusterPixel, Point2D other);

	std::vector<Point2D> initializeClusterCenters(double distanceOfClusters, Point2D dimensions);
	std::vector<std::vector<SuperPixelEntry>> imageToMatrix(CImg<unsigned char>* image);

	std::vector<Point2D> optimiceClusterCenters(const std::vector<std::vector<SuperPixelEntry>>& colorMatrix, const std::vector<Point2D>& centers, double naborPixelRadius);
	double calculateGradientof(Point2D position, const std::vector<std::vector<SuperPixelEntry>>& colorMatrix);

	std::vector<Point2D> caluclateNewPoints(std::vector<std::vector<SuperPixelEntry>> clusterDataPoints);
	double caluclateResidualError(std::vector<Point2D> oldPoints, std::vector<Point2D> newPoints);

	std::vector<std::vector<SuperPixelEntry>> sortByLabels(std::vector<std::vector<SuperPixelEntry>> colorMatrix, int maxK);
	std::vector<SuperPixelEntry> getClusterCenters(std::vector<std::vector<SuperPixelEntry>> colorMatrix, std::vector<Point2D> clusterCenters);

	double calculateS(Point2D pixelDimensions, int maxCluster);

	std::vector<Point2D> cacluateNeighbors(Point2D clusterCenter, double L);
	std::vector<SuperPixelEntry> getPixelEntries(std::vector<Point2D> neighbors, std::vector<std::vector<SuperPixelEntry>> colorMatrix, Point2D imageDimensions);
	double calculateColorDistance(ColorLib clusterCenterColor, ColorLib neighborPixelColor);
	int getClusterOfPixel(std::vector < std::vector<SuperPixelEntry>> clusterEntries, SuperPixelEntry neighborPixel);
	int getGroupIndex(const std::vector<std::vector<int>>& subSectionIndexes, int elementIndex);
};

#endif