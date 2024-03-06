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

	std::vector<PixelPosition> drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3]);
	std::vector<PixelPosition> drawCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char (&color)[3]);
	std::vector<PixelPosition> drawMultipleCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int rotationInterval, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char(&color)[3]);

	void drawRectPart(CImg<unsigned int>* bg, PixelPosition position, double spaceX, double spaceY, double boarderDamage, double boarderPixelDistribution, const unsigned char(&color)[3], const unsigned char(&boarderColor)[3]);

	std::vector<PixelPosition> drawLiddelRandomBumb(CImg<unsigned int>* bg, PixelPosition position, double boarderDamageSteuerung, double boarderPixelDistribution, int maximalCountOfBumbs, const unsigned char(&color)[3]);
	std::vector<PixelPosition> drawScratch(CImg<unsigned int>* bg, PixelPosition from, PixelPosition to, double bright, int count, int randomPixels, const unsigned char(&color)[3]);

	void drawRect(CImg<unsigned int>* bg, PixelPosition position, double spaceX, double spaceY, const unsigned char(&color)[3]);
};

#endif // _DRAWCALCULATIONS_

