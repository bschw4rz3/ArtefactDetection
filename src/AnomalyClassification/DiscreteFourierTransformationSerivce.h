#ifndef DiscreteFourierTransformationSerivce_H
#define DiscreteFourierTransformationSerivce_H

#include <vector>
#include <complex>

using namespace std::literals;

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ClassicSobelOperatorService.h"
#include "ColorService.h"
#include "GeometricService.h"
#include "MathSerivce.h"

class DiscreteFourierTransformationSerivce
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	GeometricService* geometricService;
	ColorService* colorService;
	MathSerivce* mathSerivce;

public:
	DiscreteFourierTransformationSerivce(ColorService* colorService);

	std::vector<int> calculate(CImg<unsigned char>* image);

private:
	std::vector<int> calculate_IDFT(std::vector<float> Xr, std::vector<float> Xi, int len);
};

#endif // !DiscreteFourierTransformationSerivce_H
