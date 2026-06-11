#include "MyEventReceiver.h"

MyEventReceiver::MyEventReceiver(GraphicEngineExtended* graphicEngine, DependencyInjectionService* di)
{
    this->graphicEngine = graphicEngine;
    this->superPixelService = di->superPixelService;
    this->sobelOperatorSerivce = di->classicSobelOperatorService;
    this->improvedSobelOperatorService = di->improvedSobelOperatorService;
    this->geometricService = di->geometricService;
    this->histogramValueService = di->histogramValueService;
    this->discreteFourierTransformationSerivce = di->discreteFourierTransformationSerivce;
    this->huMomentsService = di->huMomentsService;
    this->sdSfService = di->sdSfService;
    this->lbpService = di->lbpService;
    this->completedLbpService = di->completedLbpService;
    this->glcmService = di->glcmService;
    this->hogService = di->hogService;
    this->gaborServiceCV = di->gaborServiceCV;
    this->waveletTransformCV = di->waveletTransformCV;
    this->discreteFourierTransformationSerivceCV = di->discreteFourierTransformationSerivceCV;
    this->discreteFourierDescriptorService = di->discreteFourierDescriptorService;
    this->daubechiesFourWaveletService = di->daubechiesFourWaveletService;
    this->morletWaveletService = di->morletWaveletService;
    this->morletWaveletServiceFFT = di->morletWaveletServiceFFT;
    this->haarWaeletService = di->haarWavletService;
    this->daubechiesSecondWaveletService = di->daubechiesSecondWaveletService;
    this->biorWavlet = di->biorWavletService;
    this->yolov10Service = di->yolov10Service;

    this->defectGenerationService = di->defectGenerationService;

    this->stringSerivce = di->stringSerivce;
    this->directoryService = di->directoryService;
    this->mathSerivce = di->mathSerivce;
    this->colorService = di->colorService;
    this->cImgService = di->imgService;
    this->fileService = di->fileService;
    this->tempFileNameService = di->tempFileNameService;

    this->kNearestNeighborsService = di->kNearestNeighborsService;
    this->decisionTreeService = di->decisionTreeService;
    this->svmService = di->svmService;
    this->kmeansService = di->kmeansService;

    this->imageFixService = di->imageFixService;

    this->facet = NULL;
    this->context = NULL;

    this->isRunning = false;
    this->isAbbord = false;

    this->progressSymbol = '-';
    this->selectedFile = L"";
    this->tempFileIndex = 0;

    //std::string dataRepro = "classicTrainingsdata";
    //std::string dataRepro = "generatedTrainingsdata";
    std::string dataRepro = "modifiedTrainingsdata";

    std::filesystem::path cwd = std::filesystem::current_path();
    this->trainingsdata = cwd.string() + "/../../data/"+ dataRepro +"/trainingsdata";
    this->trainingsDataSavePath = cwd.string() + "/../../data/"+dataRepro+"/trainingsDataSave";
    this->testdataPath = cwd.string() + "/../../data/"+ dataRepro +"/testdata";
    this->testdataSavePath = cwd.string() + "/../../data/"+ dataRepro +"/testdataSave";

    this->fixedTrainingsdata = cwd.string() + "/../../data/" + dataRepro + "/fixedTrainingsdata";
    this->fixedTestdataPath = cwd.string() + "/../../data/" + dataRepro + "/fixedTestdata";

    mkdir(this->fixedTrainingsdata.c_str());
    mkdir(this->fixedTestdataPath.c_str());
}

MyEventReceiver::~MyEventReceiver()
{
    this->isAbbord = true;

    if (this->isRunning)
    {
        //this->onJoinTask();
    }

    this->tempFileNameService->removeTempFiles();
}

void MyEventReceiver::OnInit(SAppContext* context)
{
    this->context = context;
}

bool MyEventReceiver::setForm(s32 id)
{
    switch (id) {
    case 1:
        break;
    default:
        return false;
    }
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();

        IGUIEnvironment* env = this->context->device->getGUIEnvironment();

        switch (event.GUIEvent.EventType)
        {
        case EGET_SCROLL_BAR_CHANGED:

            break;
        case EGET_BUTTON_CLICKED:

            if (id == GUI_ID_BUTTON_CACLULATE)
            {
                if (this->selectedFile != L"")
                {
                    std::string fileName = this->stringSerivce->toString(this->selectedFile);
                    CImg<unsigned char> img(fileName.c_str());

                    this->onExecuteFeatureExtraction(fileName, &img, false);
                }
                else
                {
                    this->showMessage(L"No file selected!");
                }
            }
            else if (id == GUI_ID_BUTTON_CHOOSE_FILE)
            {
                this->onResetImages();
                this->graphicEngine->addFileOpenDialog(GUI_ID_DIALOG_CHOOSE_FILE, this->stringSerivce->toWString(this->testdataPath));
            }
            else if(id == GUI_ID_BUTTON_GENERATE_TRAININGS_DATA)
            {
                this->onGenerateTrainingsData();
            }
            else if(id == GUI_ID_BUTTON_CLASSIFY)
            {
                int classifyId = this->graphicEngine->getCheckedCheckBoxByWindowId(GUI_ID_CLASSIFY_PANNEL);
                int methodeId = this->graphicEngine->getCheckedCheckBoxByWindowId(GUI_ID_OPERATION_PANNEL);

                if (this->selectedFile == L"")
                {
                    this->showMessage(L"No file selected!");
                }
                else if (classifyId != -1 && methodeId != -1)
                {
                    if (classifyId == GUI_ID_CHECKBOX_CLASSIFY_DEFAULT)
                    {
                        std::vector<std::vector<double>> result = this->calculateFeatureVector(this->stringSerivce->toString(this->selectedFile), false);

                        if (result.size() == 0)
                        {
                            this->showMessage(L"Methode kann nicht angewendet werden.");
                            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Error!");
                        }
                    }
                    else if (classifyId == GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR)
                    {
                        std::string result = this->onClassifyKNearest(this->stringSerivce->toString(this->selectedFile), false);

                        if (result == "error")
                        {
                            this->showMessage(L"Methode kann nicht angewendet werden.");
                            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Error!");
                        }
                    }
                    else if (classifyId == GUI_ID_CHECKBOX_CLASSIFY_K_MEANS)
                    {
                        std::string result = this->onClassifyKMeans(this->stringSerivce->toString(this->selectedFile), false);

                        if (result == "error")
                        {
                            this->showMessage(L"Methode kann nicht angewendet werden.");
                            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Error!");
                        }
                    }
                    else if (classifyId == GUI_ID_CHECKBOX_CLASSIFY_DECISION_TREE)
                    {
                        std::string result = this->onClassifyDecisionTree(this->stringSerivce->toString(this->selectedFile), false);

                        if (result == "error")
                        {
                            this->showMessage(L"Methode kann nicht angewendet werden.");
                            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Error!");
                        }
                    }
                    else if (classifyId == GUI_ID_CHECKBOX_CLASSIFY_SUPPORT_VECTOR_MACHINE)
                    {
                        std::string result = this->onClassifySVM(this->stringSerivce->toString(this->selectedFile), false);

                        if (result == "error")
                        {
                            this->showMessage(L"Methode kann nicht angewendet werden.");
                            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Error!");
                        }
                    }
                    else
                    {
                        this->showMessage(L"No implemented!");
                    }
                }
                else
                {
                    this->showMessage(L"No classifier or feature method selected!");
                }
            }
            else if (id == GUI_ID_BUTTON_CLASSIFY_MULTIPLE)
            {
                auto start_time = std::chrono::high_resolution_clock::now();

                this->onClassifyMultiple();

                auto end_time = std::chrono::high_resolution_clock::now();
                auto time = end_time - start_time;
                long measuredTime = time / std::chrono::milliseconds(1);

                std::wstring measuredTimeAsString = this->stringSerivce->intToWString(measuredTime) + L" ms";
                this->graphicEngine->setGUIElementText(GUI_ID_LABEL_TIME_NEEDED, measuredTimeAsString.c_str());
            }
            else if(id == GUI_ID_BUTTON_MESSAGE_OK)
            {
                this->graphicEngine->setVisibility(GUI_ID_MESSAGE_PANNEL, false);

                this->graphicEngine->enableGUIElement(GUI_ID_OPERATION_PANNEL, true);
                this->graphicEngine->enableGUIElement(GUI_ID_GRAYINFO_PANNEL, true);
                this->graphicEngine->enableGUIElement(GUI_ID_GEOMETRICINFO_PANNEL, true);
                this->graphicEngine->enableGUIElement(GUI_ID_HU_MOMENT_PANNEL, true);
                this->graphicEngine->enableGUIElement(GUI_ID_HU_GLCM_PANNEL, true);
                this->graphicEngine->enableGUIElement(GUI_ID_CLASSIFY_PANNEL, true);

                if (this->graphicEngine->exists(GUI_ID_IMAGE_PANNEL))
                {
                    this->graphicEngine->enableGUIElement(GUI_ID_IMAGE_PANNEL, true);
                }
            }
            else if (id == GUI_ID_BUTTON_GENERATE_YOLO_TRAININGSDATA)
            {
                for (int i = 0; i < 1000; i++)
                {
                    this->defectGenerationService->generateAnomalieDirectories(this->trainingsdata+"/yoloTestdaten", 1, 1, 600);
                }
            }

            return true;
        case EGET_FILE_SELECTED:
        {
            IGUIFileOpenDialog* dialog =
                (IGUIFileOpenDialog*)event.GUIEvent.Caller;

            this->onSelectFile(core::stringc(dialog->getFileName()).c_str());
            return true;
        }
        case EGET_CHECKBOX_CHANGED:

            if(id == GUI_ID_CHECKBOX_CLASSIFY_DECISION_TREE || id == GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR || id == GUI_ID_CHECKBOX_CLASSIFY_K_MEANS || id == GUI_ID_CHECKBOX_CLASSIFY_SUPPORT_VECTOR_MACHINE || id == GUI_ID_CHECKBOX_CLASSIFY_DEFAULT)
            {
                this->graphicEngine->resetCheckBoxsByWindowId(GUI_ID_CLASSIFY_PANNEL);

                this->graphicEngine->setVisibility(GUI_ID_LABEL_PARAMETER, false);
                this->graphicEngine->setVisibility(GUI_ID_INPUTBOX_PARAMETER, false);

                if(id == GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR)
                {
                    this->graphicEngine->setGUIElementText(GUI_ID_LABEL_PARAMETER, L"Parameter K:");
                    this->graphicEngine->setGUIElementText(GUI_ID_INPUTBOX_PARAMETER, L"2");

                    this->graphicEngine->setVisibility(GUI_ID_LABEL_PARAMETER, true);
                    this->graphicEngine->setVisibility(GUI_ID_INPUTBOX_PARAMETER, true);
                }
            }
            else
            {
                this->graphicEngine->resetCheckBoxsByWindowId(GUI_ID_OPERATION_PANNEL);
            }

            this->graphicEngine->setGUIElementChecked(id, true);

            return true;

        default:
            return this->setForm(id);
        }
    }

    return false;
}

