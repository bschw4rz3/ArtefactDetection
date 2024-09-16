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

    this->stringSerivce = di->stringSerivce;
    this->directoryService = di->directoryService;
    this->mathSerivce = di->mathSerivce;
    this->colorService = di->colorService;
    this->cImgService = di->imgService;

    this->facet = NULL;
    this->context = NULL;

    this->isRunning = false;
    this->isAbbord = false;

    this->progressSymbol = '-';
    this->selectedFile = L"";
    this->tempFileIndex = 0;
}

MyEventReceiver::~MyEventReceiver()
{
    this->isAbbord = true;

    if (this->isRunning)
    {
        //this->onJoinTask();
    }

    this->removeTempFiles();
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
                if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SUPERPIXELS))
                {
                    this->onCalculateSuperPixels();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SOBEL))
                {
                    this->onCalculateSobelOperator();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_IMPROVED_SOBEL))
                {
                    this->onCalculateImprovedSobelOperator();
                }
                else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION))
                {
                    this->onDiscreteFourierTransformation();
                }
                else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HU_MOMENT))
                {
                    this->onHuMoment();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SDSF))
                {
                    this->onSdSf();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_LBP))
                {
                    this->onLbp();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_COMPLETED_LBP))
                {
                    this->onCompletedLbp();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GLCM))
                {
                    this->onGLCM();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HOG))
                {
                    this->onHOG();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GABOR))
                {
                    this->onGaborFilter();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_WAVELET))
                {
                    this->onWavelet();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION_CV))
                {
                    this->onDiscreteFourierTransformationCV();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_FOURIER_DISCRIPTOR))
                {
                    this->onFourierDiscriptor();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DAUBECHIES_FOUR_WAVELET))
                {
                    this->onDaubechiesFourWavelet();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_MORLET_WAVELET))
                {
                    this->onMorletFourWavelet();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_MORLET_WAVELET_FFT))
                {
                    this->onMorletFourWaveletFFT();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HAAR_WAVLET))
                {
                    this->onHaarWavelet();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DAUBECHIES_SECOND))
                {
                    this->onDaubechiesSecond();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_BIOR_WAVLET))
                {
                    this->onBiorWavlet();
                }

                // Clean up
                this->removeTempFiles();
            }
            else if (id == GUI_ID_BUTTON_CHOOSE_FILE)
            {
                this->onResetImages();
                this->graphicEngine->addFileOpenDialog(GUI_ID_DIALOG_CHOOSE_FILE, L"..\\AnomalyGeneration\\testdata");
            }
            else if(id == GUI_ID_BUTTON_GENERATE_TRAININGS_DATA)
            {
                this->onGenerateTrainingsData();
            }
            else if(id == GUI_ID_BUTTON_CLASSIFY)
            {
                this->onClassify();
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

            if(id == GUI_ID_CHECKBOX_CLASSIFY_DECISION_TREE || id == GUI_ID_CHECKBOX_CLASSIFY_K_NEAREST_NEIGHBOR  || id == GUI_ID_CHECKBOX_CLASSIFY_SUPPORT_VECTOR_MACHINE)
            {
                this->graphicEngine->resetCheckBoxsByWindowId(GUI_ID_CLASSIFY_PANNEL);
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

void MyEventReceiver::onGenerateTrainingsData()
{

}

void MyEventReceiver::onClassify()
{

}

/*
void display_superimposed(const cv::Mat& A1, const cv::Mat& B, const std::string& fileName)
{
    cv::Mat A;
    cv::Mat C;

    cvtColor(A1, A, cv::COLOR_BGR2GRAY);

    int aChannels = A.channels();
    int bChannels = B.channels();

    if(aChannels != bChannels)
    {
        throw "Ungleiche Channels";
    }

    try
    {
        cv::addWeighted(A, 0.5, B, 0.5, 0.0, C, C.type());
    }
    catch(cv::Exception e)
    {
        std::cout << e.what();
    }
    
    cv::imwrite(fileName, C);
}

cv::Mat custom_normalization(const cv::Mat& src) {
    double min, max;
    cv::minMaxLoc(src, &min, &max);
    cv::Mat dst = src * 200 / (max - min) + 128;
    dst.convertTo(dst, CV_8U);
    return dst;
}*/

void MyEventReceiver::onBiorWavlet()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<double, std::vector<std::complex<double>>> result = this->biorWavlet->calculate(complexTime, 10);

    
    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(TimeFrequenceResult(this->toDoubleMap(result), 30), std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);

}

void MyEventReceiver::onDaubechiesFourWavelet()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<int, std::vector<std::complex<double>>> result = this->daubechiesFourWaveletService->calculate(complexTime);

    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(result, 10, std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onDaubechiesSecond()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<int, std::vector<std::complex<double>>> result = this->daubechiesSecondWaveletService->calculate(complexTime);

    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(result, 10, std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onHaarWavelet()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    std::map<double, std::vector<double>> result = this->haarWaeletService->calculate(complexTime);

    
    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(TimeFrequenceResult(result, 40), std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onMorletFourWaveletFFT()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);

    /*
    double A = 1;
    double omega = 10;
    double timeFactor = 0.01;
    double timeMax = 30;
    double maxFrequence = 40;

    std::vector<double> complexTime;
    std::vector<std::complex<double>> complexTime2;
    std::vector<double> labels;

    for (double t = 0.0; t <= timeMax; t+=timeFactor)
    {
        labels.push_back(t);
        double value = A * cos(((omega*t)+pow(t, 3.0))-2.0);

        complexTime.push_back(value);
        complexTime2.push_back(value);
    }

    labels.push_back(timeMax+timeFactor);*/

    std::map<double, std::vector<double>> result = this->morletWaveletServiceFFT->calculate(complexTime);

    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(TimeFrequenceResult(result, 40), std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onMorletFourWavelet()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    CImg<unsigned char> sobel = this->sobelOperatorSerivce->getGradientImage(&img);
    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&sobel);
    Point2D center = this->geometricService->calculateCentroid(&sobel, backgroundColor);

    std::vector<std::complex<double>> complexTime = this->cImgService->getContureAsComplexVector(&sobel, backgroundColor, this->imageVectorCentered, this->imageVectorByConture);
    
    double maxFrequence = 30;
    double timeFactor = 1;
/*
    double A = 1;
    double omega = 10;
    double timeFactor = 0.01;
    double timeMax = 30;
    
    for (double t = 0.0; t <= timeMax; t+=timeFactor)
    {
        labels.push_back(t);
        complexTime.push_back(std::complex<double>(A * cos(((omega*t)+pow(t, 3.0))-2.0), 0));
    }

    labels.push_back(timeMax+timeFactor);*/

    WaveletResult result = this->morletWaveletService->calculate(complexTime, maxFrequence, timeFactor);

    // Add Diagram
    std::string tempName = this->generateFileName();
    this->diagram(complexTime, tempName, std::vector<double>(), "Inputsignal:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->diagram(result.waveletOutput, tempName, std::vector<double>(), "Selected Wavelet:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 420), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->heatMap(result.frequenceTime, std::vector<double>(), tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);

    /*
    tempName = this->generateFileName();
    this->diagram(result.bScoreVector, tempName, labels, "Best Score:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_1, Point2D(8, 520), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    */

    tempName = this->generateFileName();
    this->diagram(result.convolvedSignal, tempName, std::vector<double>(), "best Convolved Vector:");
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_1, Point2D(8, 520), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onFourierDiscriptor()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    FDResult result = this->discreteFourierDescriptorService->calculate(&img);

    // Add Sobelimage
    std::string tempName = this->generateFileName();
    result.sobelImage.save_png(tempName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Add Diagram of conture
    tempName = this->generateFileName();
    this->diagram(result.contourVector, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_1, Point2D(8, 520), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Add Diagram
    tempName = this->generateFileName();
    this->diagram(result.fequence, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onDiscreteFourierTransformationCV()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    DFTResult result = this->discreteFourierTransformationSerivceCV->calculate(fileName);

    std::string tempName = this->generateFileName();
    cv::imwrite(tempName.c_str(), result.spectrumMagnitude*255);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->diagram(result.radialProfile, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onWavelet()
{
    // Wavelet
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    this->waveletTransformCV->calculate(fileName);
}

void MyEventReceiver::onGaborFilter()
{
    // Gabor
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    std::vector<double> fequence = this->gaborServiceCV->calculate(fileName);

    std::string tempName = this->generateFileName();
    this->diagram(fequence, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onHOG()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // HOG
    /*cv::Mat image = cv::imread(fileName);
    this->hogService->process(image);

    auto hist = this->hogService->retrieve(cv::Rect(0, 0, image.cols, image.rows));

    //display_superimposed(image, this->hogService->get_vector_mask(2), "vector_mask");

    // magnitude
    fileName = this->generateFileName();
    display_superimposed(custom_normalization(this->hogService->get_magnitudes()), this->hogService->get_vector_mask(2), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    // orientation
    fileName = this->generateFileName();
    display_superimposed(custom_normalization(this->hogService->get_orientations()), this->hogService->get_vector_mask(2), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);*/

    std::vector<double> theVector = this->hogService->calculate(&img);
}

void MyEventReceiver::onGLCM()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // GLCM
    GLCMResult result = this->glcmService->calculate(&img);

    // Generate FileName
    fileName = this->generateFileName();
    result.getGlImage().save(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
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
}

void MyEventReceiver::onCompletedLbp()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // Sobel Image
    LbpHistogramResult result = this->completedLbpService->calculateLbpHistogram(&img, 8, 10);

    // Generate Diagram
    fileName = this->generateFileName();
    this->histogram(result.getLbpHistogram(), 5, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
    fileName = this->generateFileName();
    this->histogram(result.getUniformityHistogram(), 3, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onLbp()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // Sobel Image
    LbpHistogramResult result = this->lbpService->calculateLbpHistogram(&img, 8, 10);

    // Generate Diagram
    fileName = this->generateFileName();
    this->histogram(result.getLbpHistogram(), 5, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
    fileName = this->generateFileName();
    this->histogram(result.getUniformityHistogram(), 3, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onSdSf()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    // Sobel Image
    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);
    
    std::string sobelName = this->generateFileName();
    sobelImage.save(sobelName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Create SD-SF-Diagram
    std::map<std::string, int> distanceHistogram = this->sdSfService->calculateSdSf(&sobelImage);

    fileName = this->generateFileName();
    this->histogram(distanceHistogram, 4, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onHuMoment()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

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

        int length = sizeof(huMoments) / sizeof(double);
        for (int i = 0; i < length; i++)
        {
            std::wstring huString = this->stringSerivce->doubleToWString(huMoments[i]);
            this->graphicEngine->setGUIElementText(huMomentOpenCVMoments[i], huString.c_str());
        }
    }
    catch (cv::Exception e)
    {
        std::string message = e.what();
        int b = 0;
    }

    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);

    // Output the chart
    std::string sobelName = this->generateFileName();
    sobelImage.save(sobelName.c_str());

    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);

    double hu = this->huMomentsService->calculateHu1(&sobelImage);
    std::wstring huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_1, huString.c_str());

    hu = this->huMomentsService->calculateHu2(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_2, huString.c_str());

    hu = this->huMomentsService->calculateHu3(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_3, huString.c_str());

    hu = this->huMomentsService->calculateHu4(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_4, huString.c_str());

    hu = this->huMomentsService->calculateHu5(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_5, huString.c_str());

    hu = this->huMomentsService->calculateHu6(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_6, huString.c_str());

    hu = this->huMomentsService->calculateHu7(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_7, huString.c_str());
}

void MyEventReceiver::onDiscreteFourierTransformation()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());

    // Output the chart
    FDResult result = this->discreteFourierTransformationSerivce->calculate(&img, 2000);
    
    // Add sobel image
    std::string fileName = this->generateFileName();
    result.sobelImage.save_png(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Generate Diagram
    fileName = this->generateFileName();
    this->diagram(result.fequence, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onCalculateSuperPixels()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);

    CImg<unsigned char> img(cFile.c_str());
    SubregionResult result = this->superPixelService->calculateSuperPixelsAndSubregions(img, 50);

    std::string fileName = this->generateFileName();

    this->superPixelToImage(result.superPixelClusters, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    fileName = this->generateFileName();

    this->superPixelToImage(result.subregions, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onCalculateSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->sobelOperatorSerivce->getGradientImage(&img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

void MyEventReceiver::onCalculateImprovedSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->improvedSobelOperatorService->getGradientImage(img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3_0, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);
}

std::string MyEventReceiver::generateFileName()
{
    stringstream stream;
    std::string age_as_string;

    stream << this->tempFileIndex;
    stream >> age_as_string;

    std::string fileName = "temp";
    fileName += age_as_string;
    fileName += ".png";

    this->tempFileIndex++;

    return fileName;
}

void MyEventReceiver::removeTempFiles()
{
    std::vector<std::string> fileNames = this->directoryService->getFileNames(".");

    for(std::string fileName : fileNames)
    {
        if(this->stringSerivce->contains(fileName, "temp"))
        {
            std::remove(fileName.c_str());
        }
    }
}

void MyEventReceiver::onSelectFile(core::stringc fileName)
{
    this->onCreateImagePannel();
    
    CImg<unsigned char> img(fileName.c_str());
    
    std::wstring roiString = this->stringSerivce->intToWString(img.width()) + L" x " + this->stringSerivce->intToWString(img.height()) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ROI, roiString.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);
    std::wstring backgroundColorString = this->stringSerivce->doubleToWString(backgroundColor.r)+L"|"+this->stringSerivce->doubleToWString(backgroundColor.g) + L"|" + this->stringSerivce->doubleToWString(backgroundColor.b);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_BACKGROUND_COLOR, backgroundColorString.c_str());

    int defectPixels = this->geometricService->countDefectPixels(&img, backgroundColor);
    std::wstring defectPixelsString = this->stringSerivce->intToWString(defectPixels);
    std::wstring defectPixelsStringUnit = defectPixelsString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_AREA, defectPixelsStringUnit.c_str());

    double rotioRoiArea = defectPixels / ((double)img.width()) * ((double)img.height());
    std::wstring rotioRoiAreaString = this->stringSerivce->doubleToWString(rotioRoiArea);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_AREA_ROI, rotioRoiAreaString.c_str());

    double rotioWidthLength = ((double)img.width()) / ((double)img.height());
    std::wstring rotioWidthLengthString = this->stringSerivce->doubleToWString(rotioWidthLength);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, rotioWidthLengthString.c_str());

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
    
    std::wstring wFileName = this->stringSerivce->toWString(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(10, 10), wFileName.c_str(), GUI_ID_IMAGE_1_TAB);

    this->selectedFile = wFileName.c_str();
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

std::map<double, std::vector<double>> MyEventReceiver::toDoubleMap(std::map<double, std::vector<std::complex<double>>> a)
{
    std::map<double, std::vector<double>> result;
    std::map<double, std::vector<std::complex<double>>>::iterator it;
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