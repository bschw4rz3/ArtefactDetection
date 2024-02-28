#include "../header/DrawBumpCalculations.h"

DrawBumpCalculations::DrawBumpCalculations(RandomService* randomSerivce)
{
	this->randomSerivce = randomSerivce;
}

void DrawBumpCalculations::drawLiddelRandomBumb(CImg<unsigned int>* bg, PixelPosition position, double boarderDamageSteuerung, double pixelDistribution, const unsigned char(&color)[3])
{
	double randomNumber = this->randomSerivce->randomOneScaled();

	if (randomNumber < 0.75)
	{
		this->drawRandomPixel(bg, position, boarderDamageSteuerung, pixelDistribution, color);
	}
	else if (randomNumber < 1.0)
	{
		this->drawRandomCircel(bg, position, boarderDamageSteuerung, pixelDistribution, color);
	}	
}

void DrawBumpCalculations::drawScratch(CImg<unsigned int>* bg, PixelPosition from, PixelPosition to, double bright, int count, int randomPixelsPerLine, const unsigned char(&color)[3])
{
	for(int i = 0;i < count;i++)
	{
		double randomNumber = this->randomSerivce->randomOnePosAndNegScaled();
		double randomFromX = randomNumber * bright;
		randomNumber = this->randomSerivce->randomOnePosAndNegScaled();
		double randomFromY = randomNumber * bright;

		randomNumber = this->randomSerivce->randomOnePosAndNegScaled();
		double randomToX = randomNumber * bright;
		randomNumber = this->randomSerivce->randomOnePosAndNegScaled();
		double randomToY = randomNumber * bright;

		PixelPosition newFrom(from.x+randomFromX, from.y+randomFromY);
		PixelPosition newTo(to.x+randomToX, to.y+randomToY);

		randomNumber = this->randomSerivce->randomOneScaled();
		double brightRandom = randomNumber * bright;

		double difX = newTo.x-newFrom.x;
		double difY = newTo.y-newFrom.y;

		double difMax = max(abs(difX), abs(difY));

		double stepX = difX / difMax;
		double stepY = difY / difMax;

		double currentX = newFrom.x;
		double currentY = newFrom.y;

		double currentRandomPixels = 0;
		double shouldHavePixels = 0;
		double pixelCountPerPixel = randomPixelsPerLine/difMax;

		while(round(currentX) != newTo.x || round(currentY) != newTo.y)
		{
			shouldHavePixels += pixelCountPerPixel;

			PixelPosition current(currentX, currentY);

			this->drawLiddelRandomBumb(bg, current, brightRandom, 2.0, color);
			this->drawRandomCircel(bg, current, brightRandom, 2.0, color);

			while(currentRandomPixels <= shouldHavePixels)
			{
				this->drawRandomPixel(bg, current, brightRandom, 2.0, color);
				currentRandomPixels++;
			}

			currentX += stepX;
			currentY += stepY;
		}
	}
}

void DrawBumpCalculations::drawRandomCircel(CImg<unsigned int>* bg, PixelPosition position, double steuerung, double pixelDistribution, const unsigned char(&color)[3])
{
	double randomSteuerungX = this->randomSerivce->random(steuerung, pixelDistribution);
	double randomSteuerungY = this->randomSerivce->random(steuerung, pixelDistribution);

	double circleWidth = this->randomSerivce->random(steuerung, pixelDistribution);

	bg->draw_circle(round(position.x + randomSteuerungX), round(position.y + randomSteuerungY), circleWidth, color);
}

void DrawBumpCalculations::drawRandomPixel(CImg<unsigned int>* bg, PixelPosition position, double steuerung, double pixelDistribution, const unsigned char(&color)[3])
{
	double randomSteuerungX = this->randomSerivce->random(steuerung, pixelDistribution);
	double randomSteuerungY = this->randomSerivce->random(steuerung, pixelDistribution);

	bg->draw_point(round(position.x + randomSteuerungX), round(position.y + randomSteuerungY), color);
}