FeatureResult MyEventReceiver::onExecuteFeatureExtraction(std::string fileName, CImg<unsigned char>* img, bool silence)
{    
    FeatureResult result = FeatureResult(NAN);

    if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SUPERPIXELS))
    {
        this->onCalculateSuperPixels(img);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SOBEL))
    {
        this->onCalculateSobelOperator(img);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_IMPROVED_SOBEL))
    {
        this->onCalculateImprovedSobelOperator(img);
    }
    else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION))
    {
        result = this->onDiscreteFourierTransformation(img, silence);
    }
    else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HU_MOMENT))
    {
        result = this->onHuMoment(fileName, img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SDSF))
    {
        result = this->onSdSf(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_LBP))
    {
        result = this->onLbp(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_COMPLETED_LBP))
    {
        result = this->onCompletedLbp(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GLCM))
    {
        result = this->onGLCM(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HOG))
    {
        result = this->onHOG(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GABOR))
    {
        result = this->onGaborFilter(fileName, silence);
    }
#ifndef _USE_PYTHON_SCRIPTS
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_WAVELET))
    {
        result = this->onWavelet(fileName, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_MORLET_WAVELET))
    {
        result = this->onMorletFourWavelet(img, silence);
    }
#endif
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION_CV))
    {
        result = this->onDiscreteFourierTransformationCV(fileName, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_FOURIER_DISCRIPTOR))
    {
        result = this->onFourierDiscriptor(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DAUBECHIES_FOUR_WAVELET))
    {
        result = this->onDaubechiesFourWavelet(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_MORLET_WAVELET_FFT))
    {
        result = this->onMorletFourWaveletFFT(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HAAR_WAVLET))
    {
        result = this->onHaarWavelet(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DAUBECHIES_SECOND))
    {
        result = this->onDaubechiesSecond(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_BIOR_WAVLET))
    {
        result = this->onBiorWavlet(img, silence);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GEOMETRIC_MEASURES))
    {
        result = this->onGeometricValues(img, fileName);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GRAYSCALE_BASED_METHODS))
    {
        result = this->onGrayscaleBasedValues(img);
    }
    else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_YOLO_10))
    {
        result = this->onYolo10(img, silence);
    }    

    // Clean up
    if(!silence)
    {
        this->tempFileNameService->removeTempFiles();
    }

    return result;
}

void MyEventReceiver::onGenerateTrainingsData()
{
    rmdir(this->trainingsdata.c_str());
    this->defectGenerationService->generateAnomalieDirectories(this->trainingsdata, 10);
}

std::string MyEventReceiver::generateTestDataPath(std::string imagePath)
{
    std::vector<std::string> imagePathParts = this->stringSerivce->split(imagePath, '/');
    imagePathParts = this->stringSerivce->split(imagePathParts[imagePathParts.size()-1], '\\');
    imagePathParts = this->stringSerivce->split(imagePathParts[imagePathParts.size() - 1], '.');

    if (imagePathParts.size() <= 1)
    {
        return "";
    }
    
    std::string imageName = imagePathParts[imagePathParts.size() - 2];
    int methodeId = this->graphicEngine->getCheckedCheckBoxByWindowId(GUI_ID_OPERATION_PANNEL);

    return this->testdataSavePath + "/" + this->stringSerivce->intToString(methodeId) + "_" + imageName + ".xml";
}

std::string MyEventReceiver::generateTrainingsDataFilePath()
{
    int classifyId = this->graphicEngine->getCheckedCheckBoxByWindowId(GUI_ID_CLASSIFY_PANNEL);
    int methodeId = this->graphicEngine->getCheckedCheckBoxByWindowId(GUI_ID_OPERATION_PANNEL);

    return this->trainingsDataSavePath + "/" + this->stringSerivce->intToString(classifyId) + "_" + this->stringSerivce->intToString(methodeId) + ".xml";
}

void MyEventReceiver::saveTrainingsData(std::vector<DataPoint> trainingData, std::string fileName)
{
    DataFile dataFile;
    dataFile.addDataPoint(trainingData);

    std::string xml = dataFile.toXML();

    this->fileService->saveFile(xml, fileName);
}

void MyEventReceiver::onClassifyMultiple()
{
    int maximalThreadCount = 4;
    double totalCounter = 0;
    double successCounter = 0;

    bool isClassMethodDefault = this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_CLASSIFY_DEFAULT);
    int isClassMethodKNN = this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR);
    int isClassMethodKMeans = this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_CLASSIFY_K_MEANS);
    int isClassMethodDT = this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_CLASSIFY_DECISION_TREE);
    int isClassMethodSVM = this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_CLASSIFY_SUPPORT_VECTOR_MACHINE);

    this->graphicEngine->setGUIElementChecked(GUI_ID_CHECKBOX_GENERATE_NEW_TRAININGSDATA, false);
    this->graphicEngine->clearTable(GUI_ID_BUTTON_CLASSIFY_TABLE);

    std::vector<std::string> classNames;
    classNames.push_back("defect");
    classNames.push_back("artefact");

    std::vector<std::string> filePaths;

    for(int i = 0;i< classNames.size();i++)
        filePaths.push_back(this->testdataPath + "/" + classNames[i]);

    std::string csvResultTable = "Image;Expected;Result;Score\n";
    std::vector<std::vector<std::wstring>> resultTable;

    std::string featureCsv = "";

    for (int classIndex = 0; classIndex < 2; classIndex++)
    {
        std::vector<std::string> fileNames = this->directoryService->getFileNames(filePaths[classIndex]);
        int fileSize = fileNames.size();

        for (int i = 0; i < fileSize; )
        {
            std::vector<std::future<std::string>> threadVector;

            int threadCount = min(maximalThreadCount, fileSize - i);
            for (int t = 0 ; t < threadCount; t++)
            {
                if (isClassMethodDefault)
                {
                    threadVector.push_back(std::async(std::launch::async, [t = this, fileName = fileNames[i]]() { return t->onClassifyDefault(fileName, true); }));
                }
                else if (isClassMethodKMeans)
                {
                    threadVector.push_back(std::async(std::launch::async, [t = this, fileName = fileNames[i]]() { return t->onClassifyKMeans(fileName, true); }));
                }
                else if (isClassMethodDT)
                {
                    threadVector.push_back(std::async(std::launch::async, [t = this, fileName = fileNames[i]]() { return t->onClassifyDecisionTree(fileName, true); }));
                }
                else if(isClassMethodKNN)
                {
                    threadVector.push_back(std::async(std::launch::async, [t = this, fileName = fileNames[i]]() { return t->onClassifyKNearest(fileName, true); }));
                }
                else if (isClassMethodSVM)
                {
                    threadVector.push_back(std::async(std::launch::async, [t = this, fileName = fileNames[i]]() { return t->onClassifySVM(fileName, true); }));
                }
                
                i++;
            }

            for (int t = 0; t < threadCount; t++)
            {
                std::string classString = "error";

                try
                {
                    classString = threadVector[t].get();
                }
                catch (exception e)
                {
                    int bla = 0;
                }

                std::vector<std::string> fileNameParts = this->stringSerivce->split(fileNames[i-(threadCount - t)], '\\');
                bool hasCorrectClass = this->stringSerivce->contains(classString, classNames[classIndex]);

                std::wstring fileName = this->stringSerivce->toWString(fileNameParts[fileNameParts.size() - 1]);
                std::wstring expected = this->stringSerivce->toWString(classNames[classIndex]);
                std::wstring wrongClass = this->stringSerivce->toWString(classNames[abs(classIndex - 1)]);
                std::wstring classified = this->stringSerivce->toWString(classString);
                std::wstring percentStr = hasCorrectClass ? L"100%" : L"  0%";

                if (hasCorrectClass)
                {
                    successCounter++;
                }

                resultTable.push_back(std::vector<std::wstring> { fileName, expected, classified, percentStr});

                csvResultTable += this->stringSerivce->toString(fileName) + ";" + 
                                  this->stringSerivce->toString(expected) + ";" + 
                                  this->stringSerivce->toString(classified) + ";" + 
                                  this->stringSerivce->toString(percentStr) + "\n";

                totalCounter++;

                std::vector<std::vector<double>> testData = this->calculateFeatureVector(fileNames[i - (threadCount - t)], true);

                if (testData.size() == 1)
                {
                    featureCsv += this->stringSerivce->intToString(classIndex) + ";";

                    for (int j = 0; j < testData[0].size(); j++)
                    {
                        double featureValue = testData[0][j];
                        featureCsv += this->stringSerivce->doubleToString(featureValue) + ";";
                    }

                    this->stringSerivce->trim(featureCsv, std::vector<char> {';'});
                    featureCsv += "\n";
                }
            }
        }
    }

    this->fileService->saveFile(csvResultTable, "results.csv");

    for (int i = 0; i < resultTable.size(); i++)
    {
        this->graphicEngine->addRow(GUI_ID_BUTTON_CLASSIFY_TABLE, resultTable[i]);
    }

    std::wstring percentStr = this->stringSerivce->doubleToWString(this->mathSerivce->roundDigits(100 / totalCounter * successCounter, 2));
    this->graphicEngine->addRow(GUI_ID_BUTTON_CLASSIFY_TABLE, std::vector<std::wstring> { L"Sum", L"", L"", percentStr+L"%"});

    std::vector<DataPoint> trainingData = this->loadTrainingsData(true);
    
    for (int i = 0; i < trainingData.size(); i++)
    {
        featureCsv += this->stringSerivce->intToString(trainingData[i].label) + ";";

        for (int j = 0; j < trainingData[i].features.size(); j++)
        {
            double featureValue = trainingData[i].features[j];
            featureCsv += this->stringSerivce->doubleToString(featureValue) + ";";
        }
        
        this->stringSerivce->trim(featureCsv, std::vector<char> {';'});
        featureCsv += "\n";
    }

    this->fileService->saveFile(featureCsv, "feature.csv");
}

