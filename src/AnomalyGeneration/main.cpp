// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#define cimg_use_png

#include <iostream>
#include "header/cimg/CImg.h"
#include "header/DrawCalculations.h"
#include "header/RandomService.h"
#include "header/DrawBumpCalculations.h"

using namespace cimg_library;

int main()
{
    int w = 600;
    int h = 500;

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

    c.drawLiddelRandomBumb(&bg, PixelPosition(150, 100), 5, 1.0, 10, black);
    c.drawLiddelRandomBumb(&bg, PixelPosition(150, 150), 5, 1.0, 10, black);
    c.drawLiddelRandomBumb(&bg, PixelPosition(200, 150), 5, 1.0, 10, black);
    c.drawLiddelRandomBumb(&bg, PixelPosition(150, 200), 5, 1.0, 10, black);

    c.drawScratch(&bg, PixelPosition(300, 300), PixelPosition(350, 400), 10, 10, 10, black);
    c.drawScratch(&bg, PixelPosition(200, 100), PixelPosition(350, 50), 20, 5, 10000, black);
    c.drawScratch(&bg, PixelPosition(130, 100), PixelPosition(130, 200), 3, 2, 10, black);

    //c.drawMultipleCicelCloud(&bg, PixelPosition(xPos, yPos), r, 20, 20.0, 0.05, 1.0, 0.75, 0.5, 250, black);

    
    c.drawMultipleCicelCloud(&bg, PixelPosition(xPos+100, yPos+100), r, 20, 20.0, 0.5, 1.0, 0.5, 0.5, 230, black);

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
            tmp = bg.get_crop(x, y, 0, 0, x+wx, y+hy, 0, 3);
            
            tmp.display();
        }
    }


    

    
}