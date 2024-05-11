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
    std::string cStartDir = this->stringSerivce->toString(startDir).c_str();
    irr::c8* c8Path = (char*)cStartDir.c_str();

    IGUIElement* element = this->env->addFileOpenDialog(L"Open file", true, 0, id, false, c8Path);
    this->guiElementMap.insert(std::pair<int, IGUIElement*>(id, element));
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