std::vector<DataPoint> MyEventReceiver::loadTrainingsData(bool batchMod)
{
    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Initiate...");
    }

    mkdir(this->trainingsDataSavePath.c_str());
    std::string traningsDataFile = this->generateTrainingsDataFilePath();

    std::vector<DataPoint> trainingData;

    this->criticalLoadTraingsData.acquire();

    if (this->fileService->exists(traningsDataFile) && !this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GENERATE_NEW_TRAININGSDATA))
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Load Traingsdata...");
        }

        std::string xmlContent = this->fileService->readFile(traningsDataFile);

        DataFile dataFile;
        dataFile.fromXML(xmlContent.c_str(), &dataFile);

        trainingData = dataFile.toDataPoints();
    }
    else
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Generate Traingsdata...");
        }

        trainingData = this->loadTraingsdataForKNearest();
        this->saveTrainingsData(trainingData, traningsDataFile);
    }

    this->criticalLoadTraingsData.release();

    return trainingData;
}

std::vector<std::vector<double>> MyEventReceiver::calculateFeatureVector(std::string selectedImage, bool batchMod)
{
    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"Execute test...");
    }

    std::vector<std::vector<double>> testData;
    mkdir(this->testdataSavePath.c_str());

    std::string testDataPath = this->generateTestDataPath(selectedImage);

    this->criticalLoadTestData.acquire();

    if (this->fileService->exists(testDataPath.c_str()) && !this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GENERATE_NEW_TRAININGSDATA))
    {
        std::string xmlContent = this->fileService->readFile(testDataPath);

        DataFile dataFile;
        dataFile.fromXML(xmlContent.c_str(), &dataFile);

        std::vector<DataPoint> dataPoints = dataFile.toDataPoints();
        testData.push_back(dataPoints[0].features);
    }
    else
    {
        CImg<unsigned char> img(selectedImage.c_str());

        if (img.height() != 600 || img.height() != 600)
        {
            std::string fileName = this->saveFixedImage(selectedImage);
            img = CImg<unsigned char>(fileName.c_str());
        }

        FeatureResult featureResult = this->onExecuteFeatureExtraction(selectedImage, &img, true);

        if (!featureResult.getSuccess())
        {
            this->criticalLoadTestData.release();
            return std::vector<std::vector<double>>();
        }

        testData.push_back(featureResult.getFeatureVector());

        DataPoint dataPoint = this->toDataPoint(featureResult);
        this->saveTrainingsData(std::vector<DataPoint> { dataPoint }, testDataPath);
    }

    this->criticalLoadTestData.release();

    return testData;
}

std::string MyEventReceiver::saveFixedImage(std::string selectedImage)
{
    CImg<unsigned char> img(selectedImage.c_str());

    std::string fixedFilePath = "";
    std::string fileName = this->tempFileNameService->getFileName(selectedImage);

    if (this->stringSerivce->contains(selectedImage, "test"))
    {
        fixedFilePath = this->fixedTestdataPath + "/" + fileName;
    }
    else
    {
        fixedFilePath = this->fixedTrainingsdata + "/" + fileName;
    }

    if (!this->fileService->exists(fixedFilePath))
    {
        this->imageFixService->fixImage(&img, fixedFilePath);
    }

    return fixedFilePath;
}

std::string MyEventReceiver::onClassifyDefault(std::string selectedImage, bool batchMod)
{
    std::vector<std::vector<double>> testData = this->calculateFeatureVector(selectedImage, batchMod);

    if (testData.size() == 0)
    {
        return "error";
    }

    double avgSum = 0;

    for (int i = 0; i < testData.size(); i++)
    {
        double avg = 0;

        for (int j = 0; j < testData[i].size(); j++)
        {
            avg += testData[i][j];
        }

        avg /= (double)testData[i].size();
        avgSum += avg;
    }

    avgSum /= (double)testData.size();

    std::string classifyIndex = this->stringSerivce->intToString(avgSum);

    if (avgSum == 0)
    {
        classifyIndex = "defect";
    }
    else if(avgSum == 1)
    {
        classifyIndex = "artefact";
    }
    else
    {
        classifyIndex = "error";
    }

    return classifyIndex;
}

std::string MyEventReceiver::onClassifyDecisionTree(std::string selectedImage, bool batchMod)
{
    std::vector<DataPoint> trainingData = this->loadTrainingsData(batchMod);
    std::vector<std::vector<double>> testData = this->calculateFeatureVector(selectedImage, batchMod);

    if (testData.size() == 0)
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"error");
        }

        return "error";
    }

    std::vector<DataPoint> classifiedDatPoints = this->decisionTreeService->classify(trainingData, testData);
    int classIndex = classifiedDatPoints[0].label;

    std::string classifyIndex = this->stringSerivce->intToString(classIndex);

    if (classIndex == 0)
    {
        classifyIndex = "defect";
    }
    else
    {
        classifyIndex = "artefact";
    }

    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, this->stringSerivce->toWString(classifyIndex).c_str());
    }

    return classifyIndex;
}

std::string MyEventReceiver::onClassifySVM(std::string selectedImage, bool batchMod)
{
    std::vector<DataPoint> trainingData = this->loadTrainingsData(batchMod);
    std::vector<std::vector<double>> testData = this->calculateFeatureVector(selectedImage, batchMod);

    if (testData.size() == 0)
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"error");
        }

        return "error";
    }

    std::vector<DataPoint> classifiedDatPoints = this->svmService->classify(trainingData, testData);
    int classIndex = classifiedDatPoints[0].label;

    std::string classifyIndex = this->stringSerivce->intToString(classIndex);

    if (classIndex == 0)
    {
        classifyIndex = "defect";
    }
    else
    {
        classifyIndex = "artefact";
    }

    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, this->stringSerivce->toWString(classifyIndex).c_str());
    }

    return classifyIndex;
}

std::string MyEventReceiver::onClassifyKMeans(std::string selectedImage, bool batchMod)
{
    std::vector<DataPoint> trainingData = this->loadTrainingsData(batchMod);
    std::vector<std::vector<double>> testData = this->calculateFeatureVector(selectedImage, batchMod);

    if (testData.size() == 0)
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"error");
        }

        return "error";
    }

    std::vector<DataPoint> classifiedDatPoints = this->kmeansService->classify(trainingData, testData);
    int classIndex = classifiedDatPoints[0].label;

    std::string classifyIndex = this->stringSerivce->intToString(classIndex);

    if (classIndex == 0)
    {
        classifyIndex = "defect";
    }
    else
    {
        classifyIndex = "artefact";
    }

    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, this->stringSerivce->toWString(classifyIndex).c_str());
    }

    return classifyIndex;
}

std::string MyEventReceiver::onClassifyKNearest(std::string selectedImage, bool batchMod)
{
    std::vector<DataPoint> trainingData = this->loadTrainingsData(batchMod);
    std::vector<std::vector<double>> testData = this->calculateFeatureVector(selectedImage, batchMod);

    if (testData.size() == 0)
    {
        if (!batchMod)
        {
            this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, L"error");
        }

        return "error";
    }

    std::wstring parameterK = this->graphicEngine->getGUIElementText(GUI_ID_INPUTBOX_PARAMETER);
    int numberK = this->stringSerivce->toInt(parameterK);

    std::vector<DataPoint> classifiedDatPoints = this->kNearestNeighborsService->classify(trainingData, testData, numberK);
    int classIndex = classifiedDatPoints[0].label;

    std::string classifyIndex = this->stringSerivce->intToString(classIndex);

    if(classIndex == 0)
    {
        classifyIndex = "defect"; 
    }
    else 
    {
        classifyIndex = "artefact";
    }

    if (!batchMod)
    {
        this->graphicEngine->setGUIElementText(GUI_ID_LABEL_CLASSIFY_INDEX, this->stringSerivce->toWString(classifyIndex).c_str());
    }

    return classifyIndex;
}

DataPoint MyEventReceiver::toDataPoint(FeatureResult featureResult)
{
    if (featureResult.getSuccess())
    {
        DataPoint dataPoint;
        dataPoint.features = featureResult.getFeatureVector();
        dataPoint.label = -1;

        return dataPoint;
    }

    throw "ERROR";
}

void MyEventReceiver::showMessage(std::wstring message)
{
    this->graphicEngine->setVisibility(GUI_ID_MESSAGE_PANNEL, true);
    this->graphicEngine->setGUIElementText(GUI_ID_LABEL_MESSAGE, message.c_str());

    this->graphicEngine->bringToFront(GUI_ID_OPERATION_PANNEL);
    this->graphicEngine->bringToFront(GUI_ID_GRAYINFO_PANNEL);
    this->graphicEngine->bringToFront(GUI_ID_GEOMETRICINFO_PANNEL);
    this->graphicEngine->bringToFront(GUI_ID_HU_MOMENT_PANNEL);
    this->graphicEngine->bringToFront(GUI_ID_HU_GLCM_PANNEL);
    this->graphicEngine->bringToFront(GUI_ID_CLASSIFY_PANNEL);

    this->graphicEngine->enableGUIElement(GUI_ID_OPERATION_PANNEL, false);
    this->graphicEngine->enableGUIElement(GUI_ID_GRAYINFO_PANNEL, false);
    this->graphicEngine->enableGUIElement(GUI_ID_GEOMETRICINFO_PANNEL, false);
    this->graphicEngine->enableGUIElement(GUI_ID_HU_MOMENT_PANNEL, false);
    this->graphicEngine->enableGUIElement(GUI_ID_HU_GLCM_PANNEL, false);
    this->graphicEngine->enableGUIElement(GUI_ID_CLASSIFY_PANNEL, false);

    if (this->graphicEngine->exists(GUI_ID_IMAGE_PANNEL))
    {
        this->graphicEngine->bringToFront(GUI_ID_IMAGE_PANNEL);
        this->graphicEngine->enableGUIElement(GUI_ID_IMAGE_PANNEL, true);
    }

    this->graphicEngine->bringToFront(GUI_ID_MESSAGE_PANNEL);
    this->graphicEngine->setFocus(GUI_ID_MESSAGE_PANNEL);
}

