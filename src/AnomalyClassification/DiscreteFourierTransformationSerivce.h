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
	DiscreteFourierTransformationSerivce(ClassicSobelOperatorService* classicSobelOperatorService, ColorService* colorService);

	std::vector<std::complex<double>> calculate(CImg<unsigned char>* image, int dataSetLength);

private:
	std::vector<std::complex<double>> calculate_dft(const std::vector<std::complex<double> >& signal);
};

#endif // !DiscreteFourierTransformationSerivce_H
