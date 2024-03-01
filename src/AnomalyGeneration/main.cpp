// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#define cimg_use_png

#include <iostream>
#include "header/cimg/CImg.h"
#include "header/DrawCalculations.h"
#include "header/RandomService.h"
#include "header/DrawBumpCalculations.h"
#include "header/Anomaly.h"

using namespace cimg_library;

int main()
{
    int w = 500;
    int h = 450;

    std::vector<Anomaly> anomalyList;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};
    const unsigned char withe[] = {255, 255, 255};

    CImg<unsigned int> bg(w, h, 1, 3, 255);

    bg.draw_rectangle(0, 0, w, h, black, 1);

    int xPos = w/2;
    int yPos = h/2;

    int r = 150;
    
    RandomService randomService;

    CalculationService calculationService;
    DrawCircelCalculations drawCircelCalculations(&calculationService, &randomService);
    DrawBumpCalculations drawBumpCalculations(&randomService);
    DrawCalculations c(&drawCircelCalculations, &drawBumpCalculations);

    c.drawRectPart(&bg, PixelPosition(xPos, yPos), 200, 200, 10, 1, withe, black);

    {
        int size = 5;
        PixelPosition position(150, 100);
        c.drawLiddelRandomBumb(&bg, position, size, 1.0, 10, black);
        anomalyList.push_back(Anomaly(PixelPosition(position.x-size, position.y-size), PixelPosition(position.x+size, position.y+size), AnomalyType::MinorDefect));
    }
    
    {
        PixelPosition positionFrom(200, 100);
        PixelPosition positionTo(350, 50);
        int brigth = 20;
        c.drawScratch(&bg, positionFrom, positionTo, brigth, 5, 10000, black);
        anomalyList.push_back(Anomaly(PixelPosition(positionFrom.x-brigth, positionFrom.y-brigth), PixelPosition(positionTo.x+brigth, positionTo.y+brigth), AnomalyType::Defect));
    }
    {
        int radius = 150;
        int rotationInterval = 20;
        PixelPosition position(200, 200);    
        c.drawMultipleCicelCloud(&bg, PixelPosition(position.x, position.y), radius, rotationInterval, 20.0, 0.5, 1.0, 0.5, 0.5, 230, black);
        anomalyList.push_back(Anomaly(PixelPosition(position.x-radius, position.y-radius), PixelPosition(position.x+radius, position.y+radius), AnomalyType::Artefact));
    }
    {
        r = 50;
        PixelPosition position(xPos-150, yPos+150);

        c.drawRect(&bg, position, r, r, black);
        c.drawMultipleCicelCloud(&bg, position, r, 15, 10.0, 1.0, 1.0, 0.5, 0.5, 290, withe);
        anomalyList.push_back(Anomaly(PixelPosition(position.x-r, position.y-r), PixelPosition(position.x+r, position.y+r), AnomalyType::Artefact));
    }

    bg.display();

    int wx = 200;
    int hy = 200;

    for(int x = 0;x<w;x+=wx)
    {
        for(int y = 0;y<h;y+=hy)
        {
            PixelPosition imageFrom(x, y);
            PixelPosition imageTo(x+wx-1, y+hy-1);

            CImg<unsigned char> tmp = CImg<unsigned char>(wx, hy, 1, 4);
            tmp = bg.get_crop(imageFrom.x, imageFrom.y, 0, 0, imageTo.x, imageTo.y, 0, 3);
            
            for(int i = 0;i<anomalyList.size();i++)
            {
                PixelPosition from = anomalyList[i].from;
                PixelPosition to = anomalyList[i].to;

                int diffX = to.x - from.x;
                int diffY = to.y - from.y;

                PixelPosition middel(from.x+diffX, from.y+diffY);
                PixelPosition from2(from.x, to.y);
                PixelPosition to2(to.x, from.y);

                if((imageFrom <= from && from <= imageTo) || 
                   (imageFrom <= to && to <= imageTo) ||
                   (imageFrom <= from2 && from2 <= imageTo) ||
                   (imageFrom <= to2 && to2 <= imageTo) ||
                   (imageFrom <= middel && middel <= imageTo))
                {
                    std::cout << anomalyList[i].anomalyType << "\n";
                }
            }
            
            tmp.display();
        }
    }    
}