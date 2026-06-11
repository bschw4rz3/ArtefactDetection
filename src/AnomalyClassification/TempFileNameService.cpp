#include "TempFileNameService.h"

TempFileNameService::TempFileNameService(DirectoryService* directoryService, StringSerivce* stringSerivce)
{
    this->directoryService = directoryService;
    this->stringSerivce = stringSerivce;

    std::filesystem::path cwd = std::filesystem::current_path();
    this->rootDir = cwd.string();
}

std::string TempFileNameService::generateFileNamePng()
{
    std::string fileName = this->generateFileName();
    fileName += ".png";

    return fileName;
}

std::string TempFileNameService::generateFileNameJson()
{
    std::string fileName = this->generateFileName();
    fileName += ".json";

    return fileName;
}

std::string TempFileNameService::generateFileName()
{
    std::stringstream stream;
    std::string age_as_string;

    stream << this->tempFileIndex;
    stream >> age_as_string;

    std::string fileName = this->rootDir + "/temp";
    fileName += age_as_string;

    this->tempFileIndex++;

    return fileName;
}

void TempFileNameService::removeTempFiles()
{
    std::vector<std::string> fileNames = this->directoryService->getFileNames(this->rootDir);

    for (std::string fileName : fileNames)
    {
        if (this->stringSerivce->contains(fileName, "temp"))
        {
            std::remove(fileName.c_str());
        }
    }
}

std::string TempFileNameService::getFileName(std::string path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}