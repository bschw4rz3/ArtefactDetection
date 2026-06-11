#include "FileService.h"

void FileService::saveFile(std::string content, std::string fileName)
{
    std::ofstream out(fileName);
    out << content.c_str();
    out.close();
}

bool FileService::exists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

std::string FileService::readFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    std::string str;
    str.reserve(10000000);

    std::string file_contents;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }

    file.close();

    return file_contents;
}