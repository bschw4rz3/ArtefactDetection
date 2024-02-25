#include "../header/DrawCircelCalculations.h"


DrawCircelCalculations::DrawCircelCalculations(RandomService* randomService)
{
    this->randomService = randomService;
}

double DrawCircelCalculations::drawSouthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, 
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = beginFadeOutFactor;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    double anglePI = angle / 180 * M_PI;

    for (int x = part* fadeFrom; x >= -part* fadeTo; x--)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));

        double angledX = round(x * cos(anglePI) - y * sin(anglePI));
        double angledY = round(x * sin(anglePI) + y * cos(anglePI));

        this->drawCicelFromPointCloudPositiv(bg, angledX, angledY, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps;
    }

    return fadeOutFactor;
}

double DrawCircelCalculations::drawWestCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = beginFadeOutFactor;

    double part = r / 4 * M_PI;

    double anglePI = angle / 180 * M_PI;

    int interationCount = part * 2;

    for (int y = -part* fadeFromTo; y <= part* fadeFromTo; y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));

        double angledX = round(x * cos(anglePI) - y * sin(anglePI));
        double angledY = round(x * sin(anglePI) + y * cos(anglePI));

        this->drawCicelFromPointCloudNegativ(bg, angledX, angledY, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + (pixelCount);

        if (y == 0)
        {
            fadeOutFactor -= factorSteps;
        }
        else
        {
            fadeOutFactor -= factorSteps * abs(y) / y;
        }
    }

    return fadeOutFactor;
}

double DrawCircelCalculations::drawNorthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double anglePI = angle / 180 * M_PI;

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    for (int x = -part* fadeFrom; x <= part* fadeTo; x++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));

        double angledX = round(x * cos(anglePI) - y * sin(anglePI));
        double angledY = round(x * sin(anglePI) + y * cos(anglePI));

        this->drawCicelFromPointCloudNegativ(bg, angledX, angledY, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps;
    }

    return fadeOutFactor;
}

double DrawCircelCalculations::drawEastCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double anglePI = angle / 180 * M_PI;
    
    int countOfInterations = part - (part * (1.0 - fadeFromTo));
    double fadeOutFactor = beginFadeOutFactor + (countOfInterations* factorSteps);

    for (int y = -part; y < 0 - (part*(1.0-fadeFromTo)); y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));

        double angledX = round(x * cos(anglePI) - y * sin(anglePI));
        double angledY = round(x * sin(anglePI) + y * cos(anglePI));

        this->drawCicelFromPointCloudPositiv(bg, angledX, angledY, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor -= factorSteps;
    }
    
    fadeOutFactor = beginFadeOutFactor + (countOfInterations * factorSteps);
    writtenPixeles = 0;
    shouldWritePixels = 0;

    for (int y = part; y > (part * (1.0 - fadeFromTo)); y--)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));

        double angledX = round(x * cos(anglePI) - y * sin(anglePI));
        double angledY = round(x * sin(anglePI) + y * cos(anglePI));

        this->drawCicelFromPointCloudPositiv(bg, angledX, angledY, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor -= factorSteps;
    }

    return fadeOutFactor;
    
}

void DrawCircelCalculations::drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, 
    const unsigned char(&color)[3])
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        bg->draw_point(xPos + x + randomX, yPos + y + randomY, color);
    }
}

void DrawCircelCalculations::drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, 
    const unsigned char(&color)[3])
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        bg->draw_point(xPos - x + randomX, yPos - y + randomY, color);
    }
}