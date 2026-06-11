#include "../header/DrawCircelCalculations.h"


DrawCircelCalculations::DrawCircelCalculations(CalculationService* calculationService, RandomService* randomService)
{
    this->calculationService = calculationService;
    this->randomService = randomService;
}

double DrawCircelCalculations::drawSouthCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, 
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = beginFadeOutFactor;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    double anglePI = this->calculationService->toRadiant(angle);

    for (int x = part* fadeFrom; x >= -part* fadeTo; x--)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));

        PixelPosition angledPosition = this->calculationService->rotation(PixelPosition(x,y), anglePI);

        this->drawCicelFromPointCloudPositiv(bg, angledPosition, position, steuerung, pixelCount, pixelDistribution, color, pixelList);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps;
    }

    return fadeOutFactor;
}

double DrawCircelCalculations::drawWestCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = beginFadeOutFactor;

    double part = r / 4 * M_PI;
    
    double anglePI = this->calculationService->toRadiant(angle);

    int interationCount = part * 2;

    for (int y = -part* fadeFromTo; y <= part* fadeFromTo; y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));

        PixelPosition angledPosition = this->calculationService->rotation(PixelPosition(x,y), anglePI);

        this->drawCicelFromPointCloudNegativ(bg, angledPosition, position, steuerung, pixelCount, pixelDistribution, color, pixelList);

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

double DrawCircelCalculations::drawNorthCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double anglePI = this->calculationService->toRadiant(angle);

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    for (int x = -part* fadeFrom; x <= part* fadeTo; x++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));

        PixelPosition angledPosition = this->calculationService->rotation(PixelPosition(x,y), anglePI);

        this->drawCicelFromPointCloudNegativ(bg, angledPosition, position, steuerung, pixelCount, pixelDistribution, color, pixelList);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps;
    }

    return fadeOutFactor;
}

double DrawCircelCalculations::drawEastCircelPart(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double factorSteps, double beginFadeOutFactor, double angle, const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;

    double anglePI = this->calculationService->toRadiant(angle);
    
    int countOfInterations = part - (part * (1.0 - fadeFromTo));
    double fadeOutFactor = beginFadeOutFactor + (countOfInterations* factorSteps);

    for (int y = -part; y < 0 - (part*(1.0-fadeFromTo)); y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));

        PixelPosition angledPosition = this->calculationService->rotation(PixelPosition(x,y), anglePI);

        this->drawCicelFromPointCloudPositiv(bg, angledPosition, position, steuerung, pixelCount, pixelDistribution, color, pixelList);

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

        PixelPosition angledPosition = this->calculationService->rotation(PixelPosition(x,y), anglePI);

        this->drawCicelFromPointCloudPositiv(bg, angledPosition, position, steuerung, pixelCount, pixelDistribution, color, pixelList);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor -= factorSteps;
    }

    return fadeOutFactor;
    
}

void DrawCircelCalculations::drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, PixelPosition position, PixelPosition deltaPos, int steuerung, int pixelCount, double pixelDistribution, 
    const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        if(bg != NULL)
        {
            bg->draw_point(deltaPos.x + position.x + randomX, deltaPos.y + position.y + randomY, color);
        }
        pixelList->push_back(PixelPosition(deltaPos.x + position.x + randomX, deltaPos.y + position.y + randomY));
    }
}

void DrawCircelCalculations::drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, PixelPosition position, PixelPosition deltaPos, int steuerung, int pixelCount, double pixelDistribution, 
    const unsigned char(&color)[3], std::vector<PixelPosition>* pixelList)
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        if (bg != NULL)
        {
            bg->draw_point(deltaPos.x - position.x + randomX, deltaPos.y - position.y + randomY, color);
        }
            
        pixelList->push_back(PixelPosition(deltaPos.x - position.x + randomX, deltaPos.y - position.y + randomY));
    }
}