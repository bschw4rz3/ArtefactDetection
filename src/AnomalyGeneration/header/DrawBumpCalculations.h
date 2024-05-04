#ifndef DrawBumpCalculations_H
#define DrawBumpCalculations_H

#pragma warning(disable:4146)

#include "../../../Shared/cimg/CImg.h"
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
	void drawLiddelRandomBumb(CImg<unsigned int>* bg, PixelPosition position, double boarderDamageSteuerung, double pixelDistribution, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList = NULL);
	void drawRandomPixel(CImg<unsigned int>* bg, PixelPosition position, double steuerung, double pixelDistribution, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList = NULL);
	void drawScratch(CImg<unsigned int>* bg, PixelPosition from, PixelPosition to, double bright, int count, int randomPixelsPerLine, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList = NULL);

private:
	void drawRandomCircel(CImg<unsigned int>* bg, PixelPosition position, double steuerung, double pixelDistribution, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList = NULL);
};

#endif