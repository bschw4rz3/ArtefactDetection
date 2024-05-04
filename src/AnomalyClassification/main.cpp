// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include "../IrrlichtWrapper/GraphicEngine.h"
#include "MyEventReceiver.h"

int main()
{
    std::wstring file = L"..\\AnomalyGeneration\\testdata\\defect\\75.png";

    GraphicEngine graphicEngine;
    MyEventReceiver receiver(&graphicEngine);

    graphicEngine.initiate(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addImage(GUI_ID_IMAGE, Point2D(10, 10), file.c_str());

    graphicEngine.run((EventReceiver*)&receiver);
}