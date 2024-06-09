// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <string>

#include "GraphicEngineExtended.h"
#include "MyEventReceiver.h"
#include "SuperPixelService.h"
#include "ColorService.h"
#include "StringSerivce.h"
#include "ClassicSobelOperatorService.h"
#include "ImprovedSobelOperatorService.h"

int main()
{
    StringSerivce stringSerivce;
    ColorService colorService;
    MathSerivce mathSerivce;
    SuperPixelService superPixelService(&colorService, &mathSerivce);
    ClassicSobelOperatorService classicSobelOperatorService(&colorService);
    ImprovedSobelOperatorService improvedSobelOperatorService(&colorService);

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &superPixelService, &classicSobelOperatorService, &improvedSobelOperatorService, &stringSerivce);

    graphicEngine.initiateOpenGL(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addLabel(0, Point2D(500, 10), 50, L"Methode:");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(500, 30), L"Super Pixels");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SOBEL, Point2D(500, 50), L"Sobel Operator");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_IMPROVED_SOBEL, Point2D(500, 70), L"Improved Sobel");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(500, 110), L"Unknown");

    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(450, 400), 100, L"Calculate");
    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(50, 300), 100, L"Open File");

    graphicEngine.run((EventReceiver*)&receiver);
}