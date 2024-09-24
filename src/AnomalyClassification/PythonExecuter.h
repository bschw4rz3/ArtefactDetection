#ifndef PythonExecuter_H
#define PythonExecuter_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <windows.h>
#include <vector>
#include <complex>
#include <map>
#include <filesystem>

#include "StringSerivce.h"
#include "TempFileNameService.h"
#include "FileService.h"

class PythonExecuter
{
protected:
	StringSerivce* stringService;
	TempFileNameService* tempFileNameService;
	FileService* fileSerivce;

	std::string directoryPath;

public:
	PythonExecuter(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce);
	std::map<double, std::vector<double>> calculate(std::vector<std::complex<double>> input);

protected:
	virtual std::string getScriptName() = 0;
	virtual std::string getParameter(std::vector<std::complex<double>> input);
	virtual std::string exec(std::string cmd);

	std::map<double, std::vector<double>> toMap(std::string resultJson);
};

class MorletWaveletPythonService : public PythonExecuter
{
public:
	MorletWaveletPythonService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) : 
		PythonExecuter(stringService, tempFileNameService, fileSerivce) {};

	virtual std::string getScriptName()
	{
		return "morletWavlet.py";
	}
};

#endif