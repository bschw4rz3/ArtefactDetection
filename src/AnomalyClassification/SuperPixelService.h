#ifndef SuperPixelService_H
#define SuperPixelService_H

#include "math.h"
#include <vector>

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../../../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "SuperPixelEntry.h"
#include "ColorService.h"
#include "SuperPixelResult.h"
#include "SubregionResult.h"

class SuperPixelService
{
private:
	ColorService* colorService;

public:
	SuperPixelService(ColorService* colorService);

	SubregionResult calculateSuperPixelsAndSubregions(CImg<unsigned char>& image, int maxCluster, double m = 0, double E = 0, double T = 155);
	SuperPixelResult calculateSuperPixels(CImg<unsigned char>& image, int maxCluster, double m = 0, double E = 0);

private:
	SuperPixelResult calculateSuperPixel(std::vector<std::vector<SuperPixelEntry>> colorMatrix, Point2D pixelDimensions, int maxCluster, double m, double E);

	double calculateDc(ColorLib clusterPixel, ColorLib other);
	double calculateDs(Point2D clusterPixel, Point2D other);

	std::vector<Point2D> initializeClusterCenters(double distanceOfClusters, Point2D dimensions);
	std::vector<std::vector<SuperPixelEntry>> imageToMatrix(CImg<unsigned char>& image);

	std::vector<Point2D> optimiceClusterCenters(const std::vector<std::vector<SuperPixelEntry>>& colorMatrix, const std::vector<Point2D>& centers, double naborPixelRadius);
	double calculateGradientof(Point2D position, const std::vector<std::vector<SuperPixelEntry>>& colorMatrix);

	std::vector<Point2D> caluclateNewPoints(std::vector<std::vector<SuperPixelEntry>> clusterDataPoints);
	double caluclateResidualError(std::vector<Point2D> oldPoints, std::vector<Point2D> newPoints);

	std::vector<std::vector<SuperPixelEntry>> sortByLabels(std::vector<std::vector<SuperPixelEntry>> colorMatrix, int maxK);
	std::vector<SuperPixelEntry> getClusterCenters(std::vector<std::vector<SuperPixelEntry>> colorMatrix, std::vector<Point2D> clusterCenters);
};

#endif