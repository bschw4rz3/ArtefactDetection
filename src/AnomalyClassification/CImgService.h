#ifndef CImgService_H
#define CImgService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <vector>
#include <complex>

#include "GeometricService.h"
#include "ColorService.h"
#include "ColorRGB.h"

class CImgService
{
private:
    ColorService* colorService;
    GeometricService* geometricService;

public:
    CImgService(GeometricService* geometricService, ColorService* colorService);

    ColorRGB getPixel(const CImg<unsigned char>* image, int x, int y);

    void setPixel(CImg<unsigned char>* image, int x, int y, ColorRGB colorRGB);

    CImg<unsigned char> transpose(CImg<unsigned char>* image);

    double sum(CImg<unsigned char>* image);
    void divide(CImg<unsigned char>* image, double value);

    void normalizeGrayMatrix(CImg<unsigned char>* image, int whitePixels, int blackPixels, double factor);
    std::vector<std::complex<double>> getContureAsComplexVector(CImg<unsigned char>* contureImage, ColorRGB backgroundColor, bool normalizedToCentriod = true, bool trueToConture = false);

    std::vector<std::complex<double>> getContureByContureAsComplexVector(CImg<unsigned char>* contureImage, int backgroundGrayColor, Point2D centriod);
    std::vector<std::complex<double>> getContureByColumnAsComplexVector(CImg<unsigned char>* contureImage, int backgroundGrayColor, Point2D centriod);

    bool isIn(const std::vector<std::vector<Point2D>>& contureVectors, Point2D point);
    bool isIn(const std::vector<Point2D>& contureVectors, Point2D point);

    void addPointNear(Point2D currentPoint, CImg<unsigned char>* contureImage, std::vector<Point2D>& contureVector, int backgroundGrayColor);
};

#endif