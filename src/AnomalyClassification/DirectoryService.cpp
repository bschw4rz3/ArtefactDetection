#include "DirectoryService.h"

DirectoryService::DirectoryService(StringSerivce* stringSerivce)
{
	this->stringSerivce = stringSerivce;
	this->argvZero = argvZero;
}

std::vector<std::string> DirectoryService::getFileNames(std::string path)
{
	std::vector<std::string> result;
	
	std::filesystem::directory_iterator directories = std::filesystem::directory_iterator(path);
	
	for (std::filesystem::directory_entry entry : directories)
	{
		std::filesystem::path entryPath = entry.path();
		std::string path = entryPath.string();
		result.push_back(path);
	}

	return result;
}