#ifndef DirectoryService_H
#define DirectoryService_H

#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <iostream>
#include <filesystem>

#include "StringSerivce.h"

class DirectoryService
{
private:
	StringSerivce* stringSerivce;
	std::string argvZero;

public:
	DirectoryService(StringSerivce* stringSerivce);

	std::vector<std::string> getFileNames(std::string path);
};

#endif