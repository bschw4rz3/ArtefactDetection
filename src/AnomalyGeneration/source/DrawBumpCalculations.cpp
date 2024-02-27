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
		double randomSteuerungX = this->randomSerivce->random(boarderDamageSteuerung, pixelDistribution);
		double randomSteuerungY = this->randomSerivce->random(boarderDamageSteuerung, pixelDistribution);

		bg->draw_point(round(position.x + randomSteuerungX), round(position.y + randomSteuerungY), color);
	}
	else if (randomNumber < 1.0)
	{
		double randomSteuerungX = this->randomSerivce->random(boarderDamageSteuerung, pixelDistribution);
		double randomSteuerungY = this->randomSerivce->random(boarderDamageSteuerung, pixelDistribution);

		double circleWidth = this->randomSerivce->random(boarderDamageSteuerung, pixelDistribution);

		bg->draw_circle(round(position.x + randomSteuerungX), round(position.y + randomSteuerungY), circleWidth,color);
	}	
}