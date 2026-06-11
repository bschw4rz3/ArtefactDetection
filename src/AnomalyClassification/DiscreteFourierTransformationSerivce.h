#ifndef DiscreteFourierTransformationSerivce_H
#define DiscreteFourierTransformationSerivce_H

#include <vector>
#include <complex>

using namespace std::literals;

#include "ClassicSobelOperatorService.h"
#include "ColorService.h"
#include "GeometricService.h"
#include "MathSerivce.h"
#include "CImgService.h"

#include "FDResult.h"

class DiscreteFourierTransformationSerivce
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	CImgService* cImgService;
	ColorService* colorService;

public:
	DiscreteFourierTransformationSerivce(ClassicSobelOperatorService* classicSobelOperatorService, CImgService* cImgService, ColorService* colorService);

	FDResult calculate(CImg<unsigned char>* image, int dataSetLength);

private:
	std::vector<std::complex<double>> calculate_dft(const std::vector<std::complex<double> >& signal);
};

#endif // !DiscreteFourierTransformationSerivce_H
