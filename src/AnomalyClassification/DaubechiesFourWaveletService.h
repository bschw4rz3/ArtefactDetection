#ifndef DaubechiesFourWaveletService_H
#define DaubechiesFourWaveletService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <iostream>
#include <iomanip>
#include <vector>

#include "CImgService.h"
#include "ClassicSobelOperatorService.h"

#include "../WaveletLib/wavelet.h"

class DaubechiesFourWaveletService
{
private:
	ClassicSobelOperatorService* sobelService;
	CImgService* cImgService;

public:
	DaubechiesFourWaveletService(ClassicSobelOperatorService* sobelService, CImgService* cImgService);

	void calculate(const CImg<unsigned char>* image, ColorRGB backgroundColor, bool normalizedToCentriod, bool trueToConture);
};

#endif