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

    int size = 5;
    PixelPosition position(150, 100);
    c.drawLiddelRandomBumb(&bg, position, size, 1.0, 10, black);
    anomalyList.push_back(Anomaly(PixelPosition(position.x-size, position.x-size), PixelPosition(position.x+size, position.x+size), AnomalyType::MinorDefect));

    
    PixelPosition positionFrom(200, 100);
    PixelPosition positionTo(350, 50);
    int brigth = 20;
    c.drawScratch(&bg, positionFrom, positionTo, brigth, 5, 10000, black);
    anomalyList.push_back(Anomaly(PixelPosition(positionFrom.x-brigth, positionFrom.x-brigth), PixelPosition(positionTo.x+brigth, positionTo.x+brigth), AnomalyType::Defect));


    int radius = 150;
    int rotationInterval = 20;
    PixelPosition position(100, 100);    
    c.drawMultipleCicelCloud(&bg, PixelPosition(position.x+100, position.y+100), radius, rotationInterval, 20.0, 0.5, 1.0, 0.5, 0.5, 230, black);
    anomalyList.push_back(Anomaly(PixelPosition(position.x-radius, position.x-radius), PixelPosition(position.x+radius, position.x+radius), AnomalyType::Artefact));

    r = 50;

    c.drawRect(&bg, PixelPosition(xPos-150, yPos+150), r, r, black);
    c.drawMultipleCicelCloud(&bg, PixelPosition(xPos-150, yPos+150), r, 15, 10.0, 1.0, 1.0, 0.5, 0.5, 290, withe);

    bg.display();

    int wx = 200;
    int hy = 200;

    for(int x = 0;x<w;x+=wx)
    {
        for(int y = 0;y<h;y+=hy)
        {
            CImg<unsigned char> tmp = CImg<unsigned char>(200, 200, 1, 4);
            tmp = bg.get_crop(x, y, 0, 0, x+wx-1, y+hy-1, 0, 3);
            
            tmp.display();
        }
    }


    

    
}