std::vector<DataPoint> MyEventReceiver::loadTraingsdataForKNearest()
{
    int maxThreads = 4;

    std::vector<DataPoint> dataPointList;

    std::vector<std::string> filePaths;
    filePaths.push_back(this->trainingsdata + "/defect");
    filePaths.push_back(this->trainingsdata + "/artefact");

    for(int classIndex = 0; classIndex < 2 ;classIndex++)
    {
        std::vector<std::string> fileNames = this->directoryService->getFileNames(filePaths[classIndex]);
        int fileSize = fileNames.size();

        for(int i = 0; i < fileSize;)
        {
            int restFileSize = fileSize - i;
            int threadCount = min(maxThreads, restFileSize);
            std::vector<std::future<FeatureResult>> threadVector;
            std::vector<CImg<unsigned char>*> images;

            this->startFeatureThreads(threadVector, fileNames, images, i, threadCount);
            this->endFeatureThreads(threadVector, images, i, threadCount, classIndex, dataPointList);
        }
    }

    return dataPointList;
}

void MyEventReceiver::startFeatureThreads(std::vector<std::future<FeatureResult>>& threadVector, std::vector<std::string> fileNames, std::vector<CImg<unsigned char>*>& images, int& currentIndex, int threadCount)
{
    for (int t = 0; t < threadCount; t++)
    {
        std::string tempName = this->saveFixedImage(fileNames[currentIndex].c_str());
        
        CImg<unsigned char>* result = new CImg<unsigned char>(tempName.c_str());
        images.push_back(result);

        threadVector.push_back(std::async(std::launch::async, [t = this, fileName = tempName, i = result]() { return t->onExecuteFeatureExtraction(fileName, i, true); }));

        currentIndex++;
    }
}

void MyEventReceiver::endFeatureThreads(std::vector<std::future<FeatureResult>>& threadVector, std::vector<CImg<unsigned char>*>& images, int& currentIndex, int threadCount, int currentClassIndex, std::vector<DataPoint>& dataPointList)
{
    for (int t = 0; t < threadCount; t++)
    {
        try
        {
            FeatureResult featureResult = threadVector[t].get();

            if (featureResult.getSuccess())
            {
                DataPoint dataPoint;
                dataPoint.features = featureResult.getFeatureVector();
                dataPoint.label = currentClassIndex;

                dataPointList.push_back(dataPoint);
            }
        }
        catch (exception e)
        {
            int bla = 0;
        }
    }

    for (int t = 0; t < threadCount; t++)
    {
        delete images[t];
    }

    images.clear();
}

FeatureResult MyEventReceiver::onBiorWavlet(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);

    std::map<double, std::vector<std::complex<double>>> result = this->biorWavlet->calculate(complexTime, 10);
    std::map<double, std::vector<double>> doubleResult = this->toDoubleMap(result);

    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->heatMap(TimeFrequenceResult(doubleResult, 30), std::vector<double>(), tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }
    
    auto featureResult = this->calculateFeatureVector(doubleResult);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[7], featureVector[8], featureVector[13]);
}

FeatureResult MyEventReceiver::onDaubechiesFourWavelet(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    
#ifdef _USE_PYTHON_SCRIPTS
    std::map<double, std::vector<double>> result = this->daubechiesFourWaveletService->calculate(complexTime);
#else    
    std::map<int, std::vector<std::complex<double>>> result = this->daubechiesFourWaveletService->calculate(complexTime);
#endif

    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
#ifdef _USE_PYTHON_SCRIPTS
        this->heatMap(TimeFrequenceResult(result, result.size()), std::vector<double>(), tempName);
#else
        this->heatMap(result, 10, std::vector<double>(), tempName);
#endif
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }   

#ifdef _USE_PYTHON_SCRIPTS

    auto featureResult = this->calculateFeatureVector(result);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[9], featureVector[10], featureVector[13]);
#else
    return this->calculateFeatureVector(this->toDoubleMap(result));
#endif
}

FeatureResult MyEventReceiver::onDaubechiesSecond(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);

#ifdef _USE_PYTHON_SCRIPTS
    std::map<double, std::vector<double>> resultDouble = this->daubechiesSecondWaveletService->calculate(complexTime);
#else
    std::map<int, std::vector<std::complex<double>>> result = this->daubechiesSecondWaveletService->calculate(complexTime);
    std::map<double, std::vector<double>> resultDouble = this->toDoubleMap(result);
#endif

    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
#ifdef _USE_PYTHON_SCRIPTS
        this->heatMap(TimeFrequenceResult(resultDouble, resultDouble.size()), std::vector<double>(), tempName);
#else
        this->heatMap(result, 10, std::vector<double>(), tempName);
#endif
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    auto featureResult = this->calculateFeatureVector(resultDouble);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[9], featureVector[10], featureVector[13]);
}

FeatureResult MyEventReceiver::onHaarWavelet(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<double, std::vector<double>> result = this->haarWaeletService->calculate(complexTime);
    
    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->heatMap(TimeFrequenceResult(result, 40), std::vector<double>(), tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    auto featureResult = this->calculateFeatureVector(result);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[8], featureVector[11], featureVector[13]);
}

FeatureResult MyEventReceiver::onMorletFourWaveletFFT(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<double, std::vector<double>> result = this->morletWaveletServiceFFT->calculate(complexTime);

    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->heatMap(TimeFrequenceResult(result, 40), std::vector<double>(), tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    auto featureResult = this->calculateFeatureVector(result);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[8], featureVector[11], featureVector[13]);
}

FeatureResult MyEventReceiver::onMorletFourWavelet(CImg<unsigned char>* img, bool silence)
{
    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    
    double maxFrequence = 30;
    double timeFactor = 1;

    WaveletResult result = this->morletWaveletService->calculate(complexTime, maxFrequence, timeFactor);

    if(!silence)
    {
        // Add Diagram
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.waveletOutput, tempName, std::vector<double>(), "Selected Wavelet:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 420), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->heatMap(result.frequenceTime, std::vector<double>(), tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.convolvedSignal, tempName, std::vector<double>(), "best Convolved Vector:");
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_1, Point2D(8, 520), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    return this->calculateFeatureVector(result.frequenceTime.frequenceTimeMap);
}

FeatureResult MyEventReceiver::onFourierDiscriptor(CImg<unsigned char>* img, bool silence)
{
    FDResult result = this->discreteFourierDescriptorService->calculate(img);

    if(!silence)
    {
        // Add Sobelimage
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        result.sobelImage.save_png(tempName.c_str());
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        // Add Diagram of conture
        tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.contourVector, tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 520), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        // Add Diagram
        tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.fequence, tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    if(!result.getSuccess())
    {
        return FeatureResult();
    }

    FeatureResult featureresult = this->calculateFeatureVector(this->toDoubleVector(result.fequence));
    std::vector<double> featureVector = featureresult.getFeatureVector();

    return FeatureResult(featureVector[2], featureVector[3], featureVector[5], featureVector[6]);
}

FeatureResult MyEventReceiver::onDiscreteFourierTransformationCV(std::string fileName, bool silence)
{
    DFTResult result = this->discreteFourierTransformationSerivceCV->calculate(fileName);

    if(!silence)
    {
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        cv::imwrite(tempName.c_str(), result.spectrumMagnitude*255);
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

        tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.radialProfile, tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    if(result.frequencies.size() <= 0)
    {
        return FeatureResult();
    }

    return this->calculateFeatureVector(result.frequencies);
}

FeatureResult MyEventReceiver::onWavelet(std::string fileName, bool silence)
{
    // Wavelet
    this->waveletTransformCV->calculate(fileName);

    return FeatureResult(NAN);
}

FeatureResult MyEventReceiver::onGaborFilter(std::string fileName, bool silence)
{
    // Gabor
    std::vector<double> fequence = this->gaborServiceCV->calculate(fileName);

    if(!silence)
    {
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(fequence, tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }
    
    auto featureResult = this->calculateFeatureVector(fequence);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[2], featureVector[6]);
}

FeatureResult MyEventReceiver::onHOG(CImg<unsigned char>* img, bool silence)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);
    std::vector<double> theVector = this->hogService->calculate(img);

    if(!silence)
    {
        std::string tempName = this->tempFileNameService->generateFileNamePng();
        this->diagram(theVector, tempName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    }


    if(theVector.size() <= 0)
    {
        return FeatureResult();
    }

    FeatureResult featureResult = this->calculateFeatureVector(theVector);
    std::vector<double> featureVector = featureResult.getFeatureVector();
    return FeatureResult(featureVector[2], featureVector[3], featureVector[5], featureVector[6]);
}

FeatureResult MyEventReceiver::onGLCM(CImg<unsigned char>* img, bool silence)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);

    // GLCM
    GLCMResult result = this->glcmService->calculate(img);

    // Generate FileName
    if(!silence)
    {
        std::string fileName = this->tempFileNameService->generateFileNamePng();
        result.getGlImage().save(fileName.c_str());
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    }

    wstring valueString = this->stringSerivce->doubleToWString(result.getEnergy());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_ENERGY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getContrast());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_CONTRAST, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getHomogenity());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_HOMOGENITY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getIDM());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_IDM, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getEntropy());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_ENTROPY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getMean());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_MEAN, valueString.c_str());

    //FeatureResult featureVector = FeatureResult(result.getEnergy(), result.getContrast(), result.getHomogenity(), result.getIDM(), result.getEntropy(), result.getMean());
    FeatureResult featureVector = FeatureResult(result.getHomogenity(), result.getEntropy(), result.getMean());

    if(featureVector.getFeatureVector().size() != 3)
    {
        return FeatureResult();
    }

    return featureVector;
}

