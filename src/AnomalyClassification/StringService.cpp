#include "StringSerivce.h"

std::string StringSerivce::toString(std::wstring input)
{
    std::string s(input.begin(), input.end());
    return s;
}

std::wstring StringSerivce::toWString(std::string input)
{
    std::wstring s(input.begin(), input.end());
    return s;
}

char* StringSerivce::toChar(const wchar_t* pwchar)
{
    // get the number of characters in the string.
    int currentCharIndex = 0;
    char currentChar = pwchar[currentCharIndex];

    while (currentChar != '\0')
    {
        currentCharIndex++;
        currentChar = pwchar[currentCharIndex];
    }

    const int charCount = currentCharIndex + 1;

    // allocate a new block of memory size char (1 byte) instead of wide char (2 bytes)
    char* filePathC = (char*)malloc(sizeof(char) * charCount);

    for (int i = 0; i < charCount; i++)
    {
        // convert to char (1 byte)
        char character = pwchar[i];

        *filePathC = character;

        filePathC += sizeof(char);

    }
    filePathC += '\0';

    filePathC -= (sizeof(char) * charCount);

    return filePathC;
}

std::wstring StringSerivce::intToWString(int value)
{
    std::wostringstream myStringStream;
    myStringStream << value;
    std::wstring concatenatedStr = myStringStream.str();

    return concatenatedStr;
}

std::wstring StringSerivce::doubleToWString(double value)
{
    std::ostringstream strs;
    strs << value;
    return this->toWString(strs.str());
}

std::string StringSerivce::intToString(int value)
{
    std::stringstream myStringStream;
    myStringStream << value;
    std::string concatenatedStr = myStringStream.str();

    return concatenatedStr;
}

int StringSerivce::toInt(std::wstring text)
{
    std::string strValue = this->toString(text);
    return std::atoi(strValue.c_str());
}

double StringSerivce::toDouble(std::string strValue)
{
    return std::stod(strValue.c_str());
}

std::string StringSerivce::doubleToString(double value)
{
    std::ostringstream strs;
    strs << value;
    return strs.str();
}

bool StringSerivce::contains(std::string string, std::string term)
{
    return string.find(term) != std::string::npos;
}

std::vector<std::string> StringSerivce::split(std::string inputString, char delimiter)
{
    // Create a stringstream object with the input string 
    std::stringstream ss(inputString);

    // Tokenize the input string by comma delimiter 
    std::string token;
    std::vector<std::string> tokens;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string StringSerivce::complexToPythonValue(std::complex<double> value)
{
    return this->doubleToString(value.real()) + "+" + this->doubleToString(value.imag()) + "j";
}

void StringSerivce::trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}

void StringSerivce::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '[' && ch != ']' && ch != ',';
        }));
}

void StringSerivce::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '[' && ch != ']' && ch != ',';
        }).base(), s.end());
}