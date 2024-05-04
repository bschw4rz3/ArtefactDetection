#ifndef MyEventReceiver_H
#define MyEventReceiver_H

#include <activation.h>
#include<iostream>

#include <thread>
#include <future>

#include <irrlicht.h>
#include "driverChoice.h"

#include "../IrrlichtWrapper/GraphicEngine.h"
#include "../IrrlichtWrapper/SAppContext.h"
#include "../IrrlichtWrapper/EventReceiver.h"

#define stringify( name ) #name

enum {
    GUI_ID_IMAGE
};

class MyEventReceiver : public EventReceiver
{
private:
    GraphicEngine* graphicEngine;

    SAppContext* context;

    std::thread currentAlgorithmThread;
    std::thread currentSimulationThread;

    bool isRunning;
    bool isAbbord;

    wchar_t progressSymbol;

    double coverageOfLastRun;
    int imageCountOfLastRun;

public:
    MyEventReceiver(GraphicEngine* graphic_engine);

    ~MyEventReceiver();

    virtual void OnInit(SAppContext* context);

    bool setForm(s32 id);
    virtual bool OnEvent(const SEvent& event);
};

#endif