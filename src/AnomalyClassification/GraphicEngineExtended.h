#ifndef GraphicEngineExtended_H
#define GraphicEngineExtended_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "../IrrlichtWrapper/GraphicEngine.h"

#include "StringSerivce.h"
#include "CGUIFileSelector.h"

class GraphicEngineExtended : public GraphicEngine
{
private:
	StringSerivce* stringSerivce;
	
	std::vector<int> checkboxIds;
	std::map<int, std::vector<int>> checkboxIdsByWindow;

public:
	GraphicEngineExtended(StringSerivce* stringSerivce);

	virtual void addCheckbox(int id, Point2D position, const wchar_t* text, bool checked = false, int parentId = -1);
	virtual void resetCheckBoxs();
	virtual void resetCheckBoxsByWindowId(int parentId);

	virtual void addFileOpenDialog(int id, std::wstring startDir);
	virtual std::wstring getSelectedFile(int id);
	virtual void setVisibility(int id, bool visibile);

	virtual bool exists(int id);
	virtual void forget(int id);
};

#endif