#ifndef GraphicEngine_H
#define GraphicEngine_H

#include <vector>
#include <map>
#include <ctime>

#include <irrlicht.h>
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
#include "CGUIBar.h"

#ifdef _WIN32
#include <windows.h>    //GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_QUIT_BUTTON = 1001,
    EET_TIMER_EVENT = 2001
};

class GraphicEngine : IPrimitiveGraphic
{
protected:
    IrrlichtDevice* device;

    video::IVideoDriver* driver;
    IGUIEnvironment* env;

    std::vector<IPrimitiveDraw*> primitiveList;
    std::map<int, IGUIElement*> guiElementMap;

public:
    virtual int initiate(const wchar_t* windowTitle, Point2D windowDimensions);
    virtual int initiateOpenGL(const wchar_t* windowTitle, Point2D windowDimensions);

    virtual void loadFont(const wchar_t* fontFile);

    virtual void addScrollbar(int id, Point2D position, int length, double min, double max, double value, int parentId = -1);
    virtual void addButton(int id, Point2D position, int length, const wchar_t* text, const wchar_t* tooltip = L"", int parentId = -1);
    virtual void addLabel(int id, Point2D position, int length, const wchar_t* text, int parentId = -1);
    virtual void addListBox(int id, Point2D position, Point2D point, const wchar_t* text, int parentId = -1);
    virtual void addInputBox(int id, Point2D point, int length, const wchar_t* text, int parentId = -1);
    virtual void addCheckbox(int id, Point2D position, const wchar_t* text, bool checked = false, int parentId = -1);
    
    virtual bool isCheckboxChecked(int id);
    virtual void enableGUIElement(int id, bool enable);
    virtual void setGUIElementText(int id, const wchar_t* text);
    virtual const wchar_t* getGUIElementText(int id);
    virtual void setGUIElementChecked(int id, bool checked);

    virtual void add2DLine(Point2D one, Point2D two, Color color);
    virtual void add2DPixel(Point2D position, Color color);
    virtual void add2DRectangle(Point2D from, Point2D to, Color color);

    virtual void addImage(int id, Point2D position, const wchar_t* file, int parentId = -1);
    virtual void addImage(Point2D position, const wchar_t* file, int parentId = -1);
    virtual void addSubwindow(int id, Point2D from, Point2D to, const wchar_t* titel);
    virtual void addTabControl(int id, Point2D from, Point2D to, int parentId = -1);
    virtual void addTab(int id, const wchar_t* title, int parentId = -1);
    virtual void addProcessBar(int id, Point2D from, Point2D to, std::wstring imageFile, int parentId = -1);

    virtual void bringToFront(int id);
    virtual void sendToBack(int id);
    virtual void setFocus(int id);

    virtual void removeElement(int id);

    virtual void addPrimitiveDraw(IPrimitiveDraw* primitive);

    virtual int run(EventReceiver* receiver);

private:
    void renderPrimitive(IGeometry* geometry);
    IGUIElement* getParentElement(int parentId);
};

#endif