FeatureResult MyEventReceiver::onCompletedLbp(CImg<unsigned char>* img, bool silence)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);

    // Sobel Image
    LbpHistogramResult result = this->completedLbpService->calculateLbpHistogram(img, 8, 10);

    if(!silence)
    {
        // Generate Diagram
        std::string fileName = this->tempFileNameService->generateFileNamePng();
        this->histogram(result.getLbpHistogram(), 5, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
        fileName = this->tempFileNameService->generateFileNamePng();
        this->histogram(result.getUniformityHistogram(), 3, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    return this->calculateFeatureVector(result.getUniformityHistogram());
}

FeatureResult MyEventReceiver::onLbp(CImg<unsigned char>* img, bool silence)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);

    // Sobel Image
    LbpHistogramResult result = this->lbpService->calculateLbpHistogram(img, 8, 10);

    if(!silence)
    {
        // Generate Diagram
        std::string fileName = this->tempFileNameService->generateFileNamePng();
        this->histogram(result.getLbpHistogram(), 5, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
        fileName = this->tempFileNameService->generateFileNamePng();
        this->histogram(result.getUniformityHistogram(), 3, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    FeatureResult fv = this->calculateFeatureVector(result.getUniformityHistogram());
    
    if(fv.getFeatureVector().size() < 3)
    {
        this->showMessage(L"LBP: Too less values in feature vector");
        fv = FeatureResult();
    }

    //return fv;
    return FeatureResult(fv.getFeatureVector()[0], fv.getFeatureVector()[2], fv.getFeatureVector()[3]);
}

FeatureResult MyEventReceiver::onSdSf(CImg<unsigned char>* img, bool slience)
{
    // Sobel Image
    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);
    
    // Create SD-SF-Diagram
    std::map<std::string, int> distanceHistogram = this->sdSfService->calculateSdSf(&sobelImage);

    if(!slience)
    {
        std::string sobelName = this->tempFileNameService->generateFileNamePng();
        sobelImage.save(sobelName.c_str());
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);

        std::string fileName = this->tempFileNameService->generateFileNamePng();
        this->histogram(distanceHistogram, 4, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    FeatureResult result(distanceHistogram["0.20"], distanceHistogram["0.80"]);

    if (result.getFeatureVector().size() != 2)
    {
        throw "Misscalculate feature!";
    }

    return result;
}

FeatureResult MyEventReceiver::onHuMoment(std::string fileName, CImg<unsigned char>* img, bool silence)
{
    try
    {
        double huMoments[7];
        int huMomentOpenCVMoments[] = { GUI_ID_VALUE_HU_OPENCV_1, GUI_ID_VALUE_HU_OPENCV_2, GUI_ID_VALUE_HU_OPENCV_3, GUI_ID_VALUE_HU_OPENCV_4, GUI_ID_VALUE_HU_OPENCV_5, GUI_ID_VALUE_HU_OPENCV_6, GUI_ID_VALUE_HU_OPENCV_7 };

        cv::Mat image = cv::imread(fileName.c_str(), cv::IMREAD_GRAYSCALE);
        cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);

        // Calculate Moments 
        cv::Moments moments = cv::moments(image, false);
        // Calculate Hu Moments 
        cv::HuMoments(moments, huMoments);

        if(!silence)
        {
            int length = sizeof(huMoments) / sizeof(double);
            for (int i = 0; i < length; i++)
            {
                std::wstring huString = this->stringSerivce->doubleToWString(huMoments[i]);
                this->graphicEngine->setGUIElementText(huMomentOpenCVMoments[i], huString.c_str());
            }
        }

        return FeatureResult(huMoments[1], huMoments[2], huMoments[5], huMoments[6]);
    }
    catch (cv::Exception e)
    {
        std::string message = e.what();
        int b = 0;
    }
    
    return FeatureResult();
    
    /*
    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);

    // Output the chart
    if (!silence)
    {
        std::string sobelName = this->tempFileNameService->generateFileNamePng();
        sobelImage.save(sobelName.c_str());

        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);
    }
    
    double hu1 = this->huMomentsService->calculateHu1(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu1);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_1, huString.c_str());
    }

    double hu2 = this->huMomentsService->calculateHu2(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu2);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_2, huString.c_str());
    }

    double hu3 = this->huMomentsService->calculateHu3(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu3);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_3, huString.c_str());
    }

    double hu4 = this->huMomentsService->calculateHu4(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu4);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_4, huString.c_str());
    }

    double hu5 = this->huMomentsService->calculateHu5(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu5);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_5, huString.c_str());
    }

    double hu6 = this->huMomentsService->calculateHu6(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu6);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_6, huString.c_str());
    }

    double hu7 = this->huMomentsService->calculateHu7(&sobelImage);
    if(!silence)
    {
        std::wstring huString = this->stringSerivce->doubleToWString(hu7);
        this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_7, huString.c_str());
    }

    FeatureResult result = FeatureResult(hu1, hu2, hu3, hu4, hu5, hu6, hu7);

    if (result.getFeatureVector().size() != 7)
    {
        return FeatureResult();
    }

    return result;*/
}

FeatureResult MyEventReceiver::onDiscreteFourierTransformation(CImg<unsigned char>* img, bool silence)
{
#ifdef _USE_PYTHON_SCRIPTS
    CImg<unsigned char> sobelImage = this->sobelOperatorSerivce->getGradientImage(img);
    std::vector<std::complex<double>> complexConture = this->cImgService->getContureAsComplexVector(&sobelImage, ColorRGB(0, 0, 0));

    if (complexConture.size() <= 0)
    {
        if (!silence)
            this->showMessage(L"Found no conture!");

        return FeatureResult();
    }

    std::vector<std::complex<double>> fequence;

    try
    {
        fequence = this->discreteFourierTransformationSerivce->calculate(complexConture);

    }
    catch (exception e)
    {
        int bla = 0;
    }

    if (!silence)
    {
        std::string fileName = this->tempFileNameService->generateFileNamePng();
        sobelImage.save_png(fileName.c_str());
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

        // Generate Diagram
        fileName = this->tempFileNameService->generateFileNamePng();
        this->diagram(fequence, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    auto featureresult = this->calculateFeatureVector(this->toDoubleVector(fequence));
    std::vector<double> featureVector = featureresult.getFeatureVector();

    return FeatureResult(featureVector[0], featureVector[2], featureVector[3], featureVector[6]);
#else
    FDResult result = this->discreteFourierTransformationSerivce->calculate(img, 2000);

    if (!silence)
    {
        // Add sobel image
        std::string fileName = this->tempFileNameService->generateFileNamePng();
        result.sobelImage.save_png(fileName.c_str());
        this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

        // Generate Diagram
        fileName = this->tempFileNameService->generateFileNamePng();
        this->diagram(result.fequence, fileName);
        this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    }

    if (!result.getSuccess())
    {
        return FeatureResult();
    }

    return this->calculateFeatureVector(this->toDoubleVector(result.fequence));
#endif // !_USE_PYTHON_SCRIPTS
}

void MyEventReceiver::onCalculateSuperPixels(CImg<unsigned char>* img)
{
    SubregionResult result = this->superPixelService->calculateSuperPixelsAndSubregions(img, 50);

    std::string fileName = this->tempFileNameService->generateFileNamePng();

    this->superPixelToImage(result.superPixelClusters, img->width(), img->height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    fileName = this->tempFileNameService->generateFileNamePng();

    this->superPixelToImage(result.subregions, img->width(), img->height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onCalculateSobelOperator(CImg<unsigned char>* img)
{
    CImg<unsigned char> tempImage = this->sobelOperatorSerivce->getGradientImage(img);

    std::string tempFileName = this->tempFileNameService->generateFileNamePng();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onCalculateImprovedSobelOperator(CImg<unsigned char>* img)
{
    CImg<unsigned char> tempImage = this->improvedSobelOperatorService->getGradientImage(img);

    std::string tempFileName = this->tempFileNameService->generateFileNamePng();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

FeatureResult MyEventReceiver::onYolo10(CImg<unsigned char>* img, bool silence)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;
    const unsigned char wihte[] = { 255,255,255 };

    CImg<unsigned char> sizeImg(*img);
    sizeImg.resize(sizeImg.width() + 1, sizeImg.height() + 1);
    sizeImg.draw_line(sizeImg.width() - 1, 0, sizeImg.width() - 1, sizeImg.height() - 1, wihte);
    sizeImg.draw_line(0, sizeImg.height() - 1, sizeImg.width() - 1, sizeImg.height() - 1, wihte);
    sizeImg.resize(600, 600, -100, -100, 0, 1, 0, 0, 0, 0);

    std::string tempFileName = this->tempFileNameService->generateFileNamePng();
    sizeImg.save_png(tempFileName.c_str());

    std::vector<double> result = this->yolov10Service->calculate(tempFileName);

    if (result.size() != 0)
    {
        double doubleClass = this->mathSerivce->avg(result);
        double roundedClass = this->mathSerivce->roundDigits(doubleClass, 0);

        return FeatureResult(roundedClass);
    }

    return FeatureResult(NAN);
}

FeatureResult MyEventReceiver::onGrayscaleBasedValues(CImg<unsigned char>* img)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);

    //double mean = this->histogramValueService->getMean(img);
    //double variance = this->histogramValueService->getVariance(img);
    double skewness = this->histogramValueService->getSkewness(img);
    double kurtosis = this->histogramValueService->getKurtosis(img);
    //double power = this->histogramValueService->getPower(img);
    double entropy = this->histogramValueService->getEntropy(img);

    if (isnan(skewness))
    {
        skewness = 0;
    }

    if (isnan(kurtosis))
    {
        kurtosis = 0;
    }

    FeatureResult result = FeatureResult(/*mean, variance,*/ skewness, kurtosis, /*power,*/ entropy);

    if (result.getFeatureVector().size() != /*6*/ 3)
    {
        return FeatureResult();
    }

    return result;
}


FeatureResult MyEventReceiver::onGeometricValues(CImg<unsigned char>* img, std::string fileName)
{
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(img);
    Point2D roiLength = this->geometricService->getRoiLength(img, backgroundColor);

    int defectPixels = this->geometricService->countDefectPixels(img, backgroundColor);
    double lenght = ((double)roiLength.x);
    double widht = (double)roiLength.y;
    double rotioRoiArea = defectPixels / ((double)roiLength.x) * ((double)roiLength.y);
    double rotioWidthLength = ((double)roiLength.x) / ((double)roiLength.y);
    int scope = this->geometricService->calculateScope(img, backgroundColor);
    Point2D defectFocus = this->geometricService->calculateCentroid(img, backgroundColor);
    double rectangularity = this->geometricService->calculateRectangularity(img, backgroundColor);

    OrientationResult orientationResult = this->calculteOpenCVValues(fileName);

    /*
    FeatureResult result = FeatureResult(lenght, widht, defectPixels, rotioRoiArea, rotioWidthLength, scope, defectFocus.x, defectFocus.y, rectangularity);

    if (result.getFeatureVector().size() != 7)
    {
        return FeatureResult();
    }*/

    FeatureResult result = FeatureResult(rotioWidthLength, rotioRoiArea, orientationResult.height);

    return result;
}

void MyEventReceiver::onSelectFile(core::stringc fileName)
{
    this->onCreateImagePannel();

    std::string fixedFileName = this->saveFixedImage(fileName.c_str());
    
    OrientationResult orientationResult = this->calculteOpenCVValues(fixedFileName);

    std::wstring widthString = this->stringSerivce->intToWString(orientationResult.width);
    std::wstring widthStringUnit = widthString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_WIDTH, widthStringUnit.c_str());

    std::wstring heightString = this->stringSerivce->intToWString(orientationResult.height);
    std::wstring heightStringUnit = heightString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HEIGHT, heightStringUnit.c_str());

    std::wstring angleString = this->stringSerivce->intToWString(orientationResult.angle);
    std::wstring angleStringUnit = angleString + std::wstring(L" Grad");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ANGLE, angleStringUnit.c_str());

    CImg<unsigned char> img = CImg<unsigned char>(fixedFileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);
    std::wstring backgroundColorString = this->stringSerivce->doubleToWString(backgroundColor.r)+L"|"+this->stringSerivce->doubleToWString(backgroundColor.g) + L"|" + this->stringSerivce->doubleToWString(backgroundColor.b);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_BACKGROUND_COLOR, backgroundColorString.c_str());

    int defectPixels = this->geometricService->countDefectPixels(&img, backgroundColor);
    std::wstring defectPixelsString = this->stringSerivce->intToWString(defectPixels);
    std::wstring defectPixelsStringUnit = defectPixelsString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_AREA, defectPixelsStringUnit.c_str());

    Point2D roiLength = this->geometricService->getRoiLength(&img, backgroundColor);
    std::wstring roiString = this->stringSerivce->intToWString(roiLength.x) + L" x " + this->stringSerivce->intToWString(roiLength.y) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ROI, roiString.c_str());

    double rotioWidthLength = ((double)roiLength.x) / ((double)roiLength.y);
    std::wstring rotioWidthLengthString = this->stringSerivce->doubleToWString(rotioWidthLength);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, rotioWidthLengthString.c_str());

    double rotioRoiArea = defectPixels / ((double)roiLength.x) * ((double)roiLength.y);
    std::wstring rotioRoiAreaString = this->stringSerivce->doubleToWString(rotioRoiArea);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_AREA_ROI, rotioRoiAreaString.c_str());

    int scope = this->geometricService->calculateScope(&img, backgroundColor);
    std::wstring scropWithUnit = this->stringSerivce->doubleToWString(scope) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SCOPE, scropWithUnit.c_str());

    Point2D defectFocus = this->geometricService->calculateCentroid(&img, backgroundColor);
    std::wstring defectFocusString = L"(" + this->stringSerivce->doubleToWString(defectFocus.x) + L"px/" + this->stringSerivce->doubleToWString(defectFocus.y)+L"px)";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_DEFECT_FOCUS, defectFocusString.c_str());

    double rectangularity = this->geometricService->calculateRectangularity(&img, backgroundColor);
    std::wstring rectangularityString = this->stringSerivce->doubleToWString(rectangularity);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RECTANGULARITY, rectangularityString.c_str());
    
    double mean = this->histogramValueService->getMean(&img);
    std::wstring meanString = this->stringSerivce->doubleToWString(mean);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_MEAN, meanString.c_str());

    double variance = this->histogramValueService->getVariance(&img);
    std::wstring varianceString = this->stringSerivce->doubleToWString(variance);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_VARIANCE, varianceString.c_str());

    double skewness = this->histogramValueService->getSkewness(&img);
    std::wstring skewnessString = this->stringSerivce->doubleToWString(skewness);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SKEWNESS, skewnessString.c_str());

    double kurtosis = this->histogramValueService->getKurtosis(&img);
    std::wstring kurtosisString = this->stringSerivce->doubleToWString(kurtosis);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_KURTOSIS, kurtosisString.c_str());

    double power = this->histogramValueService->getPower(&img);
    std::wstring powerString = this->stringSerivce->doubleToWString(power);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_POWER, powerString.c_str());

    double entropy = this->histogramValueService->getEntropy(&img);
    std::wstring entropyString = this->stringSerivce->doubleToWString(entropy);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ENTROPY, entropyString.c_str());

    std::wstring wFileName = this->stringSerivce->toWString(fixedFileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(10, 10), wFileName.c_str(), GUI_ID_IMAGE_1_TAB);

    this->selectedFile = wFileName.c_str();
}

