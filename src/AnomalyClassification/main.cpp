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
#include "GeometricService.h"

int main()
{
    StringSerivce stringSerivce;
    ColorService colorService;
    MathSerivce mathSerivce;
    SuperPixelService superPixelService(&colorService, &mathSerivce);
    ClassicSobelOperatorService classicSobelOperatorService(&colorService);
    ImprovedSobelOperatorService improvedSobelOperatorService(&colorService);
    GeometricService geometricService(&colorService);

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &superPixelService, &classicSobelOperatorService, &improvedSobelOperatorService, &geometricService, &stringSerivce);

    graphicEngine.initiateOpenGL(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addLabel(0, Point2D(500, 10), 50, L"Methode:");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(500, 30), L"Super Pixels");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SOBEL, Point2D(500, 50), L"Sobel Operator");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_IMPROVED_SOBEL, Point2D(500, 70), L"Improved Sobel");
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(500, 110), L"Unknown");

    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(450, 400), 100, L"Calculate");
    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(50, 300), 100, L"Open File");

    int pannelX = 350;
    int pannelY = 30;

    graphicEngine.addLabel(GUI_ID_LABEL_ROI, Point2D(pannelX, pannelY), 100, L"ROI:");
    graphicEngine.addLabel(GUI_ID_LABEL_AREA, Point2D(pannelX, pannelY+20), 100, L"Area of Anomaly:");
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_AREA_ROI, Point2D(pannelX, pannelY + 40), 100, L"Ratio of Area and ROI:");
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_WIDTH_LENGTH, Point2D(pannelX, pannelY + 60), 100, L"Ratio of width and length:");
    graphicEngine.addLabel(GUI_ID_LABEL_SCOPE, Point2D(pannelX, pannelY + 80), 100, L"Defektumfang:");
    graphicEngine.addLabel(GUI_ID_LABEL_DEFECT_FOCUS, Point2D(pannelX, pannelY + 100), 100, L"Defektschwerpunkt:");

    graphicEngine.addLabel(GUI_ID_VALUE_ROI, Point2D(pannelX+100, pannelY), 60, L"");
    graphicEngine.addLabel(GUI_ID_VALUE_AREA, Point2D(pannelX + 100, pannelY + 20), 60, L"");
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_AREA_ROI, Point2D(pannelX + 100, pannelY+40), 60, L"");
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, Point2D(pannelX + 100, pannelY+60), 60, L"");
    graphicEngine.addLabel(GUI_ID_VALUE_SCOPE, Point2D(pannelX + 100, pannelY + 80), 60, L"");
    graphicEngine.addLabel(GUI_ID_VALUE_DEFECT_FOCUS, Point2D(pannelX + 100, pannelY + 100), 60, L"");

    graphicEngine.run((EventReceiver*)&receiver);
}