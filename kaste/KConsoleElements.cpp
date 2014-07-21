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

void KConsoleElements::drawMenu(MenuData &data)
{
	unsigned t(0);
	for (std::vector<std::string>::iterator it = data.str.begin();it < data.str.end(); ++it)
	{
		if (it->length() > t)
		{
			t = it->length();
		}
	}

	LineData ld(Line_Char,65);
	pConsole->getConsoleDraw()->drawQuad(data.x,data.y,t+2+data.lBorder+data.rBorder,(data.str.size()*2)+1+data.tBorder+data.bBorder,ld);
	t = 0;
	for (std::vector<std::string>::iterator it = data.str.begin();it < data.str.end(); ++it,++t)
	{
		pConsole->printxy(*it,data.x+1+data.lBorder,data.y+(t*2)+1+data.tBorder);
	}
}

}
