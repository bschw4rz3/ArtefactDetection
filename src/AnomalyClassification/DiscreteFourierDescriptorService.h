#ifndef DiscreteFourierDescriptorService_H
#define DiscreteFourierDescriptorService_H

#include <vector>
#include <complex>

#include "MathSerivce.h"
#include "CImgService.h"
#include "ClassicSobelOperatorService.h"

#include "FDResult.h"

class DiscreteFourierDescriptorService
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	CImgService* cImgService;

public:
	DiscreteFourierDescriptorService(ClassicSobelOperatorService* classicSobelOperatorService, CImgService* cImgService);

	FDResult calculate(CImg<unsigned char>* image);

private:
	std::vector<std::complex<double>> computeFourierDescriptors(const std::vector<std::complex<double>>& contour);
};

#endif