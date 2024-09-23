// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <string>

#include "DependencyInjectionService.h"
#include "MyEventReceiver.h"

int main()
{
    DependencyInjectionService dependencyInjectionService;

    GraphicEngineExtended graphicEngine(dependencyInjectionService.stringSerivce);
    MyEventReceiver receiver(&graphicEngine, &dependencyInjectionService);

    Point2D windowSize(1280, 1040);

    graphicEngine.initiateOpenGL(L"Part Cover", windowSize);
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");
    graphicEngine.addSubwindow(GUI_ID_OPERATION_PANNEL, Point2D(windowSize.x - 180, 0), Point2D(windowSize.x, 580), L"Operationpannel");

    graphicEngine.addLabel(0, Point2D(10, 30), 50, L"Methode:", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SUPERPIXELS, Point2D(10, 50), L"Super Pixels", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SOBEL, Point2D(10, 70), L"Sobel Operator", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_IMPROVED_SOBEL, Point2D(10, 90), L"Improved Sobel", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION, Point2D(10, 110), L"Discrete Fourier Transformation", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_HU_MOMENT, Point2D(10, 130), L"Hu Moment", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_SDSF, Point2D(10, 150), L"SdSf", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_LBP, Point2D(10, 170), L"LBP", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_COMPLETED_LBP, Point2D(10, 190), L"Completed LBP", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_GLCM, Point2D(10, 210), L"GLCM", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_HOG, Point2D(10, 230), L"HOG", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_GABOR, Point2D(10, 250), L"GaborFilter", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_WAVELET, Point2D(10, 270), L"Wavelet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION_CV, Point2D(10, 290), L"Discrete Fourier Transformation (CV)", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_FOURIER_DISCRIPTOR, Point2D(10, 310), L"Fourier Discriptor", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_DAUBECHIES_FOUR_WAVELET, Point2D(10, 330), L"Daubechies four wavelet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_MORLET_WAVELET, Point2D(10, 350), L"Morelet wavelet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_MORLET_WAVELET_FFT, Point2D(10, 370), L"Morelet FFT", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_HAAR_WAVLET, Point2D(10, 390), L"Haarwavlet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_DAUBECHIES_SECOND, Point2D(10, 410), L"Daubechies 2. Wavlet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_BIOR_WAVLET, Point2D(10, 430), L"Bior Wavlet", false, GUI_ID_OPERATION_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_UNKNOWN, Point2D(10, 450), L"Unknown", false, GUI_ID_OPERATION_PANNEL);

    graphicEngine.addButton(GUI_ID_BUTTON_CHOOSE_FILE, Point2D(10, 525), 70, L"Open File", L"Öffnet ein neues File", GUI_ID_OPERATION_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_CACLULATE, Point2D(90, 525), 70, L"Calculate", L"Startet die ausgewählte Methode", GUI_ID_OPERATION_PANNEL);

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

    graphicEngine.addSubwindow(GUI_ID_HU_MOMENT_PANNEL, Point2D(windowSize.x - 360, 480), Point2D(windowSize.x-180, 480+200), L"Hu Moments");

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

    graphicEngine.addSubwindow(GUI_ID_HU_GLCM_PANNEL, Point2D(windowSize.x - 180, 570), Point2D(windowSize.x, 720), L"GLCM values");

    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_ENERGY, Point2D(pannelX, pannelY), 120, L"Energy: ", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_CONTRAST, Point2D(pannelX, pannelY + 20), 120, L"Contrast: ", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_HOMOGENITY, Point2D(pannelX, pannelY + 40), 120, L"Homogenity: ", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_IDM, Point2D(pannelX, pannelY + 60), 120, L"IDM: ", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_ENTROPY, Point2D(pannelX, pannelY + 80), 120, L"Entropy: ", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_GLCM_MEAN, Point2D(pannelX, pannelY + 100), 120, L"Mean: ", GUI_ID_HU_GLCM_PANNEL);

    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_ENERGY, Point2D(pannelX + 60, pannelY), 60, L"", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_CONTRAST, Point2D(pannelX + 60, pannelY + 20), 60, L"", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_HOMOGENITY, Point2D(pannelX + 60, pannelY + 40), 60, L"", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_IDM, Point2D(pannelX + 60, pannelY + 60), 60, L"", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_ENTROPY, Point2D(pannelX + 60, pannelY + 80), 60, L"", GUI_ID_HU_GLCM_PANNEL);
    graphicEngine.addLabel(GUI_ID_VALUE_GLCM_MEAN, Point2D(pannelX + 60, pannelY + 100), 60, L"", GUI_ID_HU_GLCM_PANNEL);

    graphicEngine.addSubwindow(GUI_ID_CLASSIFY_PANNEL, Point2D(500, 0), Point2D(windowSize.x - 360, 1060), L"Classify");

    graphicEngine.addLabel(GUI_ID_LABEL_CHECKBOX_CLASSIFY, Point2D(pannelX, pannelY + 10), 60, L"Classify method:", GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR, Point2D(pannelX, pannelY + 30), L"k-Nearest-Neighbor", false, GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_CLASSIFY_SUPPORT_VECTOR_MACHINE, Point2D(pannelX, pannelY + 50), L"support vector machine", false, GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addCheckbox(GUI_ID_CHECKBOX_CLASSIFY_DECISION_TREE, Point2D(pannelX, pannelY + 70), L"decision trees", false, GUI_ID_CLASSIFY_PANNEL);

    graphicEngine.addLabel(GUI_ID_LABEL_CLASSIFY_INDEX, Point2D(pannelX + 180, pannelY + 10), 60, L"", GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_GENERATE_TRAININGS_DATA, Point2D(pannelX + 180, pannelY + 30), 200, L"Generate trainings data", L"Generiere neu Trainingsdaten", GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_CLASSIFY, Point2D(pannelX + 180, pannelY + 60), 200, L"Classify", L"Klassifizieren des aktuellen Bildes", GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addLabel(GUI_ID_LABEL_PARAMETER, Point2D(pannelX + 10, pannelY + 110), 100, L"Parameter:", GUI_ID_CLASSIFY_PANNEL);
    graphicEngine.addInputBox(GUI_ID_INPUTBOX_PARAMETER, Point2D(pannelX + 180, pannelY + 100), 200, L"", GUI_ID_CLASSIFY_PANNEL);

    graphicEngine.setVisibility(GUI_ID_LABEL_PARAMETER, false);
    graphicEngine.setVisibility(GUI_ID_INPUTBOX_PARAMETER, false);
    //graphicEngine.addProcessBar(GUI_ID_PROCESSBAR_CLASSIFY, Point2D(10, pannelY + 80), Point2D(pannelX + 200, pannelY + 100), L"processbar.bmp", GUI_ID_CLASSIFY_PANNEL);

    graphicEngine.addSubwindow(GUI_ID_MESSAGE_PANNEL, Point2D((windowSize.x/2)-100, (windowSize.y/2)-50), Point2D((windowSize.x/2)+100, (windowSize.y/2)+50), L"Message");
    graphicEngine.addLabel(GUI_ID_LABEL_MESSAGE, Point2D(10, 30), 180, L"", GUI_ID_MESSAGE_PANNEL);
    graphicEngine.addButton(GUI_ID_BUTTON_MESSAGE_OK, Point2D(75, 70), 60, L"OK", L"", GUI_ID_MESSAGE_PANNEL);
    graphicEngine.setVisibility(GUI_ID_MESSAGE_PANNEL, false);

    graphicEngine.run((EventReceiver*)&receiver);
}