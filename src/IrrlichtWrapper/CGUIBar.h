#ifndef CGUIBar_H
#define CGUIBar_H

#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace core;

class CGUIBar : public gui::IGUIElement 
{
private:
	video::IVideoDriver* driver;
	int x1Bar, y1Bar, x2Bar, y2Bar;
	int barSize;
	int   maxBarValue; //bar size
	int deltaBar;   //interpolation
	double BarValue;   //current bar value
	stringw m_Name;
	video::ITexture* BarTexture;

public:

	CGUIBar(int id, int x1, int y1, int x2, int y2, int maxValue, video::ITexture* texture, stringw name, gui::IGUIEnvironment* environment, video::IVideoDriver* driver, gui::IGUIElement* parent); //constructor
	~CGUIBar(); //destructor :O

	virtual void draw();

	void renderGUIBars(video::IVideoDriver* driver); //render the bars, must be called AFTER the 3D draw, or it  wont show
	void setBarValue(s32 healthValue); //change bar values
	void changeValueBy(s32 Value);
	int getBarValue();
	stringw getName() {return m_Name;}
}; 

#endif