OrientationResult MyEventReceiver::calculteOpenCVValues(std::string filePath)
{
    // 1. Bild einlesen und binarisieren
    cv::Mat img = imread(filePath.c_str(), IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return OrientationResult(-1, -1, -1);
    }
    cv::Mat binary;
    cv::threshold(img, binary, 128, 255, THRESH_BINARY);

    // 2. Bild invertieren
    Mat inverted_img;
    bitwise_not(binary, inverted_img);

    //cv::imshow("Orientierungswinkel", inverted_img);
    //waitKey(0);

    // 2. Konturen finden
    std::vector<vector<Point>> contours;
    cv::findContours(inverted_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int height = 0;
    int width = 0;
    int angle = 0;

    std::vector<Point> contour;

    // 3. Orientierung jeder Kontur berechnen
    for (size_t i = 0; i < contours.size(); i++) {
        if (contours[i].size() < 2) continue; // Zu kleine Konturen ignorieren
        
        for(size_t j = 0; j < contours[i].size(); j++)
            contour.push_back(contours[i][j]);
    }

    if (contour.size() > 0)
    {
        cv::RotatedRect rotatedRect = cv::minAreaRect(contour);

        angle = rotatedRect.angle;

        if (rotatedRect.size.width > rotatedRect.size.height)
        {
            width = rotatedRect.size.width;
            height = rotatedRect.size.height;
        }
        else
        {
            width = rotatedRect.size.height;
            height = rotatedRect.size.width;
        }
    }

    return OrientationResult(width, height, angle);
}

void MyEventReceiver::superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned int> bg(width, height, size_z, size_c, 255);

    for (int k = 0; k < pixelCluster.size(); k++)
    {
        const unsigned char(&color)[3] = { (unsigned char)(k * 75), (unsigned char)((k%3) * k * 75), (unsigned char)((k%5) * k * 75) };

        for (int i = 0; i < pixelCluster[k].size(); i++)
        {
            SuperPixelEntry entry = pixelCluster[k][i];
            bg.draw_point(entry.position.x, entry.position.y, color);
        }
    }

    bg.save_png(tempPath.c_str());
}

void MyEventReceiver::onCreateImagePannel()
{
    this->graphicEngine->addSubwindow(GUI_ID_IMAGE_PANNEL, Point2D(0, 0), Point2D(500, 1060), L"Image");
    this->graphicEngine->addTabControl(GUI_ID_TABCONTROL, Point2D(0, 20), Point2D(500, 1060), GUI_ID_IMAGE_PANNEL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_1_TAB, L"Input image", GUI_ID_TABCONTROL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_2_TAB, L"Process image", GUI_ID_TABCONTROL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_3_TAB, L"Output image", GUI_ID_TABCONTROL);
}

void MyEventReceiver::onResetImages()
{
    if(this->graphicEngine->exists(GUI_ID_IMAGE_1))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_1);
    }

    if(this->graphicEngine->exists(GUI_ID_IMAGE_2_0))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2_0);
    }

    if(this->graphicEngine->exists(GUI_ID_IMAGE_2_1))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2_1);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_3_0))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_3_0);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_3_1))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_3_1);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_1_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_1_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_2_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_3_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_3_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_TABCONTROL))
    {
        this->graphicEngine->removeElement(GUI_ID_TABCONTROL);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_PANNEL))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_PANNEL);
    }
}

void MyEventReceiver::histogram(std::map<int, int> histogramData, int labelCount, std::string fileName)
{
    std::map<std::string, int> stringHistogramData;

    std::map<int, int>::iterator it;
    for (it = histogramData.begin(); it != histogramData.end(); it++)
    {        
		std::string key = std::format("{:03}", it->first);
        stringHistogramData.insert(std::pair<std::string, int>(key, it->second));
    }

    this->histogram(stringHistogramData, labelCount, fileName);
}

void MyEventReceiver::histogram(std::map<std::string, int> histogramData, int labelCount, std::string fileName)
{
    int n = histogramData.size();
    double* x = new double[n];
    const char** z = new const char* [n];

    int i = 0;
    std::map<std::string, int>::iterator it;
    for (it = histogramData.begin(); it != histogramData.end(); it++)
    {
        x[i] = it->second;
        z[i] = it->first.c_str();
        i++;
    }

    XYChart* c = new XYChart(500, 500);
    c->setPlotArea(50, 20, 430, 440);

    // Add a line chart layer using the given data
    c->addBarLayer(DoubleArray(x, n));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    double steps = ((double)n)/((double)labelCount);
    c->xAxis()->setLabelStep(steps);

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete[] x;
    delete[] z;
}

