#include "..\header\DrawCalculations.h"

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

void DrawCalculations::drawCicelCloud(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, const unsigned char (&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double part = r/4*M_PI;

    for(int x = -part;x <= part;x++)
    {
        shouldWritePixels = shouldWritePixels + (2*pixelCountPerBoarderPixel);

        int pixelCount = (shouldWritePixels - writtenPixeles)/2;

        int y = round(sqrt(pow(r,2)-pow(x,2)));
        this->drawPointFromCloud(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + (pixelCount * 2);
    }

    for(int y = -part;y <= part;y++)
    {   
        shouldWritePixels = shouldWritePixels + (2*pixelCountPerBoarderPixel);

        int pixelCount = (shouldWritePixels - writtenPixeles)/2;

        int x = round(sqrt(pow(r,2) - pow(y, 2)));
        this->drawPointFromCloud(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + (pixelCount * 2);
    }
}

void DrawCalculations::drawPointFromCloud(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char (&color)[3])
{
    for(int i = 0; i < pixelCount; i++)
    {
        int randomX = this->random(steuerung, pixelDistribution);
        int randomY = this->random(steuerung, pixelDistribution);

        bg->draw_point(xPos + x + randomX, yPos + y + randomY, color);

        randomX = this->random(steuerung, pixelDistribution);
        randomY = this->random(steuerung, pixelDistribution);

        bg->draw_point(xPos - x + randomX, yPos - y + randomY, color);
    }
}

int DrawCalculations::random(int steuerung, double pixelDistribution)
{
    if(steuerung == 0)
    {
        return 0;
    }

    double random = std::rand();
    double scaledRandom = random / ((RAND_MAX + 1u) / 2) - (1);

    double o = sqrt(sqrt(pixelDistribution));
    double x = scaledRandom;

    double result = round(pow(x, pixelDistribution) * pow(x, pixelDistribution) * x * (steuerung/2));

    return result;
}