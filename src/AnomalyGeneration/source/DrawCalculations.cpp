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

void DrawCalculations::drawCicelCloud(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeOutX, double fadeOutY, const unsigned char (&color)[3])
{
    int writtenPixeles = 0;
    double shouldWritePixels = 0;

    double part = r / 4*M_PI;
    double fadeOutFactor = 0;

    int interationCount = part*2;
    int writePixelPerSector = pixelCountPerBoarderPixel * interationCount;


    // south
    double factorSteps = abs(fadeOutY)/(double)interationCount;

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
    
    for(int x = -part;x <= part;x++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);
        
        int y = round(sqrt(pow(r,2)-pow(x,2)));
        this->drawCicelFromPointCloudPositiv(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor += factorSteps * (abs(fadeOutY)/fadeOutY);
    }
    
    // west
    if(fadeOutY > 0)
    {
        fadeOutFactor = fadeOutY-0.5;
    }
    else if(fadeOutY < 0)
    {
        fadeOutFactor = 0.0;
    }
    else
    {
        fadeOutFactor = 1.0;
    }

    if(fadeOutFactor > 0)
    {
        for(int y = -part;y <= part;y++)
        {   
            shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

            int pixelCount = (shouldWritePixels - writtenPixeles);

            int x = round(sqrt(pow(r,2) - pow(y, 2)));
            this->drawCicelFromPointCloudNegativ(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

            writtenPixeles = writtenPixeles + (pixelCount);

            if(y == 0)
            {
                y = 1;
            }

            fadeOutFactor += factorSteps * (abs(fadeOutY)/fadeOutY) * (abs(y)/y);
        }   
    }

    // north
    if(fadeOutY > 0)
    {
        fadeOutFactor = abs(fadeOutY);
    }
    else if(fadeOutY < 0)
    {
        fadeOutFactor = 0.0;
    }
    else
    {
        fadeOutFactor = 1.0;
    }

    for(int x = -part;x <= part;x++)
    {
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int y = round(sqrt(pow(r,2)-pow(x,2)));
        this->drawCicelFromPointCloudNegativ(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        fadeOutFactor -= factorSteps * (abs(fadeOutY)/fadeOutY);
    }

    // east
    if(fadeOutY < 0)
    {
        fadeOutFactor = 0.0;
    }
    else if(fadeOutY > 0)
    {
        fadeOutFactor = fadeOutY;
    }
    else
    {
        fadeOutFactor = 1.0;
    }

    for(int y = -part;y <= part;y++)
    {   
        shouldWritePixels += (pixelCountPerBoarderPixel * fadeOutFactor);

        int pixelCount = (shouldWritePixels - writtenPixeles);

        int x = round(sqrt(pow(r,2) - pow(y, 2)));
        this->drawCicelFromPointCloudPositiv(bg, x, y, xPos, yPos, steuerung, pixelCount, pixelDistribution, color);

        writtenPixeles = writtenPixeles + pixelCount;

        if(y == 0)
        {
            y = 1;
        }

        fadeOutFactor += factorSteps * (abs(fadeOutY)/fadeOutY) * (abs(y)/y);
    }
}

void DrawCalculations::drawCicelFromPointCloudPositiv(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char (&color)[3])
{
    for(int i = 0; i < pixelCount; i++)
    {
        int randomX = this->random(steuerung, pixelDistribution);
        int randomY = this->random(steuerung, pixelDistribution);

        bg->draw_point(xPos + x + randomX, yPos + y + randomY, color);
    }
}

void DrawCalculations::drawCicelFromPointCloudNegativ(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char (&color)[3])
{
    for(int i = 0; i < pixelCount; i++)
    {
        int randomX = this->random(steuerung, pixelDistribution);
        int randomY = this->random(steuerung, pixelDistribution);

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

    double result = x;
    result = round(pow(x, pixelDistribution) * pow(x, pixelDistribution) * x * (steuerung/2));

    return result;
}

double DrawCalculations::randomOneScaled()
{    
    double random = std::rand();
    double result = random / (RAND_MAX + 1u);
    return result;
}