void MyEventReceiver::diagram(std::vector<std::complex<double>> data, std::string fileName, std::vector<std::complex<double>> complexDiscription, std::string title)
{
    std::vector<double> discription;

    for (int i = 0; i < complexDiscription.size(); i++)
    {
        discription.push_back(complexDiscription[i].real());
    }

    this->diagram(data, fileName, discription, title);
}

void MyEventReceiver::diagram(std::vector<std::complex<double>> data, std::string fileName, std::vector<double> discription, std::string title)
{
    int n = data.size();
    double* x = new double[n];
    double* y = new double[n];
    char** z = new char* [n];

    for (uint32_t i = 0; i < n; ++i)
    {
        x[i] = data[i].real();
        y[i] = data[i].imag();

        if (discription.size() == 0)
        {
            z[i] = new char[20];
            itoa(i, z[i], 10);
        }
        else
        {
            std::string discriptionString = this->stringSerivce->doubleToString(discription[i]);

            z[i] = new char[discriptionString.size()+1];
            discriptionString.copy(z[i], discriptionString.size());
            z[i][discriptionString.size()] = '\0';
        }
    }

    XYChart* c = new XYChart(500, 500);
    c->setPlotArea(50, 20, 430, 440);

    c->addTitle(title.c_str());

    int realColor = 0xff0000;
    int imagColor = 0x00cc00;

    // Add a line chart layer using the given data
    c->addLineLayer(DoubleArray(x, n), realColor, "Real");
    c->addLineLayer(DoubleArray(y, n), imagColor, "Imaginär");

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    c->xAxis()->setLabelStep(n/3);

    LegendBox* b = c->addLegend(70, 10, false, "Arial", 12);
    b->setBackground(Chart::Transparent, Chart::Transparent);
    b->setLineStyleKey();

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete[] x;
    delete[] y;

    for (int i = 0; i < n; ++i)
    {
        delete[] z[i];
    }

    delete[] z;
}

void MyEventReceiver::diagram(std::vector<double> data, std::string fileName)
{
    int n = data.size();
    double* x = new double[n];
    const char** z = new const char* [n];

    for (int i = 0; i < n; ++i)
    {
        x[i] = data[i];

        const char* label = this->stringSerivce->intToString(i).c_str();
        z[i] = label;
    }

    XYChart* c = new XYChart(500, 500);
    c->setPlotArea(50, 20, 430, 440);

    // Add a line chart layer using the given data
    c->addLineLayer(DoubleArray(x, n));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    c->xAxis()->setLabelStep(3);

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete[] x;

    delete[] z;
}

void MyEventReceiver::heatMap(TimeFrequenceResult timeFrequence, std::vector<double> labels, std::string fileName)
{
    bool xIsGenerated = false;

    double timeMin = DBL_MAX;
    double timeMax = -DBL_MAX;

    // The x and y coordinates of the grid
    double* dataX = NULL;
    const int dataX_size = timeFrequence.getTimeScala(1).size();

    if (labels.size() == 0)
    {
        dataX = this->generateNewArray(dataX_size);
        xIsGenerated = true;
    }
    else
    {
        dataX = labels.data();
    }

    double* dataY = this->generateNewArrayFromExsistingFrequence(timeFrequence);
    //double* dataY = this->generateNewArray(timeFrequence.getMaxFrequence());
    const int dataY_size = timeFrequence.frequenceTimeMap.size();

    // The values at the grid points. In this example, we will compute the values using the formula
    // z = x * sin(y) + y * sin(x).
    int dataZ_size = dataX_size * (dataY_size+1);
    double* dataZ = new double[dataZ_size];
    for (int yIndex = 0; yIndex < dataY_size; ++yIndex)
    {
        double y = this->mathSerivce->roundDigits(dataY[yIndex], 2);

        if (yIndex != 0 && y == 0)
        {
            break;
        }

        std::vector<double> time = timeFrequence.getTimeScala(y);
        
        for (int xIndex = 0; xIndex < dataX_size; ++xIndex)
        {
            double value = 0;
                
            if(time.size() > 0)
            {
                value = this->mathSerivce->roundDigits(time[xIndex], 3);
            }

            if (value < timeMin)
            {
                timeMin = value;
            }
            else if (value > timeMax)
            {
                timeMax = value;
            }

            if (value <= 0 || isnan(value) || isinf(value))
            {
                value = 0;
            }

            dataZ[yIndex * dataX_size + xIndex] = value;
        }
    }

    // Create a XYChart object of size 600 x 500 pixels
    XYChart* c = new XYChart(500, 500);

    // Add a title to the chart using 15 points Arial Bold Italic font
    c->addTitle("Wavlet scalogram", "Arial Bold Italic", 15);

    // Set the plotarea at (75, 40) and of size 400 x 400 pixels. Use semi-transparent black
    // (80000000) dotted lines for both horizontal and vertical grid lines
    c->setPlotArea(40, 40, 380, 380, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);

    // Set x-axis and y-axis title using 12 points Arial Bold Italic font
    c->xAxis()->setTitle("Time", "Arial Bold Italic", 12);
    c->yAxis()->setTitle("Frequence", "Arial Bold Italic", 12);

    // Set x-axis and y-axis labels to use Arial Bold font
    c->xAxis()->setLabelStyle("Arial Bold");
    c->yAxis()->setLabelStyle("Arial Bold");

    // When auto-scaling, use tick spacing of 40 pixels as a guideline
    c->yAxis()->setTickDensity(40);
    c->xAxis()->setTickDensity(40);

    // Add a contour layer using the given data
    ContourLayer* layer = c->addContourLayer(DoubleArray(dataX, dataX_size), DoubleArray(dataY,
        dataY_size), DoubleArray(dataZ, dataZ_size));

    // Move the grid lines in front of the contour layer
    //c->getPlotArea()->moveGridBefore(layer);

    // Add a color axis (the legend) in which the top left corner is anchored at (505, 40). Set the
    // length to 400 pixels and the labels on the right side.
    ColorAxis* cAxis = layer->setColorAxis(420, 20, Chart::TopLeft, 250, Chart::Right);

    // Add a title to the color axis using 12 points Arial Bold Italic font
    cAxis->setTitle("Legende", "Arial Bold Italic", 12);

    // Set color axis labels to use Arial Bold font
    cAxis->setLabelStyle("Arial Bold");

    // Output the chart
    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete[] dataY;
    delete[] dataZ;

    if (xIsGenerated)
    {
        delete[] dataX;
    }
}

void MyEventReceiver::heatMap(std::map<int, std::vector<std::complex<double>>> input, int maxLevel, std::vector<double> labels, std::string fileName)
{
    bool xIsGenerated = false;

    double timeMin = DBL_MAX;
    double timeMax = -DBL_MAX;

    // The x and y coordinates of the grid
    double* dataX = NULL;
    const int dataX_size = input[1].size();

    if (labels.size() == 0)
    {
        dataX = this->generateNewArray(dataX_size);
        xIsGenerated = true;
    }
    else
    {
        dataX = labels.data();
    }

    double* dataY = this->generateNewArrayFromExsistingFrequence(input, maxLevel);
    //double* dataY = this->generateNewArray(timeFrequence.getMaxFrequence());
    const int dataY_size = input.size();

    // The values at the grid points. In this example, we will compute the values using the formula
    // z = x * sin(y) + y * sin(x).
    int dataZ_size = dataX_size * (dataY_size+1);
    double* dataZ = new double[dataZ_size];
    for (int yIndex = 0; yIndex < dataY_size; ++yIndex)
    {
        double y = this->mathSerivce->roundDigits(dataY[yIndex], 2);

        if (yIndex != 0 && y == 0)
        {
            break;
        }

        std::vector<std::complex<double>> time = input[y];
        
        for (int xIndex = 0; xIndex < time.size(); ++xIndex)
        {
            double value = 0;
                
            if(time.size() > 0)
            {
                double eulerValue = this->mathSerivce->calculateEuler(time[xIndex], 1);
                value = this->mathSerivce->roundDigits(eulerValue, 3);
            }

            if (value < timeMin)
            {
                timeMin = value;
            }
            else if (value > timeMax)
            {
                timeMax = value;
            }

            if (value <= 0 || isnan(value) || isinf(value))
            {
                value = 0;
            }

            dataZ[yIndex * dataX_size + xIndex] = value;
        }
    }
    /*
    for (int i = 0; i < dataZ_size; i++)
    {
        double orgValue = dataZ[i];
        double value = this->mathSerivce->roundDigits(orgValue / timeMax, 4);

        if (value <= 0)
        {
            value = 0.05;
        }

        dataZ[i] = value;
    }*/

    // Create a XYChart object of size 600 x 500 pixels
    XYChart* c = new XYChart(500, 500);

    // Add a title to the chart using 15 points Arial Bold Italic font
    c->addTitle("Wavlet scalogram", "Arial Bold Italic", 15);

    // Set the plotarea at (75, 40) and of size 400 x 400 pixels. Use semi-transparent black
    // (80000000) dotted lines for both horizontal and vertical grid lines
    c->setPlotArea(40, 40, 380, 380, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);

    // Set x-axis and y-axis title using 12 points Arial Bold Italic font
    c->xAxis()->setTitle("Time", "Arial Bold Italic", 12);
    c->yAxis()->setTitle("Level", "Arial Bold Italic", 12);

    // Set x-axis and y-axis labels to use Arial Bold font
    c->xAxis()->setLabelStyle("Arial Bold");
    c->yAxis()->setLabelStyle("Arial Bold");

    // When auto-scaling, use tick spacing of 40 pixels as a guideline
    c->yAxis()->setTickDensity(40);
    c->xAxis()->setTickDensity(40);

    // Add a contour layer using the given data
    ContourLayer* layer = c->addContourLayer(DoubleArray(dataX, dataX_size), DoubleArray(dataY,
        dataY_size), DoubleArray(dataZ, dataZ_size));

    // Move the grid lines in front of the contour layer
    //c->getPlotArea()->moveGridBefore(layer);

    // Add a color axis (the legend) in which the top left corner is anchored at (505, 40). Set the
    // length to 400 pixels and the labels on the right side.
    ColorAxis* cAxis = layer->setColorAxis(420, 20, Chart::TopLeft, 250, Chart::Right);

    // Add a title to the color axis using 12 points Arial Bold Italic font
    cAxis->setTitle("Legende", "Arial Bold Italic", 12);

    // Set color axis labels to use Arial Bold font
    cAxis->setLabelStyle("Arial Bold");

    // Output the chart
    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete[] dataY;
    delete[] dataZ;

    if (xIsGenerated)
    {
        delete[] dataX;
    }
}

