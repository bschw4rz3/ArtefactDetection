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
#include "DirectoryService.h"
#include "HuMomentsService.h"
#include "LbpService.h"

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
    DiscreteFourierTransformationSerivce discreteFourierTransformationSerivce(&classicSobelOperatorService, &colorService);
    DirectoryService directoryService(&stringSerivce);
    HuMomentsService huMomentsService(&colorService);
    SdSfService sdSfService(&classicSobelOperatorService, &geometricService, &mathSerivce, &stringSerivce, &colorService);
    LbpService lbpService(&geometricService, &mathSerivce, &colorService);

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &superPixelService, &classicSobelOperatorService, &improvedSobelOperatorService, &geometricService, &histogramValueService, &discreteFourierTransformationSerivce, &huMomentsService, &sdSfService, &lbpService, &directoryService, &stringSerivce);

    Point2D windowSize(1280, 720);

    graphicEngine.initiateOpenGL(L"Part Cover", windowSize);
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");
    graphicEngine.addSubwindow(GUI_ID_OPERATION_PANNEL, Point2D(windowSize.x - 180, 0), Point2D(windowSize.x, 320), L"Operationpannel");

    graphicEngine.addLabel(0, Point2D(10, 30), 50, L"Methode:", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(10, 50), L"Super Pixels", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SOBEL, Point2D(10, 70), L"Sobel Operator", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_IMPROVED_SOBEL, Point2D(10, 90), L"Improved Sobel", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION, Point2D(10, 110), L"Discrete Fourier Transformation", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_HU_MOMENT, Point2D(10, 130), L"Hu Moment", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SDSF, Point2D(10, 150), L"SdSf", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_LBP, Point2D(10, 170), L"LBP", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(10, 190), L"Unknown", false, GUI_ID_OPERATION_PANNEL);    

    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(10, 250), 100, L"Calculate", L"Startet die ausgewählte Methode", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(10, 280), 100, L"Open File", L"Öffnet ein neues File", GUI_ID_OPERATION_PANNEL);

    int pannelX = 10;
    int pannelY = 30;
    graphicEngine.addSubwindow(GUI_ID_GEOMETRICINFO_PANNEL, Point2D(windowSize.x-360, 0), Point2D(windowSize.x-180, 270), L"Geometrische Merkmale");
  
    graphicEngine.addLabel(GUI_ID_LABEL_DEFECT_COLOR, Point2D(pannelX, pannelY), 100, L"Defect color:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_BACKGROUND_COLOR, Point2D(pannelX, pannelY + 20), 100, L"Background color:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_ROI, Point2D(pannelX, pannelY + 40), 100, L"ROI:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_AREA, Point2D(pannelX, pannelY+60), 100, L"Area of Anomaly:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_AREA_ROI, Point2D(pannelX, pannelY + 80), 100, L"Ratio of Area and ROI:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_RATIO_WIDTH_LENGTH, Point2D(pannelX, pannelY + 100), 100, L"Ratio of width and length:\n(Slimness)", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_SCOPE, Point2D(pannelX, pannelY + 120), 100, L"Defektumfang:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_DEFECT_FOCUS, Point2D(pannelX, pannelY + 140), 100, L"Defektschwerpunkt:", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_RECTANGULARITY, Point2D(pannelX, pannelY + 160), 100, L"Rectangularity:", GUI_ID_GEOMETRICINFO_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_DEFECT_COLOR, Point2D(pannelX + 100, pannelY), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_BACKGROUND_COLOR, Point2D(pannelX + 100, pannelY + 20), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_ROI, Point2D(pannelX+100, pannelY + 40), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_AREA, Point2D(pannelX + 100, pannelY + 60), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_AREA_ROI, Point2D(pannelX + 100, pannelY+80), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, Point2D(pannelX + 100, pannelY+100), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_SCOPE, Point2D(pannelX + 100, pannelY + 120), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_DEFECT_FOCUS, Point2D(pannelX + 100, pannelY + 140), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_RECTANGULARITY, Point2D(pannelX + 100, pannelY + 160), 60, L"", GUI_ID_GEOMETRICINFO_PANNEL);

    graphicEngine.addSubwindow(GUI_ID_GRAYINFO_PANNEL, Point2D(windowSize.x-360, 270), Point2D(windowSize.x-180, 480), L"Graustufenbasierte Merkmale");

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

    graphicEngine.addSubwindow(GUI_ID_HU_MOMENT_PANNEL, Point2D(windowSize.x - 180, 320), Point2D(windowSize.x, 520), L"Hu Moments");

    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN, Point2D(pannelX, pannelY), 120, L"Own Calculation:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_1, Point2D(pannelX, pannelY + 20), 25, L"Hu 1:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_2, Point2D(pannelX, pannelY + 40), 25, L"Hu 2:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_3, Point2D(pannelX, pannelY + 60), 25, L"Hu 3:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_4, Point2D(pannelX, pannelY + 80), 25, L"Hu 4:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_5, Point2D(pannelX, pannelY + 100), 25, L"Hu 5:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_6, Point2D(pannelX, pannelY + 120), 25, L"Hu 6:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OWN_7, Point2D(pannelX, pannelY + 140), 25, L"Hu 7:", GUI_ID_HU_MOMENT_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_1, Point2D(pannelX + 25, pannelY + 20), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_2, Point2D(pannelX + 25, pannelY + 40), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_3, Point2D(pannelX + 25, pannelY + 60), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_4, Point2D(pannelX + 25, pannelY + 80), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_5, Point2D(pannelX + 25, pannelY + 100), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_6, Point2D(pannelX + 25, pannelY + 120), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OWN_7, Point2D(pannelX + 25, pannelY + 140), 120, L"", GUI_ID_HU_MOMENT_PANNEL);

    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV, Point2D(pannelX + 90, pannelY), 120, L"openCV:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_1, Point2D(pannelX + 90, pannelY + 20), 25, L"Hu 1:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_2, Point2D(pannelX + 90, pannelY + 40), 25, L"Hu 2:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_3, Point2D(pannelX + 90, pannelY + 60), 25, L"Hu 3:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_4, Point2D(pannelX + 90, pannelY + 80), 25, L"Hu 4:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_5, Point2D(pannelX + 90, pannelY + 100), 25, L"Hu 5:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_6, Point2D(pannelX + 90, pannelY + 120), 25, L"Hu 6:", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_HU_OPENCV_7, Point2D(pannelX + 90, pannelY + 140), 25, L"Hu 7:", GUI_ID_HU_MOMENT_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_1, Point2D(pannelX + 115, pannelY + 20), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_2, Point2D(pannelX + 115, pannelY + 40), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_3, Point2D(pannelX + 115, pannelY + 60), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_4, Point2D(pannelX + 115, pannelY + 80), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_5, Point2D(pannelX + 115, pannelY + 100), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_6, Point2D(pannelX + 115, pannelY + 120), 120, L"", GUI_ID_HU_MOMENT_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_HU_OPENCV_7, Point2D(pannelX + 115, pannelY + 140), 120, L"", GUI_ID_HU_MOMENT_PANNEL);

    graphicEngine.run((EventReceiver*)&receiver);
}