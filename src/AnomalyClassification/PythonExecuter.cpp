#include "PythonExecuter.h"

PythonExecuter::PythonExecuter(StringSerivce* stringService, TempFileNameService* tempFileNameService, FileService* fileSerivce)
{
    this->stringService = stringService;
    this->tempFileNameService = tempFileNameService;
    this->fileSerivce = fileSerivce;

    std::filesystem::path cwd = std::filesystem::current_path();
    this->directoryPath = cwd.string() + "/../python/";
}

std::map<double, std::vector<double>> PythonExecuter::calculate(std::vector<std::complex<double>> input)
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

std::map<double, std::vector<double>> PythonExecuter::toMap(std::string resultJson)
{
    std::vector<std::string> lines = this->stringService->split(resultJson, ']');

    std::map<double, std::vector<double>> map;
    double key = 0;

    for (int i = lines.size()-1; i >= 0 ;i--)
    {
        std::string line = lines[i];

        std::vector<double> vector;
        std::vector<std::string> unsureValues = this->stringService->split(line, ',');

        for (std::string unsureValue : unsureValues)
        {
            this->stringService->trim(unsureValue);

            if (unsureValue.size() < 1)
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

    this->stringService->trim(parameter);

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