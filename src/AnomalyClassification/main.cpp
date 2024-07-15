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
#include "HistogramValueService.h"
#include "DiscreteFourierTransformationSerivce.h"

int main()
{
    StringSerivce stringSerivce;
    ColorService colorService;
    MathSerivce mathSerivce;
    SuperPixelService superPixelService(&colorService, &mathSerivce);
    ClassicSobelOperatorService classicSobelOperatorService(&colorService);
    ImprovedSobelOperatorService improvedSobelOperatorService(&colorService);
    GeometricService geometricService(&colorService);
    HistogramValueService histogramValueService(&colorService);
    DiscreteFourierTransformationSerivce discreteFourierTransformationSerivce(&colorService);

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &superPixelService, &classicSobelOperatorService, &improvedSobelOperatorService, &geometricService, &histogramValueService, &discreteFourierTransformationSerivce, &stringSerivce);

    graphicEngine.initiateOpenGL(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");


    graphicEngine.addSubwindow(GUI_ID_OPERATION_PANNEL, Point2D(500, 0), Point2D(620, 320), L"Operationpannel");

    graphicEngine.addLabel(0, Point2D(10, 30), 50, L"Methode:", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(10, 50), L"Super Pixels", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SOBEL, Point2D(10, 70), L"Sobel Operator", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_IMPROVED_SOBEL, Point2D(10, 90), L"Improved Sobel", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(10, 130), L"Unknown", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(10, 200), 100, L"Calculate", L"Startet die ausgewählte Methode", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(10, 250), 100, L"Open File", L"Öffnet ein neues File", GUI_ID_OPERATION_PANNEL);

    int pannelX = 10;
    int pannelY = 30;
    graphicEngine.addSubwindow(GUI_ID_GEOMETRICINFO_PANNEL, Point2D(330, 0), Point2D(500, 210), L"Geometrische Merkmale");

    graphicEngine.addLabel(GUI_ID_LABEL_ROI, Point2D(pannelX, pannelY), 100, L"ROI:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_AREA, Point2D(pannelX, pannelY+20), 100, L"Area of Anomaly:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_AREA_ROI, Point2D(pannelX, pannelY + 40), 100, L"Ratio of Area and ROI:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_WIDTH_LENGTH, Point2D(pannelX, pannelY + 60), 100, L"Ratio of width and length:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_SCOPE, Point2D(pannelX, pannelY + 80), 100, L"Defektumfang:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_DEFECT_FOCUS, Point2D(pannelX, pannelY + 100), 100, L"Defektschwerpunkt:", GUI_ID_GEOMETRICINFO_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_ROI, Point2D(pannelX+100, pannelY), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_AREA, Point2D(pannelX + 100, pannelY + 20), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_AREA_ROI, Point2D(pannelX + 100, pannelY+40), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, Point2D(pannelX + 100, pannelY+60), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_SCOPE, Point2D(pannelX + 100, pannelY + 80), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_DEFECT_FOCUS, Point2D(pannelX + 100, pannelY + 100), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);

    graphicEngine.addSubwindow(GUI_ID_GRAYINFO_PANNEL, Point2D(330, 210), Point2D(500, 370), L"Graustufenbasierte Merkmale");

    graphicEngine.addLabel(GUI_ID_LABEL_MEAN, Point2D(pannelX, pannelY), 100, L"Mean:", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_VARIANCE, Point2D(pannelX, pannelY + 20), 100, L"Variance:", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_SKEWNESS, Point2D(pannelX, pannelY + 40), 100, L"Skewness:", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_KURTOSIS, Point2D(pannelX, pannelY + 60), 100, L"kurtosis:", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_POWER, Point2D(pannelX, pannelY + 80), 100, L"Power:", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_ENTROPY, Point2D(pannelX, pannelY + 100), 100, L"Entropy:", GUI_ID_GRAYINFO_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_MEAN, Point2D(pannelX + 100, pannelY), 60, L"", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_VARIANCE, Point2D(pannelX + 100, pannelY + 20), 60, L"", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_SKEWNESS, Point2D(pannelX + 100, pannelY + 40), 60, L"", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_KURTOSIS, Point2D(pannelX + 100, pannelY + 60), 60, L"", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_POWER, Point2D(pannelX + 100, pannelY + 80), 60, L"", GUI_ID_GRAYINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_ENTROPY, Point2D(pannelX + 100, pannelY + 100), 60, L"", GUI_ID_GRAYINFO_PANNEL);

    graphicEngine.run((EventReceiver*)&receiver);
}