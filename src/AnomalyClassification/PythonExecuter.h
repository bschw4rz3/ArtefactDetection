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
#include "FDResult.h"

class PythonExecuter
{
protected:
	StringSerivce* stringService;
	TempFileNameService* tempFileNameService;
	FileService* fileSerivce;

	std::string directoryPath;

public:
	PythonExecuter(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce);

protected:
	virtual std::string getScriptName() = 0;

	virtual std::string getParameter(std::vector<std::complex<double>> input);
	virtual std::string getParameter(std::vector<std::vector<std::complex<double>>> input);
	virtual std::string exec(std::string cmd);
};

class PythonWaveletExecuter : public PythonExecuter
{
public:
	PythonWaveletExecuter(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonExecuter(stringService, tempFileNameService, fileSerivce) {};

	std::map<double, std::vector<double>> calculate(std::vector<std::complex<double>> input);

protected:
	std::map<double, std::vector<double>> toMap(std::string resultJson);
};

class MorletWaveletPythonService : public PythonWaveletExecuter
{
public:
	MorletWaveletPythonService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) : 
		PythonWaveletExecuter(stringService, tempFileNameService, fileSerivce) {};

protected:
	virtual std::string getScriptName()
	{
		return "morletWavelet.py";
	}
};

class HaarWaveletPythonService : public PythonWaveletExecuter
{
public:
	HaarWaveletPythonService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonWaveletExecuter(stringService, tempFileNameService, fileSerivce) {};

protected:
	virtual std::string getScriptName()
	{
		return "haarWavelet.py";
	}
};

class Db2WaveletPythonService : public PythonWaveletExecuter
{
public:
	Db2WaveletPythonService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonWaveletExecuter(stringService, tempFileNameService, fileSerivce) {};

protected:
	virtual std::string getScriptName()
	{
		return "db2Wavelet.py";
	}
};

class Db4WaveletPythonService : public PythonWaveletExecuter
{
public:
	Db4WaveletPythonService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonWaveletExecuter(stringService, tempFileNameService, fileSerivce) {};

protected:
	virtual std::string getScriptName()
	{
		return "db4Wavelet.py";
	}
};

class FastFourierDescriptorService : public PythonExecuter
{
public:
	FastFourierDescriptorService(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonExecuter(stringService, tempFileNameService, fileSerivce) {};

	std::vector<std::complex<double>> calculate(std::vector<std::complex<double>> contour);

protected:
	virtual std::string getScriptName()
	{
		return "fft.py";
	}

	std::vector<std::complex<double>> toList(std::string json);

};

class Yolov10Service : public PythonExecuter
{
public:
	Yolov10Service(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce) :
		PythonExecuter(stringService, tempFileNameService, fileSerivce) {};

	std::vector<double> calculate(std::string imagePath)
	{
		std::vector<char> symbols;
		symbols.push_back('[');
		symbols.push_back(']');

		std::string scriptName = this->getScriptName();
		std::string comand = "python " + this->directoryPath + scriptName + " " + imagePath.c_str();

		std::string consoleResult = this->exec(comand.c_str());
		std::vector<std::string> parts = this->stringService->split(consoleResult, '\n');
		std::string lastPart = parts[0];

		std::vector<double> values;
		std::vector<std::string> strValues = this->stringService->split(lastPart, ',');

		for (std::string strValue : strValues)
		{
			this->stringService->trim(strValue, symbols);

			if (strValue.length() > 0)
			{
				double value = this->stringService->toDouble(strValue);
				values.push_back(value);
			}
		}

		return values;
	}

protected:
	virtual std::string getScriptName()
	{
		return "runYolo.py";
	}

};

#endif