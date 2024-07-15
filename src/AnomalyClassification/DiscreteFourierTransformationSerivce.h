#ifndef DiscreteFourierTransformationSerivce_H
#define DiscreteFourierTransformationSerivce_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ClassicSobelOperatorService.h"
#include "ColorService.h"
#include "GeometricService.h"

class DiscreteFourierTransformationSerivce
{
private:
	ClassicSobelOperatorService* classicSobelOperatorService;
	GeometricService* geometricService;
	ColorService* colorService;

public:
	DiscreteFourierTransformationSerivce(ClassicSobelOperatorService* classicSobelOperatorService, GeometricService* geometricService, ColorService* colorService);

public:
	void calculate(CImg<unsigned char>* image);
};

#endif // !DiscreteFourierTransformationSerivce_H
