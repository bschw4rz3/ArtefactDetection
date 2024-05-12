#include "GraphicEngineExtended.h"

GraphicEngineExtended::GraphicEngineExtended(StringSerivce* stringSerivce) : GraphicEngine()
{
    this->stringSerivce = stringSerivce;
}

void GraphicEngineExtended::addCheckbox(int id, Point2D position, const wchar_t* text, bool checked)
{
    this->checkboxIds.push_back(id);
    GraphicEngine::addCheckbox(id, position, text, checked);
}

void GraphicEngineExtended::resetMethodCheckBoxs()
{
    for (int i = 0; i < this->checkboxIds.size(); i++)
    {
        int id = this->checkboxIds[i];
        IGUICheckBox* element = (IGUICheckBox*) this->guiElementMap[id];
        element->setChecked(false);
    }
}

void GraphicEngineExtended::addFileOpenDialog(int id, std::wstring startDir)
{
    /*
    std::string cStartDir = this->stringSerivce->toString(startDir).c_str();
    irr::c8* c8Path = (char*)cStartDir.c_str();

    IGUIElement* element = this->env->addFileOpenDialog(L"Open file", true, 0, id, false, c8Path);
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, element));*/

    CGUIFileSelector* selector = new CGUIFileSelector(L"File Selector", env, env->getRootGUIElement(), 1, CGUIFileSelector::EFST_OPEN_DIALOG);
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, selector));

    if (selector) {
        // Add some file filters and custom icons for unknown files and directories
        //selector->setCustomFileIcon(driver->getTexture("file.png"));
        //selector->setCustomDirectoryIcon(driver->getTexture("folder.png"));
        //selector->addFileFilter((wchar_t*) L"MP3", (wchar_t*) L"mp3", driver->getTexture("mp3.png"));
        //selector->addFileFilter((wchar_t*) L"PCM WAV", (wchar_t*) L"wav", driver->getTexture("wav.png"));
        //selector->addFileFilter((wchar_t*) L"Windows Media Audio", (wchar_t*) L"wma", driver->getTexture("wma.png"));
        //selector->drop();
        selector->setVisible(false);
    }
}

void GraphicEngineExtended::setVisibility(int id, bool visibile)
{
    IGUIElement* element = this->guiElementMap[id];
    return element->setVisible(visibile);
}

std::wstring GraphicEngineExtended::getSelectedFile(int id)
{
    IGUIFileOpenDialog* element = (IGUIFileOpenDialog*)this->guiElementMap[id];
    return element->getFileName();
}

/*
void GraphicEngineExtended::addScaledImage(int id, Point2D position, const wchar_t* filePath)
{
    const char* fileChars = this->stringSerivce->toChar(filePath);
    CImg<unsigned int> bg(fileChars);
    
    IFileSystem* irrFS = this->device->getFileSystem();
    IWriteFile* file = irrFS->createAndWriteFile(L"bla.png");
    
    //bg.resize(400, 400);
    bg.
    
    IReadFile* file2 = irrFS->createAndOpenFile(L"bla.png");

    ITexture* texture = this->driver->getTexture(file2);
    this->env->addImage(texture, position2d<int>(position.x, position.y), id);

    file->drop();
}*/