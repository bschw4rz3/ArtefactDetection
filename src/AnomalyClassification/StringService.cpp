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