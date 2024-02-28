#include "..\header\DrawCalculations.h"

DrawCalculations::DrawCalculations(DrawCircelCalculations* drawCircelCalculations, DrawBumpCalculations* drawBumpCalculations)
{
    this->drawCircelCalculations = drawCircelCalculations;
    this->drawBumpCalculations = drawBumpCalculations;
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

void DrawCalculations::drawCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char (&color)[3])
{
    double fadeOutFactor = 0;

    double part = r / 4 * M_PI;
    double interationCount = part*2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;

    double sectorEast = (fadeFromTo * 3)- 2.0;
    
    if (sectorEast < 0)
    {
        sectorEast = 0;
    }
    
    double sectorMidd = (fadeFromTo * 3) - 1.0 - sectorEast;

    if (sectorMidd < 0)
    {
        sectorMidd = 0;
    }

    double sectorWest = (fadeFromTo * 3) - (sectorMidd+sectorEast);
    double sectorCount = sectorEast != 0 ? 1 : 0 + sectorMidd != 0 ? 2 : 0 + sectorWest != 0 ? 1 : 0;

    double factorSteps = abs(fadeOutY) / (sectorCount);

    double lastFadeFactor = this->drawCircelCalculations->drawEastCircelPart(bg, position, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, sectorEast, factorSteps * 0.25, 0, rotation, color);
    this->drawCircelCalculations->drawSouthCircelPart(bg, position, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, sectorMidd, factorSteps * 0.75, lastFadeFactor, rotation, color);
    lastFadeFactor = this->drawCircelCalculations->drawNorthCircelPart(bg, position, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, sectorMidd, factorSteps * 0.75, lastFadeFactor, rotation, color);
    this->drawCircelCalculations->drawWestCircelPart(bg, position, r, steuerung, pixelCountPerBoarderPixel, pixelDistribution, sectorWest, factorSteps*1.75, lastFadeFactor, rotation, color);
    
}

void DrawCalculations::drawMultipleCicelCloud(CImg<unsigned int>* bg, PixelPosition position, int r, int rotationInterval, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, double rotation, const unsigned char(&color)[3])
{
    int radus = r;

    while (radus > 0)
    {
        this->drawCicelCloud(bg, position, radus, steuerung, pixelCountPerBoarderPixel, pixelDistribution, fadeFromTo, fadeOutY, rotation, color);

        radus -= rotationInterval;
    }
}

void DrawCalculations::drawRectPart(CImg<unsigned int>* bg, PixelPosition position, double spaceX, double spaceY, double boarderDamageSteuerung, double boarderPixelDistribution, const unsigned char(&color)[3], const unsigned char(&boarderColor)[3])
{
    CImg<unsigned int> points(4, 2);

    PixelPosition topLeft(position.x + spaceX, position.y - spaceY);
    PixelPosition topRight(position.x + spaceX, position.y + spaceY);
    PixelPosition buttomRight(position.x - spaceX, position.y + spaceY);
    PixelPosition buttomLeft(position.x - spaceX, position.y - spaceY);

    int thePoints[] = {
        buttomRight.x, buttomLeft.x, topLeft.x, topRight.x, buttomRight.y, buttomLeft.y, topLeft.y, topRight.y
    };

    int *iterator = thePoints;

    cimg_forXY(points,x,y)
        points(x,y) = *iterator++;

    bg->draw_polygon(points, color);

    PixelPosition boarders[4][2] = {
        {topRight, topLeft},
        {topRight, buttomRight},
        {buttomRight, buttomLeft},
        {topLeft, buttomLeft}
    };

    for (int i = 0;i < 4 ;i++)
    {
        PixelPosition start = boarders[i][0];
        PixelPosition end = boarders[i][1];

        int x = end.x- start.x;
        int y = end.y- start.y;

        int stepX = 0;
        int stepY = 0;

        if (x != 0)
        {
            stepX = abs(x) / x;
        }
        
        if (y != 0)
        {
            stepY = abs(y) / y;
        }

        PixelPosition currentPosition(start.x, start.y);

        while (currentPosition.y >= end.y and currentPosition.x >= end.x)
        {
            for (int i = 0; i < 10; i++)
            {
                this->drawBumpCalculations->drawLiddelRandomBumb(bg, currentPosition, boarderDamageSteuerung, boarderPixelDistribution, boarderColor);
            }

            currentPosition.x += stepX;
            currentPosition.y += stepY;
        }
    }
}

void DrawCalculations::drawLiddelRandomBumb(CImg<unsigned int>* bg, PixelPosition position, double boarderDamageSteuerung, double boarderPixelDistribution, int maximalCountOfBumbs, const unsigned char(&color)[3])
{
    for (int i = 0; i < maximalCountOfBumbs; i++)
    {
        this->drawBumpCalculations->drawLiddelRandomBumb(bg, position, boarderDamageSteuerung, boarderPixelDistribution, color);
    }
}