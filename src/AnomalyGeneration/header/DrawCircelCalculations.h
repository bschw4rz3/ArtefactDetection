#ifndef DrawCircelCalculations_h
#define DrawCircelCalculations_h

#pragma warning(disable:4146)

#include <math.h>
#include "corecrt_math_defines.h"

#include "cimg/CImg.h"
using namespace cimg_library;

#include "RandomService.h"
#include "PixelPosition.h"
#include "CalculationService.h"

class DrawCircelCalculations {
private:
	CalculationService* calculationService;
	RandomService* randomService;

public:
	DrawCircelCalculations(CalculationService* calculationService, RandomService* randomService);

	double drawSouthCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, 
		double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3]);
	
	double drawWestCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3]);

	double drawNorthCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3]);

	double drawEastCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3]);

private:
	void drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, PixelPosition position, PixelPosition deltaPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3]);
	void drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, PixelPosition position, PixelPosition deltaPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3]);


};

#endif // !DrawCircelCalculations_h

