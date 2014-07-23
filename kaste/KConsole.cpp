#include "KConsole.h"
#include <iostream>
#include <stdlib.h>

#define PRINT(something) { std::cout << something; }
#define SET_ERROR_IF(condition) if (condition) PRINT("Error");
#define FREE(thing) if (thing) { free(thing); thing = 0; }
#define KDELETE(thing) if (thing) { delete thing; thing = 0; }

coord top = { 0, 0 };

namespace k
{

KConsole::KConsole(int w_,int h_):cursorX(0),cursorY(0),w(w_),h(h_),
    cursorFollow(true),characterData(0),attributeData(0),currentCharAttribute(0),pConsoleDraw(0),pConsoleElements(0),pConsoleDriver(0)
{
	pConsoleDriver = new KConsoleDriver();
	pConsoleDriver->aquireDefaultConsole();
	if (w > 1 && h > 1)
	{
		pConsoleDriver->setConsoleWindowSize(w,h);
		pConsoleDriver->setConsoleSize(w,h);
	}

	resize();
}

KConsole::~KConsole()
{
	deleteBuffers();
	KDELETE(pConsoleDraw);
	KDELETE(pConsoleElements);
}

KConsoleDraw *KConsole::getConsoleDraw()
{
	if (!pConsoleDraw)
	{
		pConsoleDraw = new KConsoleDraw(this);
	}
	return pConsoleDraw;
}

KConsoleElements *KConsole::getConsoleElements()
{
	if (!pConsoleElements)
	{
		pConsoleElements = new KConsoleElements(this);
	}
	return pConsoleElements;
}

void KConsole::deleteBuffers()
{
	FREE(characterData);
	FREE(attributeData);
}

void KConsole::resize()
{
	deleteBuffers();
	createBuffers();
}

void KConsole::createBuffers()
{
	pConsoleDriver->getConsoleSize(&w,&h);
	currentCharAttribute = DEFAULT_ATTRIBUTE;

	characterData = (char*)malloc(sizeof(char)*w*h);
	attributeData = (CharAttribute*)malloc(sizeof(CharAttribute)*w*h);

	clear();
}

const KConsole &KConsole::operator<<(const std::string &str)
{
	print(str);
	return *this;
}

void KConsole::clearColorBuffer(int color)
{
//	unsigned long temp;
//	FillConsoleOutputAttribute(hStdOut,color,w*h,top,&temp);
	for (int i=0;i<w*h;++i)
	{
		attributeData[i] = (CharAttribute)color;
	}
}

void KConsole::clearCharBuffer(char ch)
{
//	unsigned long temp;
//	FillConsoleOutputCharacter(hStdOut,ch,w*h,top,&temp);

	for (int i=0;i<w*h;++i)
	{
		characterData[i] = ch;
	}
}

void KConsole::clear()
{
	clearCharBuffer(' ');
	clearColorBuffer(DEFAULT_ATTRIBUTE);

	if (cursorFollow)
	{
		pConsoleDriver->setCursorPosition(top.X,top.Y);
	}
}

void KConsole::gotoxy(int x,int y)
{
	cursorX = x;
	cursorY = y;
}

void KConsole::flush()
{
	pConsoleDriver->flushCharacters(0,0,w,h,characterData);
	pConsoleDriver->flushAttributes(0,0,w,h,attributeData);

	if (cursorFollow)
	{
		pConsoleDriver->setCursorPosition(cursorX,cursorY);
	}
}

void KConsole::printxy(const std::string &str,int x,int y)
{
	gotoxy(x,y);
	print(str);
}

void KConsole::print(const std::string &str)
{
	for (size_t i=0;i<str.length();++i)
	{
		printChar(str[i]);
	}
}

void KConsole::printEndLine()
{
	cursorX = 0;
	cursorY++;
}

bool KConsole::readKey(char *out)
{
	bool pr;
	int repcnt;
	return pConsoleDriver->readKeyExtended(out,&pr,&repcnt);
}

void KConsole::printChar(char ch)
{
	if (ch == '\n')
	{
		printEndLine();
	}
	else
	{
		int index = cIndex();
		characterData[index] = ch;
		attributeData[index] = currentCharAttribute;
		cursorX++;
	}
}

void KConsole::printCharxy(char ch,int x,int y)
{
	gotoxy(x,y);
	printChar(ch);
}

}
