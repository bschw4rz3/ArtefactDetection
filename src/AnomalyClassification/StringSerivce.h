#ifndef StringSerivce_H
#define StringSerivce_H

#include <string>
#include <sstream>

class StringSerivce
{
public:
	std::string toString(std::wstring input);
	std::wstring toWString(std::string input);
	char* toChar(const wchar_t* pwchar);

	std::wstring intToWString(int value);
	std::wstring doubleToWString(double value);

	std::string intToString(int value);
	std::string doubleToString(double value);

	bool contains(std::string string, std::string term);
};

#endif