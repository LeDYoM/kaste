#ifndef __KCONSOLEELEMENTS_H__
#define __KCONSOLEELEMENTS_H__

#include "KConsoleTypes.h"
#include "KAttributes.h"
#include <vector>
#include <string>

namespace k
{
	class KConsole;

typedef struct _GUIData
{
	CharAttribute lineBackground;
	CharAttribute background;
	CharAttribute highlightText;
	CharAttribute normalText;

	_GUIData()
	{
		lineBackground = DEFAULT_ATTRIBUTE;
		background = DEFAULT_ATTRIBUTE;
		highlightText = DEFAULT_ATTRIBUTE;
		normalText = DEFAULT_ATTRIBUTE;
	}
} GUIData;

typedef struct _MenuData
{
	int x;
	int y;
	std::vector<std::string> str;
	int lBorder;
	int rBorder;
	int tBorder;
	int bBorder;
	int optionSelected;

	_MenuData()
	{
		x = 0;
		y = 0;
		lBorder = rBorder = tBorder = bBorder = 1;
		optionSelected = 0;
	}
} MenuData;

class KConsoleElements
{
public:
	KConsoleElements(KConsole *pConsole_);
	virtual ~KConsoleElements();

	bool drawMenu(MenuData &data);
	GUIData guiData;
private:
	KConsole *pConsole;
};

}

#endif
