#ifndef StringSerivce_H
#define StringSerivce_H

#include <string>

class StringSerivce
{
public:
	std::string toString(std::wstring input);
	std::wstring toWString(std::string input);
	char* toChar(const wchar_t* pwchar);
};

#endif