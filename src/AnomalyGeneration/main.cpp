// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#define cimg_use_png

#include <iostream>
#include "header/cimg/CImg.h"
#include "header/DrawCalculations.h"
#include "header/RandomService.h"

using namespace cimg_library;

int main()
{
    int w = 500;
    int h = 400;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};

    CImg<unsigned int> bg(w, h, 1, 3, 255);

    bg.draw_rectangle(0, 0, w, h, black, 1);

    int xPos = w/2;
    int yPos = h/2;

    int r = 150;
    
    RandomService randomService;

    DrawCircelCalculations drawCircelCalculations(&randomService);
    DrawCalculations c(&drawCircelCalculations);

    c.drawMultipleCicelCloud(&bg, xPos, yPos, r, 20, 20.0, 1, 2.0, 0.75, 0.5, 250, bluegreen);

    bg.display();
}