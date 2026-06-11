#ifndef TempFileNameService_H
#define TempFileNameService_H

#include <activation.h>
#include <iostream>
#include <cstdio>
#include <sstream> 
#include <thread>
#include <future>
#include <algorithm>
#include <string>
#include <vector>

#include "DirectoryService.h"
#include "StringSerivce.h"

class TempFileNameService
{
private:
	DirectoryService* directoryService;
	StringSerivce* stringSerivce;

	std::string rootDir;
	int tempFileIndex;

public:
	TempFileNameService(DirectoryService* directoryService, StringSerivce* stringSerivce);

	std::string generateFileNamePng();
	std::string generateFileNameJson();

	void removeTempFiles();
	std::string getFileName(std::string path);

private:
	std::string generateFileName();
};

#endif