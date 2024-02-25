#include "..\header\DrawCalculations.h"

DrawCalculations::DrawCalculations(DrawCircelCalculations* drawCircelCalculations)
{
    this->drawCircelCalculations = drawCircelCalculations;
}

void DrawCalculations::drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3])
{
    int lastX = 0;
    int lastY = 0;

    int firstX = 0;
    int firstY = 0;

    for(int x = -r;x <= r;x++)
    {
        int y = round(sqrt(pow(r,2)-pow(x,2)));

        if(firstY == 0)
        {
            firstX = x;
            firstY = y;
        }

        if(lastY != 0)
        {
            bg->draw_line(xPos + x, yPos + y, xPos + lastX, yPos + lastY, color);
            bg->draw_line(xPos - x, yPos - y, xPos - lastX, yPos - lastY, color);
        }

        lastX = x;
        lastY = y;
    }

    bg->draw_line(xPos + firstX, yPos + firstY, xPos - lastX, yPos - lastY, color);
    bg->draw_line(xPos - firstX, yPos - firstY, xPos + lastX, yPos + lastY, color);
}

void DrawCalculations::drawCicelCloud(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeOutX, double fadeOutY, const unsigned char (&color)[3])
{
    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;
    double interationCount = part*2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    double factorSteps = abs(fadeOutY)/interationCount;

    if(fadeOutY < 0)
    {
        fadeOutFactor = abs(fadeOutY);
    }
    else if(fadeOutY > 0)
    {
        fadeOutFactor = 0.0;
    }
    else
    {
        fadeOutFactor = 1.0;
    }
    
    this->drawCircelCalculations->drawSouthCircelPart(bg, xPos, yPos, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, 0.7, fadeOutY, factorSteps * 1.0, color);
    this->drawCircelCalculations->drawWestCircelPart(bg, xPos, yPos, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, 0.5, 1.0, 1.0, color);
    this->drawCircelCalculations->drawNorthCircelPart(bg, xPos, yPos, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, 0.7, fadeOutY, factorSteps * 1.0, color);
    this->drawCircelCalculations->drawEastCircelPart(bg, xPos, yPos, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, 0.5, fadeOutY, factorSteps * 0.5, color);
}