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