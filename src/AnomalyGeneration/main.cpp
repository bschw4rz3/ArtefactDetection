// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#define cimg_use_png

#include <iostream>
#include "header/cimg/CImg.h"
#include "header/DrawCalculations.h"

using namespace cimg_library;

int main()
{
    int w = 300;
    int h = 400;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};

    CImg<unsigned int> bg(w, h, 1, 3, 255);

    bg.draw_rectangle(0, 0, w, h, black, 1);

    int xPos = w/2;
    int yPos = h/2;

    int r = 100;
    
    DrawCalculations c;

    c.drawCicelCloud(&bg, xPos, yPos, r, 10, 20.0, 10, 0, 0, bluegreen);
    c.drawCicelCloud(&bg, xPos, yPos, 80, 10, 20.0, 10, 0, 0, bluegreen);
    c.drawCicelCloud(&bg, xPos, yPos, 60, 10, 20.0, 10, 0, 0, bluegreen);
    c.drawCicelCloud(&bg, xPos, yPos, 40, 10, 20.0, 10, 0, 0, bluegreen);
    c.drawCicelCloud(&bg, xPos, yPos, 20, 10, 20.0, 10, 0, 0, bluegreen);

    bg.display();
}