#ifndef DrawBumpCalculations_H
#define DrawBumpCalculations_H

#pragma warning(disable:4146)

#include "cimg/CImg.h"
using namespace cimg_library;

#include "RandomService.h"
#include "PixelPosition.h"

class DrawBumpCalculations 
{
private:
	RandomService* randomSerivce;

public:
	DrawBumpCalculations(RandomService* randomSerivce);

public:
	void drawLiddelRandomBumb(CImg<unsigned int>* bg, PixelPosition position, double boarderDamageSteuerung, double pixelDistribution, const unsigned char(&color)[3]);
};

#endif