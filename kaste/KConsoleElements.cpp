#include "KConsoleElements.h"
#include "KConsole.h"

namespace k
{

KConsoleElements::KConsoleElements(KConsole *pConsole_):pConsole(pConsole_)
{
}


KConsoleElements::~KConsoleElements()
{
}

bool KConsoleElements::drawMenu(MenuData &data)
{
	guiData.highlightText = 1;
	unsigned t(0);
	for (std::vector<std::string>::iterator it = data.str.begin();it < data.str.end(); ++it)
	{
		if (it->length() > t)
		{
			t = it->length();
		}
	}

	LineData ld(Line_Simple);

	pConsole->setCharAttribute(guiData.lineBackground);
	pConsole->getConsoleDraw()->drawQuad(data.x,data.y,t+2+data.lBorder+data.rBorder,(data.str.size()*2)+1+data.tBorder+data.bBorder,ld);

	int ind = 0;
	for (std::vector<std::string>::iterator it = data.str.begin();it < data.str.end(); ++it,++ind)
	{
		pConsole->setCharAttribute((ind == data.optionSelected) ? guiData.highlightText : guiData.normalText);
		pConsole->printxy(*it,data.x+1+data.lBorder,data.y+(ind*2)+1+data.tBorder);
	}

	char out;
	return pConsole->readKey(&out);
}

}
