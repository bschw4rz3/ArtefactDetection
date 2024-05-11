// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <string>

#include "GraphicEngineExtended.h"
#include "MyEventReceiver.h"
#include "SuperPixelService.h"
#include "ColorService.h"
#include "StringSerivce.h"

int main()
{
    StringSerivce stringSerivce;
    ColorService colorService;
    MathSerivce mathSerivce;
    SuperPixelService superPixelService(&colorService, &mathSerivce);

    std::wstring wFile = L"..\\AnomalyGeneration\\testdata\\defect\\75.png";
    std::string cFile = stringSerivce.toString(wFile);

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &superPixelService, &stringSerivce);

    graphicEngine.initiate(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addLabel(0, Point2D(500, 10), 50, L"Methode:");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(500, 30), L"Super Pixels");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(500, 50), L"Unknown");

    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(450, 400), 100, L"Calculate");
    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(50, 300), 100, L"Open File");

    graphicEngine.run((EventReceiver*)&receiver);
}