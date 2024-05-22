#include "DirectoryService.h"

DirectoryService::DirectoryService(StringSerivce* stringSerivce, std::string argvZero)
{
	this->stringSerivce = stringSerivce;
	this->argvZero = argvZero;
}

std::string DirectoryService::getCurrentPath()
{
	std::string delimiters = "\\/";
	std::vector<std::string> tokens = this->stringSerivce->splitStringByDelimiters(this->argvZero, delimiters);

	std::string result = "";

	for(int i = 0;i < tokens.size()-1;i++)
	{
		result += tokens[i] + "/";
	}

	return this->stringSerivce->trim(result, "/");
}