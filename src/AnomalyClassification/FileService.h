#ifndef FileService_H
#define FileService_H

#include <fstream>
#include <string>
#include <iostream>

class FileService
{
public:
	void saveFile(std::string content, std::string fileName);
	bool exists(const std::string& name);
	std::string readFile(std::string fileName);
};

#endif