#ifndef _DRAWCALCULATIONS_
#define _DRAWCALCULATIONS_

#pragma warning(disable:4146)

#include <iostream>
#include <format>
#include <cstdlib>
#include <math.h>
#include "corecrt_math_defines.h"

#include "cimg/CImg.h"
using namespace cimg_library;

#include "DrawCircelCalculations.h"
#include "DrawBumpCalculations.h"
#include "RandomService.h"
#include "PixelPosition.h"

class DrawCalculations
{
private:
	DrawCircelCalculations* drawCircelCalculations;
	DrawBumpCalculations* drawBumpCalculations;

public:
	DrawCalculations(DrawCircelCalculations* drawCircelCalculations, DrawBumpCalculations* drawBumpCalculations);

	void drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3]);
	void drawCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char (&color)[3]);
	void drawMultipleCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int rotationInterval, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char(&color)[3]);

	void drawRectPart(CImg<unsigned int>* bg, PixelPosition position, double spaceX, double spaceY, double boarderDamage, double boarderPixelDistribution, const unsigned char(&color)[3], const unsigned char(&boarderColor)[3]);
};

#endif // _DRAWCALCULATIONS_

