#ifndef GraphicEngine_H
#define GraphicEngine_H

#include <vector>
#include <map>
#include <ctime>

#include "irrlicht.h"
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "SAppContext.h"
#include "Skin.h"
#include "Point2D.h"
#include "Color.h"
#include "IPrimitiveDraw.h"
#include "IPrimitiveGraphic.h"
#include "EventReceiver.h"
#include "IEventReceiver.h"

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_QUIT_BUTTON = 1001,
    EET_TIMER_EVENT = 2001
};

class GraphicEngine : IPrimitiveGraphic
{
private:
    IrrlichtDevice* device;

    video::IVideoDriver* driver;
    IGUIEnvironment* env;

    std::vector<IPrimitiveDraw*> primitiveList;
    std::map<int, IGUIElement*> guiElementMap;

public:
    int initiate(const wchar_t* windowTitle, Point2D windowDimensions);
    void loadFont(const wchar_t* fontFile);

    void addScrollbar(int id, Point2D position, int length, double min, double max, double value);
    void addButton(int id, Point2D position, int length, const wchar_t* text, const wchar_t* tooltip = L"");
    void addLabel(int id, Point2D position, int length, const wchar_t* text);
    void addListBox(int id, Point2D position, Point2D point, const wchar_t* text);
    void addInputBox(int id, Point2D point, int length, const wchar_t* text);

    void enableGUIElement(int id, bool enable);
    void setGUIElementText(int id, const wchar_t* text);

    void add2DLine(Point2D one, Point2D two, Color color);
    void add2DPixel(Point2D position, Color color);
    void add2DRectangle(Point2D from, Point2D to, Color color);

    void addImage(int id, Point2D position, const wchar_t* file);
    void addImage(Point2D position, const wchar_t* file);
    void addScaledImage(int id, Point2D position, const wchar_t* file);

    void addPrimitiveDraw(IPrimitiveDraw* primitive);

    int run(EventReceiver* receiver);

private:
    void renderPrimitive(IGeometry* geometry);
};

#endif