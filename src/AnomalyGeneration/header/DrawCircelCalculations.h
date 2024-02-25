#ifndef DrawCircelCalculations_h
#define DrawCircelCalculations_h

#pragma warning(disable:4146)

#include <math.h>
#include "corecrt_math_defines.h"

#include "cimg/CImg.h"
using namespace cimg_library;

#include "RandomService.h"

class DrawCircelCalculations {
private:
	RandomService* randomService;

public:
	DrawCircelCalculations(RandomService* randomService);

	void drawSouthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, 
		double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3]);
	
	void drawWestCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3]);

	void drawNorthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3]);

	void drawEastCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
		double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3]);

private:
	void drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3]);
	void drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3]);


};

#endif // !DrawCircelCalculations_h

