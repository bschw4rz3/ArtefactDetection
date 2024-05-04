#ifndef EventReceiver_H
#define EventReceiver_H

#include <irrlicht.h>
#include "driverChoice.h"

#include "GraphicEngine.h"
#include "SAppContext.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiver : public IEventReceiver
{
public:
    IGeometry* facet;

public:
    virtual void OnInit(SAppContext* context) = 0;

    virtual bool OnEvent(const SEvent& event) = 0;
};

#endif // !EventReceiver

