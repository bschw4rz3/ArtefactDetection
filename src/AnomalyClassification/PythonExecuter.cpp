#include "PythonExecuter.h"

PythonExecuter::PythonExecuter(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce)
{
    this->stringService = stringService;
    this->tempFileNameService = tempFileNameService;
    this->fileSerivce = fileSerivce;

    std::filesystem::path cwd = std::filesystem::current_path();
    this->directoryPath = cwd.string() + "/../python/";
}

std::map<double, std::vector<double>> PythonWaveletExecuter::calculate(std::vector<std::complex<double>> input)
{
    std::string inputJson = this->tempFileNameService->generateFileNameJson();
    std::string outputJson = this->tempFileNameService->generateFileNameJson();

    std::string parameter = this->getParameter(input);
    this->fileSerivce->saveFile(parameter, inputJson);

    std::string scriptName = this->getScriptName();
    std::string comand = "python " + this->directoryPath + scriptName + " " + inputJson + " " + outputJson;
    //std::string comand = "dir";

    std::string consoleResult = this->exec(comand.c_str());
    std::string resultJson = this->fileSerivce->readFile(outputJson);

    std::remove(inputJson.c_str());
    std::remove(outputJson.c_str());

    return this->toMap(resultJson);
}

std::map<double, std::vector<double>> PythonWaveletExecuter::toMap(std::string resultJson)
{
    std::vector<char> symbols = { '[', ']' };
    std::vector<std::string> lines = this->stringService->split(resultJson, ']');

    std::map<double, std::vector<double>> map;
    double key = 0;

    for (int i = lines.size()-1; i >= 0 ;i--)
    {
        std::string line = lines[i];

        std::vector<double> vector;
        std::vector<std::string> unsureValues = this->stringService->split(line, ',');

        if (unsureValues.size() > 0)
        {
            this->stringService->trim(unsureValues[0], symbols);

            if (unsureValues.size() > 1)
            {
                this->stringService->trim(unsureValues[1], symbols);
            }

            this->stringService->trim(unsureValues[unsureValues.size() - 1], symbols);
        }

        for (std::string unsureValue : unsureValues)
        {
            if (unsureValue.size() < 2)
            {
                continue;
            }

            double value = this->stringService->toDouble(unsureValue);
            vector.push_back(value);
        }

        if (vector.size() > 0)
        {
            map.insert(std::pair<double, std::vector<double>>(key, vector));
            key++;
        }
    }

    return map;
}

std::string PythonExecuter::getParameter(std::vector<std::complex<double>> input)
{
    std::string parameter = "";
    
    for (std::complex<double> value : input)
    {
        std::string pythonValue = this->stringService->complexToPythonValue(value);
        parameter += pythonValue + "\n";
    }

    std::vector<char> symbol = { '\n' };
    this->stringService->rtrim(parameter, symbol);

    return parameter;
}

std::string PythonExecuter::exec(std::string cmd)
{
    std::string result = "";
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (pipe) 
    {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) 
        {
            result += buffer;
        }
        _pclose(pipe);
    }

    return result;
}

std::vector<std::complex<double>> FastFourierDescriptorService::calculate(std::vector<std::complex<double>> input)
{
    std::string inputJson = this->tempFileNameService->generateFileNameJson();
    std::string outputJson = this->tempFileNameService->generateFileNameJson();

    std::string parameter = this->getParameter(input);
    this->fileSerivce->saveFile(parameter, inputJson);

    std::string scriptName = this->getScriptName();
    std::string comand = "python " + this->directoryPath + scriptName + " " + inputJson + " " + outputJson;
    //std::string comand = "dir";

    std::string consoleResult = this->exec(comand.c_str());
    std::string resultJson = this->fileSerivce->readFile(outputJson);

    std::remove(inputJson.c_str());
    std::remove(outputJson.c_str());

    return this->toList(resultJson);
}

std::vector<std::complex<double>> FastFourierDescriptorService::toList(std::string resultJson)
{
    std::vector<char> symbols = { '(', ')', '"' };

    std::vector<std::string> lines = this->stringService->split(resultJson, ']');
    std::vector<std::complex<double>> list;
    double key = 0;

    for (int i = lines.size() - 1; i >= 0; i--)
    {
        std::string line = lines[i];

        std::vector<double> vector;
        std::vector<std::string> unsureValues = this->stringService->split(line, ',');

        for (std::string unsureValue : unsureValues)
        {
            std::vector<std::string> valueParts = this->stringService->split(unsureValue, '|');

            if (valueParts.size() != 2)
            {
                continue;
            }

            this->stringService->trim(valueParts[0], symbols);
            this->stringService->trim(valueParts[1], symbols);

            double realPart = this->stringService->toDouble(valueParts[0]);
            double imagPart = this->stringService->toDouble(valueParts[1]);

            list.push_back(std::complex<double>(realPart, imagPart));
        }
    }

    return list;
}