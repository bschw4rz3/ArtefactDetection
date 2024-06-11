#ifndef MyEventReceiver_H
#define MyEventReceiver_H

#include <activation.h>
#include <iostream>
#include <cstdio>
#include <sstream> 
#include <thread>
#include <future>

#include <irrlicht.h>
#include "driverChoice.h"

#include "GraphicEngineExtended.h"
#include "../IrrlichtWrapper/SAppContext.h"
#include "../IrrlichtWrapper/EventReceiver.h"

#include "SuperPixelService.h"
#include "ClassicSobelOperatorService.h"
#include "ImprovedSobelOperatorService.h"
#include "GeometricService.h"

#define stringify( name ) #name

enum {
    GUI_ID_IMAGE,
    GUI_ID_IMAGE_1,
    GUI_ID_IMAGE_2,
    GUI_ID_CHECKBOX_SUPERPIXELS,
    GUI_ID_CHECKBOX_SOBEL,
    GUI_ID_CHECKBOX_IMPROVED_SOBEL,
    GUI_ID_CHECKBOX_UNKNOWN,
    GUI_ID_BUTTON_CACLULATE,
    GUI_ID_BUTTON_CHOOSE_FILE,
    GUI_ID_DIALOG_CHOOSE_FILE,
    GUI_ID_LABEL_ROI,
    GUI_ID_LABEL_AREA,
    GUI_ID_LABEL_RATIO_AREA_ROI,
    GUI_ID_LABEL_RATIO_WIDTH_LENGTH,
    GUI_ID_VALUE_ROI,
    GUI_ID_VALUE_AREA,
    GUI_ID_VALUE_RATIO_AREA_ROI,
    GUI_ID_VALUE_RATIO_WIDTH_LENGTH
};

class MyEventReceiver : public EventReceiver
{
private:
    GraphicEngineExtended* graphicEngine;
    SAppContext* context;
    StringSerivce* stringSerivce;

    SuperPixelService* superPixelService;
    ClassicSobelOperatorService* sobelOperatorSerivce;
    ImprovedSobelOperatorService* improvedSobelOperatorService;
    GeometricService* geometricService;

    std::thread currentAlgorithmThread;
    std::thread currentSimulationThread;

    bool isRunning;
    bool isAbbord;

    wchar_t progressSymbol;

    double coverageOfLastRun;
    int imageCountOfLastRun;

    std::wstring selectedFile;
    int tempFileIndex;

public:
    MyEventReceiver(GraphicEngineExtended* graphic_engine, SuperPixelService* superPixelService, ClassicSobelOperatorService* sobelOperatorSerivce, ImprovedSobelOperatorService* improvedSobelOperatorService, GeometricService* geometricService, StringSerivce* stringSerivce);
    ~MyEventReceiver();

    virtual void OnInit(SAppContext* context);

    bool setForm(s32 id);
    virtual bool OnEvent(const SEvent& event);

private:
    void onCalculateSuperPixels();
    void onCalculateSobelOperator();
    void onCalculateImprovedSobelOperator();

    void onSelectFile(core::stringc fileName);
    void onResetImages();

    void superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath);
    std::string generateFileName();
};

#endif