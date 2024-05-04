#include "GraphicEngine.h"

int GraphicEngine::initiate(const wchar_t* windowTitle, Point2D windowDimensions)
{
    // ask user for driver
    video::E_DRIVER_TYPE driverType = driverChoiceConsole();
    if (driverType == video::EDT_COUNT)
    {
        return 1;
    }

    // create device and exit if creation failed
    this->device = createDevice(driverType, core::dimension2d<u32>(windowDimensions.x, windowDimensions.y));

    if (this->device == 0)
    {
        return 1; // could not create selected driver.
    }

    this->device->setWindowCaption(windowTitle);
    this->device->setResizable(true);

    this->driver = device->getVideoDriver();
    this->env = device->getGUIEnvironment();

    return 0;
}

void GraphicEngine::loadFont(const wchar_t* fontFile)
{
    IGUISkin* skin = this->env->getSkin();
    IGUIFont* font = this->env->getFont(fontFile);

    if (font)
    {
        skin->setFont(font);
    }

    skin->setFont(this->env->getBuiltInFont(), EGDF_TOOLTIP);
}

void GraphicEngine::addScrollbar(int id, Point2D position, int length, double min, double max, double value)
{
    IGUIScrollBar* scrollBar = this->env->addScrollBar(true, rect<s32>(position.x, position.y, position.x + length, position.y + 32), 0, id);
    scrollBar->setPos(value);
    scrollBar->setMin(min);
    scrollBar->setMax(max);

    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, scrollBar));
}

void GraphicEngine::addButton(int id, Point2D position, int length, const wchar_t* text, const wchar_t* tooltip)
{
    IGUIButton* button = this->env->addButton(rect<s32>(position.x, position.y, position.x + length, position.y + 32), 0, id, text, tooltip);
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, button));
}

void GraphicEngine::addLabel(int id, Point2D position, int length, const wchar_t* text)
{
    IGUIStaticText* label = this->env->addStaticText(text, rect<s32>(position.x, position.y, position.x + length, position.y + 32), false);
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, label));
}

void GraphicEngine::addListBox(int id, Point2D position, Point2D point, const wchar_t* text)
{
    IGUIListBox* listbox = this->env->addListBox(rect<s32>(position.x, position.y, position.x, position.y));
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, listbox));
}

void GraphicEngine::addInputBox(int id, Point2D point, int length, const wchar_t* text)
{
    IGUIEditBox* input = this->env->addEditBox(text, rect<s32>(point.x, point.y, point.x + length, point.y + 32));
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, input));
}

void GraphicEngine::enableGUIElement(int id, bool enable)
{
    IGUIElement* element = this->guiElementMap[id];
    element->setEnabled(enable);
}

void GraphicEngine::setGUIElementText(int id, const wchar_t* text)
{
    IGUIElement* element = this->guiElementMap[id];
    element->setText(text);
}

void GraphicEngine::add2DLine(Point2D one, Point2D two, Color color)
{
    this->driver->draw2DLine(core::position2d<s32>(one.x, one.y), core::position2d<s32>(two.x, two.y), SColor(color.a, color.r, color.g, color.b));
}

void GraphicEngine::add2DPixel(Point2D position, Color color)
{
    this->driver->drawPixel(position.x, position.y, SColor(color.a, color.r, color.g, color.b));
}

void GraphicEngine::add2DRectangle(Point2D from, Point2D to, Color color)
{
    this->driver->draw2DRectangleOutline(rect<s32>(from.x, from.y, to.x, to.y), SColor(color.a, color.r, color.g, color.b));
}

void GraphicEngine::addScaledImage(int id, Point2D position, const wchar_t* file)
{/*
    const char* fileChars = wchar_to_char(file);

    CImg<unsigned int> bg(fileChars);

    bg.resize(400, 400);
    bg.save()

    IFileSystem* irrFS = this->device->getFileSystem();
    IReadFile* file = irrFS->createMemoryReadFile(data, SizeofResource(NULL, res), "", true);
    //tex = driver->getTexture(file);

    ITexture* texture = this->driver->getTexture(file);
    this->env->addImage(texture, position2d<int>(position.x, position.y), id);*/

    //file->drop();
}

void GraphicEngine::addImage(int id, Point2D position, const wchar_t* file)
{
    ITexture* texture = this->driver->getTexture(file);
    this->env->addImage(texture, position2d<int>(position.x, position.y), id);
}

void GraphicEngine::addImage(Point2D position, const wchar_t* file)
{
    this->addImage(-1, position, file);
}

void GraphicEngine::addPrimitiveDraw(IPrimitiveDraw* primitive)
{
    this->primitiveList.push_back(primitive);
}

int GraphicEngine::run(EventReceiver* receiver)
{
    // Store the appropriate data in a context structure.
    SAppContext context;
    context.device = this->device;
    context.counter = 0;

    receiver->OnInit(&context);

    // And tell the device to use our custom event receiver.
    this->device->setEventReceiver(receiver);

    u32 lastTimeEventTrigger = device->getTimer()->getTime();

    while (this->device->run() && this->driver)
    {
        u32 timeNow = device->getTimer()->getTime();

        if (timeNow - lastTimeEventTrigger > 1000)
        {
            SEvent event;
            event.EventType = EET_USER_EVENT;

            device->postEventFromUser(event);

            lastTimeEventTrigger = device->getTimer()->getTime();
        }

        if (this->device->isWindowActive())
        {
            this->driver->beginScene(true, true, SColor(0, 200, 200, 200));

	        this->env->drawAll();
	        this->renderPrimitive(receiver->facet);

	        this->driver->endScene();      
        }
    }

    this->device->drop();

    return 0;
}

void GraphicEngine::renderPrimitive(IGeometry* geometry)
{
    if (geometry == NULL)
    {
        return;
    }

    for (int i = 0; i < this->primitiveList.size(); i++)
    {
        IPrimitiveDraw* entry = this->primitiveList[i];
        entry->render(this, geometry);
    }
}
/*
char* wchar_to_char(const wchar_t* pwchar)
{
    // get the number of characters in the string.
    int currentCharIndex = 0;
    char currentChar = pwchar[currentCharIndex];

    while (currentChar != '\0')
    {
        currentCharIndex++;
        currentChar = pwchar[currentCharIndex];
    }

    const int charCount = currentCharIndex + 1;

    // allocate a new block of memory size char (1 byte) instead of wide char (2 bytes)
    char* filePathC = (char*)malloc(sizeof(char) * charCount);

    for (int i = 0; i < charCount; i++)
    {
        // convert to char (1 byte)
        char character = pwchar[i];

        *filePathC = character;

        filePathC += sizeof(char);

    }
    filePathC += '\0';

    filePathC -= (sizeof(char) * charCount);

    return filePathC;
}*/