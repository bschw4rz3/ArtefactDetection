#include "GraphicEngineExtended.h"

GraphicEngineExtended::GraphicEngineExtended(StringSerivce* stringSerivce) : GraphicEngine()
{
    this->stringSerivce = stringSerivce;
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