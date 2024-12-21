#ifndef StringSerivce_H
#define StringSerivce_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <complex>

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
	std::vector<std::string> split(std::string inputString, char delimiter);

	int toInt(std::wstring text);
	int toInt(std::string text);

	double toDouble(std::string strValue);
	std::string complexToPythonValue(std::complex<double> value);

	void trim(std::string& s, const std::vector<char>& symbols);
	void ltrim(std::string& s, const std::vector<char>& symbols);
	void rtrim(std::string& s, const std::vector<char>& symbols);
};

#endif