#include "CGUIBar.h"

CGUIBar::CGUIBar(int id, int x1, int y1, int x2, int y2, int maxValue, video::ITexture* texture, stringw name, gui::IGUIEnvironment* environment, video::IVideoDriver* driver, gui::IGUIElement* parent) : 
	gui::IGUIElement(irr::gui::EGUI_ELEMENT_TYPE::EGUIET_IMAGE, environment, parent, (s32)id, rect<s32>(x1, y1, x2, y2))
{
   //class constructor
       
   //bars size
   x1Bar = x1;
   y1Bar = y1;
   x2Bar = x2;
   y2Bar = y2;

   barSize = (x2Bar-3) - (x1Bar+3);
   //max bar values
   maxBarValue = maxValue;

   //current bar values
   BarValue = maxValue;

   deltaBar = maxValue;

   //bar name (asociated with skill/ability name)
   m_Name = name;

   //texture
   BarTexture = texture;
   this->driver = driver;
} 

CGUIBar::~CGUIBar()
{

}

void CGUIBar::draw()
{
	if ( isVisible() && this->driver != NULL)
	{
		this->renderGUIBars(this->driver);
	}
}

void CGUIBar::renderGUIBars(video::IVideoDriver* driver){

   double delta; //status bar variation
   const core::dimension2d<u32>& screenSize = this->driver->getScreenSize();

   double x=17; //spell bar position
   double y=35;

        //here is some cool stuff, it changes the bar value from X to Y smoothly
   if ((int)deltaBar != (int)BarValue){
      delta = BarValue - deltaBar;
      if (delta > 0)
         BarValue -= 0.2;
      if (delta < 0)
         BarValue += 0.2;
   }
       
 
   //another cool stuff,  it draws the bar according to its value (green for high, decreasing to yellow till red), and some others rectangles for a cool look
	if(BarTexture)
	{
		driver->draw2DImage(BarTexture, core::position2d<s32>(x1Bar-50, y1Bar-29), core::rect<s32>(0,0,605,94), 0, video::SColor(255,255,255,255), true);
	}

	driver->draw2DRectangle(video::SColor(255, 100, 100, 100), core::rect<s32>(x1Bar, y1Bar, x2Bar, y2Bar));

	driver->draw2DRectangle(video::SColor(255, 125, 125, 125), core::rect<s32>(x1Bar+1, y1Bar+1, x2Bar-1, y2Bar-1));

	driver->draw2DRectangle(video::SColor(255, 150, 150, 150), core::rect<s32>(x1Bar+3, y1Bar+3, x2Bar-3, y2Bar-3));

	driver->draw2DRectangle(core::rect<s32>(x1Bar+3, y1Bar+3, x1Bar+3+(s32)(barSize*BarValue/maxBarValue), y2Bar-3),

						video::SColor(255, (s32)(255-BarValue*(255/maxBarValue)), (s32)(BarValue*(255/maxBarValue)), 0),

						video::SColor(255, (s32)(255-BarValue*(255/maxBarValue)), (s32)(BarValue*(255/maxBarValue)), 0),

						video::SColor(255, 180, 180, 0),

						video::SColor(255, 180, 180, 0));

} 

void CGUIBar::setBarValue(s32 Value)
{
   deltaBar = (int)Value;
}

int CGUIBar::getBarValue()
{
   return deltaBar;
}

void CGUIBar::changeValueBy(s32 Value)
{
   deltaBar += (int)Value;
   if (deltaBar < 0)
   {
	   deltaBar = 0;
   }
   if (deltaBar > maxBarValue)
   {
	   deltaBar = maxBarValue;
   }
}