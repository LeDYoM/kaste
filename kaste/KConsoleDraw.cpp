#include "KConsole.h"
#include "KConsoleDraw.h"

namespace k
{

KConsoleDraw::KConsoleDraw(KConsole *pConsole_):pConsole(pConsole_)
{
}


KConsoleDraw::~KConsoleDraw()
{
}

void KConsoleDraw::drawLineX(int x,int len,int y,char ch)
{
	std::string tmp;

	for (int i=x;i<(x+len);++i)
	{
		tmp += ch;
	}
	pConsole->printxy(tmp,x,y);
}

void KConsoleDraw::drawLineY(int y,int len,int x,char ch)
{
	for (int i=y;i<(y+len);++i)
	{
		pConsole->printCharxy(ch,x,i);
	}
}

void KConsoleDraw::drawQuad(int x,int y,int lenx,int leny,const LineData &ld)
{
	unsigned char chX  = ld.ch, chY = ld.ch, chX0Y0 = ld.ch, chX1Y0 = ld.ch, chX0Y1 = ld.ch, chX1Y1 = ld.ch;

	switch (ld.lMode)
	{
		case Line_Simple:
			chY = 179;
			chX = 196;
			chX0Y0 = 218;
			chX0Y1 = 192;
			chX1Y0 = 191;
			chX1Y1 = 217;
			break;
		case Line_Double:
			chY = 186;
			chX = 205;
			chX0Y0 = 201;
			chX0Y1 = 200;
			chX1Y0 = 187;
			chX1Y1 = 188;
			break;
        case Line_Char:
        default:
            break;
	}

	drawLineX(x+1,lenx-2,y,chX);
	drawLineY(y+1,leny-2,x,chY);
	drawLineY(y+1,leny-2,(x+(lenx-1)),chY);
	drawLineX(x+1,lenx-2,(y+(leny-1)),chX);

	// Now, draw the four borders.
	pConsole->printCharxy(chX0Y0,x,y);
	pConsole->printCharxy(chX1Y0,(x+lenx)-1,y);
	pConsole->printCharxy(chX0Y1,x,(y+leny)-1);
	pConsole->printCharxy(chX1Y1,(x+lenx)-1,(y+leny)-1);

}

}
