#include "MyEventReceiver.h"
/*
std::string enStr[]{
    stringify(GUI_ID_IMAGE),
    stringify(GUI_ID_IMAGE_1),
    stringify(GUI_ID_IMAGE_2),
    stringify(GUI_ID_CHECKBOX_UNKNOWN),
    stringify(GUI_ID_CHECKBOX_SOBEL),
    stringify(GUI_ID_CHECKBOX_IMPROVED_SOBEL),
    stringify(GUI_ID_CHECKBOX_SUPERPIXELS),
    stringify(GUI_ID_BUTTON_CACLULATE),
    stringify(GUI_ID_BUTTON_CHOOSE_FILE),
    stringify(GUI_ID_DIALOG_CHOOSE_FILE),
};*/

MyEventReceiver::MyEventReceiver(GraphicEngineExtended* graphicEngine, SuperPixelService* superPixelService, ClassicSobelOperatorService* sobelOperatorSerivce, ImprovedSobelOperatorService* improvedSobelOperatorService, GeometricService* geometricService, StringSerivce* stringSerivce)
{
    this->graphicEngine = graphicEngine;
    this->superPixelService = superPixelService;
    this->sobelOperatorSerivce = sobelOperatorSerivce;
    this->improvedSobelOperatorService = improvedSobelOperatorService;
    this->geometricService = geometricService;

    this->stringSerivce = stringSerivce;

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
                this->onResetImages();

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
                    
            }
            else if (id == GUI_ID_BUTTON_CHOOSE_FILE)
            {
                this->graphicEngine->addFileOpenDialog(GUI_ID_DIALOG_CHOOSE_FILE, L"..\\AnomalyGeneration\\testdata");
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
            this->graphicEngine->resetMethodCheckBoxs();
            this->graphicEngine->setGUIElementChecked(id, true);

            return true;

        default:
            return this->setForm(id);
        }
    }

    return false;
}

void MyEventReceiver::onCalculateSuperPixels()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);

    CImg<unsigned char> img(cFile.c_str());
    SubregionResult result = this->superPixelService->calculateSuperPixelsAndSubregions(img, 50);

    std::string fileName = this->generateFileName();

    this->superPixelToImage(result.superPixelClusters, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(220, 10), this->stringSerivce->toWString(fileName).c_str());

    fileName = this->generateFileName();

    this->superPixelToImage(result.subregions, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(220, 250), this->stringSerivce->toWString(fileName).c_str());
}

void MyEventReceiver::onCalculateSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->sobelOperatorSerivce->getGradientImage(img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(220, 10), this->stringSerivce->toWString(tempFileName).c_str());
}

void MyEventReceiver::onCalculateImprovedSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->improvedSobelOperatorService->getGradientImage(img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(220, 10), this->stringSerivce->toWString(tempFileName).c_str());
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

void MyEventReceiver::onSelectFile(core::stringc fileName)
{
    if (!this->selectedFile.empty() && this->graphicEngine->exists(GUI_ID_IMAGE))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE);
        this->selectedFile = L"";
    }
    
    CImg<unsigned char> img(fileName.c_str());
    
    std::wstring roiString = this->stringSerivce->intToWString(img.width()) + L" x " + this->stringSerivce->intToWString(img.height()) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ROI, roiString.c_str());

    int blackPixels = this->geometricService->countBlackPixels(img);
    std::wstring blackPixelsString = this->stringSerivce->intToWString(blackPixels);
    std::wstring blackPixelsStringUnit = blackPixelsString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_AREA, blackPixelsStringUnit.c_str());

    double rotioRoiArea = ((double)img.width()) * ((double)img.height()) / ((double)blackPixels);
    std::wstring rotioRoiAreaString = this->stringSerivce->doubleToWString(rotioRoiArea);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_AREA_ROI, rotioRoiAreaString.c_str());

    double rotioWidthLength = ((double)img.width()) / ((double)img.height());
    std::wstring rotioWidthLengthString = this->stringSerivce->doubleToWString(rotioWidthLength);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, rotioWidthLengthString.c_str());

    int scope = this->geometricService->calculateScope(img);
    std::wstring scropWithUnit = this->stringSerivce->doubleToWString(scope) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SCOPE, scropWithUnit.c_str());

    Point2D defectFocus = this->geometricService->calculateDefectFocus(img);
    std::wstring defectFocusString = L"(" + this->stringSerivce->doubleToWString(defectFocus.x) + L"px/" + this->stringSerivce->doubleToWString(defectFocus.y)+L"px)";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_DEFECT_FOCUS, defectFocusString.c_str());
    
    std::wstring wFileName = this->stringSerivce->toWString(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE, Point2D(10, 10), wFileName.c_str());

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

void MyEventReceiver::onResetImages()
{
    if(this->graphicEngine->exists(GUI_ID_IMAGE_1))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_1);
    }

    if(this->graphicEngine->exists(GUI_ID_IMAGE_2))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2);
    }
}