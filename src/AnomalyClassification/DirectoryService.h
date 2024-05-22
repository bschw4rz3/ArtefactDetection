#ifndef DirectoryService_H
#define DirectoryService_H

#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <regex>

#include "StringSerivce.h"

class DirectoryService
{
private:
	StringSerivce* stringSerivce;
	std::string argvZero;

public:
	DirectoryService(StringSerivce* stringSerivce, std::string argvZero);

	std::string getCurrentPath();
};

#endif