#include "MyEventReceiver.h"

std::string enStr[]{
    stringify(GUI_ID_IMAGE),
    stringify(GUI_ID_CHECKBOX_UNKNOWN),
    stringify(GUI_ID_CHECKBOX_SUPERPIXELS),
    stringify(GUI_ID_BUTTON_CACLULATE),
    stringify(GUI_ID_BUTTON_CHOOSE_FILE),
    stringify(GUI_ID_DIALOG_CHOOSE_FILE),
};

MyEventReceiver::MyEventReceiver(GraphicEngineExtended* graphicEngine, SuperPixelService* superPixelService, StringSerivce* stringSerivce)
{
    this->graphicEngine = graphicEngine;
    this->superPixelService = superPixelService;

    this->stringSerivce = stringSerivce;

    this->facet = NULL;
    this->context = NULL;

    this->isRunning = false;
    this->isAbbord = false;

    this->progressSymbol = '-';
    this->selectedFile = L"";
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
                if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SUPERPIXELS))
                {
                    this->onCalculateSuperPixels();
                }
            }
            else if (id == GUI_ID_BUTTON_CHOOSE_FILE)
            {
                graphicEngine->setVisibility(GUI_ID_DIALOG_CHOOSE_FILE, true);
            }

            return true;
        case EGET_FILE_SELECTED:
            {
            CGUIFileSelector* dialog = (CGUIFileSelector*)event.GUIEvent.Caller;
            this->onSelectFile(dialog->getFileName());
        //case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
            //this->graphicEngine->removeElement(GUI_ID_DIALOG_CHOOSE_FILE);
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

    superPixelToImage(result.superPixelClusters, img.width(), img.height(), "temp.png");
    this->graphicEngine->addImage(0, Point2D(220, 10), L"temp.png");

    superPixelToImage(result.subregions, img.width(), img.height(), "temp1.png");
    this->graphicEngine->addImage(0, Point2D(220, 250), L"temp1.png");
}

void MyEventReceiver::onSelectFile(core::stringc fileName)
{
    if (!this->selectedFile.empty())
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE);
    }

    //this->selectedFile = this->graphicEngine->getSelectedFile(GUI_ID_DIALOG_CHOOSE_FILE);
    //this->graphicEngine->addImage(GUI_ID_IMAGE, Point2D(10, 10), this->selectedFile.c_str());

    this->selectedFile = this->stringSerivce->toWString(fileName.c_str());
    //this->graphicEngine->addImage(GUI_ID_IMAGE, Point2D(10, 10), this->selectedFile.c_str());
}

void MyEventReceiver::superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned int> bg(width, height, size_z, size_c, 255);

    for (int k = 0; k < pixelCluster.size(); k++)
    {
        const unsigned char(&color)[3] = { (unsigned char)(k * 75), (unsigned char)(k * 75), (unsigned char)(k * 75) };

        for (int i = 0; i < pixelCluster[k].size(); i++)
        {
            SuperPixelEntry entry = pixelCluster[k][i];
            bg.draw_point(entry.position.x, entry.position.y, color);
        }
    }

    bg.save_png(tempPath.c_str());
}