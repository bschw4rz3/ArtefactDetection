// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#define cimg_use_png

#include <iostream>
#include "header/cimg/CImg.h"

using namespace cimg_library;

int main()
{
    int w = 300;
    int h = 400;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};

    CImg<unsigned int> bg(w, h, 1, 3, 255);

    bg.draw_rectangle(0, 0, w, h, black, 1);
    bg.draw_point(10, 10, bluegreen);

    bg.draw_circle(w/2, h/2, 100, bluegreen);

    bg.display();

    //bg.save("file.png");
}