double* MyEventReceiver::generateNewArrayFromExsistingFrequence(TimeFrequenceResult timeFrequence)
{
    int to = timeFrequence.frequenceTimeMap.size();
    double* result = new double[to];

    int arrayIndex = 0;

    for (int i = 0; i <= timeFrequence.getMaxFrequence(); ++i)
    {
        if (timeFrequence.frequenceTimeMap.find(i) != timeFrequence.frequenceTimeMap.end())
        {
            result[arrayIndex] = i;
            arrayIndex++;
        }
    }

    while(arrayIndex < to)
    {
        result[arrayIndex] = timeFrequence.getMaxFrequence()+1;
        arrayIndex++;
    }

    return result;
}

double* MyEventReceiver::generateNewArrayFromExsistingFrequence(std::map<int, std::vector<std::complex<double>>> frequenceTimeMap, int maxFrequence)
{
    int to = frequenceTimeMap.size();
    double* result = new double[to];

    int arrayIndex = 0;

    for (int i = 0; i <= maxFrequence; ++i)
    {
        if (frequenceTimeMap.find(i) != frequenceTimeMap.end())
        {
            result[arrayIndex] = i;
            arrayIndex++;
        }
    }

    while(arrayIndex < to)
    {
        result[arrayIndex] = maxFrequence+1;
        arrayIndex++;
    }

    return result;
}

double* MyEventReceiver::generateNewArray(int to)
{
    double* array = new double[to];

    for (int i = 0; i < to; ++i) {
        array[i] = i;
    }

    return array;
}

void MyEventReceiver::heatMapImg(TimeFrequenceResult timeFrequence, std::string fileName)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    double timeMin = DBL_MAX;
    double timeMax = -DBL_MAX;

    const int timeScalaSize = timeFrequence.getTimeScala(1).size();
    const int frequenceSize = timeFrequence.getMaxFrequence();

    CImg<unsigned char> transposeMatrix(frequenceSize, timeScalaSize, size_z, size_c, 0);

    for (int yIndex = 1; yIndex < frequenceSize; ++yIndex) {

        std::vector<double> time = timeFrequence.getTimeScala(yIndex);

        for (int xIndex = 0; xIndex < timeScalaSize; ++xIndex) {
            double value = time[xIndex];

            if (value < timeMin)
            {
                timeMin = value;
            }
            else if (value > timeMax)
            {
                timeMax = value;
            }
        }
    }

    for (int yIndex = 1; yIndex < frequenceSize; ++yIndex) 
    {
        std::vector<double> time = timeFrequence.getTimeScala(yIndex);

        for (int xIndex = 0; xIndex < timeScalaSize; ++xIndex) 
        {
            double value = time[xIndex] / timeMax * 255.0;

            const unsigned char* color = this->colorService->rgb2byte(ColorRGB(value, value, value));
            transposeMatrix.draw_point(yIndex, xIndex, color);
        }
    }

    const unsigned char* color = this->colorService->rgb2byte(ColorRGB(255, 255, 255));
    transposeMatrix.draw_text(frequenceSize / 2, timeScalaSize - 20, "Frequence", color);

    transposeMatrix.save_png(fileName.c_str());
}

std::map<double, std::vector<double>> MyEventReceiver::toDoubleMap(std::map<int, std::vector<std::complex<double>>> a)
{
    std::map<double, std::vector<double>> result;
    std::map<int, std::vector<std::complex<double>>>::iterator it;
    for (it = a.begin(); it != a.end(); it++)
    {  
        std::vector<std::complex<double>> list = it->second;
        std::vector<double> convertedList;

        for(int i = 0; i < list.size();i++)
        {
            double value = this->mathSerivce->calculateEuler(list[i], 1);
            convertedList.push_back(value);
        }

        result.insert(std::pair<double, std::vector<double>>(it->first, convertedList));
    }

    return result;
}

std::map<double, std::vector<double>> MyEventReceiver::toDoubleMap(std::map<double, std::vector<std::complex<double>>> a)
{
    std::map<double, std::vector<double>> result;
    std::map<double, std::vector<std::complex<double>>>::iterator it;
    for (it = a.begin(); it != a.end(); it++)
    {  
        std::vector<double> convertedList = this->toDoubleVector(it->second);
        result.insert(std::pair<double, std::vector<double>>(it->first, convertedList));
    }

    return result;
}

std::vector<double> MyEventReceiver::toDoubleVector(std::vector<std::complex<double>> list)
{
    std::vector<double> convertedList;

    for(int i = 0; i < list.size();i++)
    {
        double value = this->mathSerivce->calculateEuler(list[i], 1);
        convertedList.push_back(value);
    }

    return convertedList;
}

FeatureResult MyEventReceiver::calculateFeatureVector(std::map<int, std::vector<double>> heatMap)
{
    std::map<double, std::vector<double>> conerted;

    for (std::map<int, std::vector<double>>::iterator it = heatMap.begin(); it != heatMap.end(); ++it)
    {
        conerted.insert(std::pair<double, std::vector<double>>(it->first, it->second));
    }

    return this->calculateFeatureVector(conerted);
}

FeatureResult MyEventReceiver::calculateFeatureVector(std::map<double, std::vector<double>> heatMap)
{
    /*
    double maxFrequence = -INT_MAX;
    double minFrequence = INT_MAX;
    double maxAmplitude = -INT_MAX;
    double minAmplitude = INT_MAX;
    double avgFrequence = 0;
    double avgAmplitude = 0;
    long amplitudeCount = 0;
    long frequenceCount = 0;*/

    std::vector<double> frequenceVector;
    std::vector<double> amplitudeVector;

    for (std::map<double, std::vector<double>>::iterator it = heatMap.begin(); it != heatMap.end(); ++it)
    {
        double frequence = it->first;
        frequenceVector.push_back(frequence);
        
        std::vector<double> timeLine = it->second;
        /*
        if(frequence < minFrequence)
        {
            minFrequence = frequence;
        }

        if(frequence > maxFrequence)
        {
            maxFrequence = frequence;
        }

        avgFrequence += frequence;*/

        for(int i = 0; i < timeLine.size() ;i++)
        {
            amplitudeVector.push_back(timeLine[i]);
        }

        // frequenceCount++;
    }

    // avgAmplitude /= amplitudeCount;
    // avgFrequence /= frequenceCount;

    auto minFrequence = min_element(frequenceVector.begin(), frequenceVector.end());
    auto maxFrequence = max_element(frequenceVector.begin(), frequenceVector.end());
    double avgFrequence = this->mathSerivce->avg(frequenceVector);
    double skewnessFrequence = this->mathSerivce->calculateSkewness(frequenceVector);
    double varianceFrequence = this->mathSerivce->calculateVariance(frequenceVector);
    double energyFrequence = this->mathSerivce->calculateEnergy(frequenceVector);
    double kurtosisFrequence = this->mathSerivce->calculateKurtosis(frequenceVector);

    auto minAmplitude = min_element(amplitudeVector.begin(), amplitudeVector.end());
    auto maxAmplitude = max_element(amplitudeVector.begin(), amplitudeVector.end());
    double avgAmplitude = this->mathSerivce->avg(amplitudeVector);
    double skewnessAmplitude = this->mathSerivce->calculateSkewness(amplitudeVector);
    double varianceAmplitude = this->mathSerivce->calculateVariance(amplitudeVector);
    double energyAmplitude = this->mathSerivce->calculateEnergy(amplitudeVector);
    double kurtosisAmplitude = this->mathSerivce->calculateKurtosis(amplitudeVector);

    FeatureResult result = FeatureResult(*minFrequence, *maxFrequence, avgFrequence, skewnessFrequence, varianceFrequence, energyFrequence, kurtosisFrequence, 
                                         *minAmplitude, *maxAmplitude, avgAmplitude, skewnessAmplitude, varianceAmplitude, energyAmplitude, kurtosisAmplitude);

    if(result.getFeatureVector().size() != 14)
    {
        this->showMessage(L"Calculation not valid!");
        return FeatureResult();
    }

    std::string valueString = "";
    std::vector<double> featureVector = result.getFeatureVector();
    for (int i = 0; i < featureVector.size(); i++)
    {
        valueString += this->stringSerivce->doubleToString(featureVector[i]) + " & ";
    }

    return result;
}

FeatureResult MyEventReceiver::calculateFeatureVector(std::vector<double> vector)
{
    auto minFrequence = min_element(vector.begin(), vector.end());
    auto maxFrequence = max_element(vector.begin(), vector.end());
    double avgFrequence = this->mathSerivce->avg(vector);
    double skewness = this->mathSerivce->calculateSkewness(vector);
    double variance = this->mathSerivce->calculateVariance(vector);
    double energy = this->mathSerivce->calculateEnergy(vector);
    double kurtosis = this->mathSerivce->calculateKurtosis(vector);

    FeatureResult result = FeatureResult(*minFrequence, *maxFrequence, avgFrequence, skewness, variance, energy, kurtosis);

    if(result.getFeatureVector().size() != 7)
    {
        this->showMessage(L"Calculation not valid!");
        result = FeatureResult();
    }

    std::string valueString = "";
    std::vector<double> featureVector = result.getFeatureVector();
    for (int i = 0; i < featureVector.size(); i++)
    {
        valueString += this->stringSerivce->doubleToString(featureVector[i]) + " & ";
    }

    return result;
}

FeatureResult MyEventReceiver::calculateFeatureVector(std::map<std::string, int> map)
{
    std::string valueSum = "";
    std::vector<double> vector;

    for (std::map<std::string, int>::iterator it = map.begin(); it != map.end(); ++it)
    {
        vector.push_back(it->second);
        valueSum += this->stringSerivce->intToString(it->second) + " & ";
    }

    return FeatureResult(vector);
}