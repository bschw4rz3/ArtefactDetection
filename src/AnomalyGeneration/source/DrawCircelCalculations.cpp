#include "../header/DrawCircelCalculations.h"


DrawCircelCalculations::DrawCircelCalculations(RandomService* randomService)
{
    this->randomService = randomService;
}

void DrawCircelCalculations::drawSouthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, 
    double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    for (int x = part* fadeFrom; x >= -part* fadeTo; x--)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));
        this->drawCicelFromPointCloudPositiv(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps * (abs(fadeOutY) / fadeOutY);
    }
}

void DrawCircelCalculations::drawWestCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    for (int y = -part* fadeFromTo; y <= part* fadeFromTo; y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));
        this->drawCicelFromPointCloudNegativ(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + (pixelCount);

        if (y == 0)
        {
            y = 1;
        }

        fadeOutFactor -= factorSteps * (abs(fadeOutY) / fadeOutY) * abs(y)/y;
    }
}

void DrawCircelCalculations::drawNorthCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    double fadeFrom = (fadeFromTo * 2) - 1.0;
    double fadeTo = (fadeFromTo * 2) - fadeFrom;

    for (int x = -part* fadeFrom; x <= part* fadeTo; x++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r, 2) - pow(x, 2)));
        this->drawCicelFromPointCloudNegativ(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps * (abs(fadeOutY) / fadeOutY);
    }
}

void DrawCircelCalculations::drawEastCircelPart(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution,
    double fadeFromTo, double fadeOutY, double factorSteps, const unsigned char(&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double fadeOutFactor = 0.5;

    double part = r / 4 * M_PI;

    int interationCount = part * 2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    for (int y = -part; y < 0 - (part*(1.0-fadeFromTo)); y++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));
        this->drawCicelFromPointCloudPositiv(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps * (abs(fadeOutY) / fadeOutY) * abs(y) / y;
    }

    for (int y = part; y > +(part * (1.0 - fadeFromTo)); y--)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r, 2) - pow(y, 2)));
        this->drawCicelFromPointCloudPositiv(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps * (abs(fadeOutY) / fadeOutY) * abs(y) / y;
    }
    
}

void DrawCircelCalculations::drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3])
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        bg->draw_point(xPos + x + randomX, yPos + y + randomY, color);
    }
}

void DrawCircelCalculations::drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char(&color)[3])
{
    for (int i = 0; i < pixelCount; i++)
    {
        int randomX = this->randomService->random(steuerung, pixelDistribution);
        int randomY = this->randomService->random(steuerung, pixelDistribution);

        bg->draw_point(xPos - x + randomX, yPos - y + randomY, color);
    }
}