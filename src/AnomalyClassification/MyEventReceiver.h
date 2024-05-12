#ifndef MyEventReceiver_H
#define MyEventReceiver_H

#include <activation.h>
#include<iostream>

#include <thread>
#include <future>

#include <irrlicht.h>
#include "driverChoice.h"

#include "GraphicEngineExtended.h"
#include "../IrrlichtWrapper/SAppContext.h"
#include "../IrrlichtWrapper/EventReceiver.h"

#include "SuperPixelService.h"

#define stringify( name ) #name

enum {
    GUI_ID_IMAGE,
    GUI_ID_CHECKBOX_SUPERPIXELS,
    GUI_ID_CHECKBOX_UNKNOWN,
    GUI_ID_BUTTON_CACLULATE,
    GUI_ID_BUTTON_CHOOSE_FILE,
    GUI_ID_DIALOG_CHOOSE_FILE
};

class MyEventReceiver : public EventReceiver
{
private:
    GraphicEngineExtended* graphicEngine;
    SAppContext* context;
    StringSerivce* stringSerivce;

    SuperPixelService* superPixelService;

    std::thread currentAlgorithmThread;
    std::thread currentSimulationThread;

    bool isRunning;
    bool isAbbord;

    wchar_t progressSymbol;

    double coverageOfLastRun;
    int imageCountOfLastRun;

    std::wstring selectedFile;

public:
    MyEventReceiver(GraphicEngineExtended* graphic_engine, SuperPixelService* superPixelService, StringSerivce* stringSerivce);

    ~MyEventReceiver();

    virtual void OnInit(SAppContext* context);

    bool setForm(s32 id);
    virtual bool OnEvent(const SEvent& event);

private:
    void onCalculateSuperPixels();
    void onSelectFile(core::stringc fileName);

    void superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath);
};

#endif