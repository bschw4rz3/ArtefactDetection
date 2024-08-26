#ifndef CImgService_H
#define CImgService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ColorService.h"

#include "ColorRGB.h"
#include <vector>

class CImgService
{
private:
    ColorService* colorService;

public:
    CImgService(ColorService* colorService);

    ColorRGB getPixel(const CImg<unsigned char>* image, int x, int y);

    void setPixel(CImg<unsigned char>* image, int x, int y, ColorRGB colorRGB);

    CImg<unsigned char> transpose(CImg<unsigned char>* image);

    double sum(CImg<unsigned char>* image);
    void divide(CImg<unsigned char>* image, double value);

    void normalizeGrayMatrix(CImg<unsigned char>* image, int whitePixels, int blackPixels, double factor);
};

#endif