#include "KConsole.h"
#include <iostream>

#define PRINT(something) { std::cout << something; }
#define SET_ERROR_IF(condition) if (condition) printf("Error");
COORD top = { 0, 0 };

namespace k
{

KConsole::KConsole(int w_,int h_):cursorX(0),cursorY(0),consoleData(0),w(w_),h(h_),currentCharAttribute(0),cursorFollow(true),
	pConsoleDraw(0),pConsoleElements(0)
{
	aquireDefaultConsole();
	if (w > 1 && h > 1)
	{
		setConsoleWindowSize(w,h);
		setConsoleSize(w,h);
	}

	resize();
}

KConsole::~KConsole()
{
	deleteBuffers();
	if (pConsoleDraw)
	{
		delete pConsoleDraw;
		pConsoleDraw = 0;
	}
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
	if (consoleData)
	{
		free(consoleData);
		consoleData = 0;
	}

}

void KConsole::resize()
{
	deleteBuffers();
	createBuffers();
}

void KConsole::createBuffers()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SET_ERROR_IF(!GetConsoleScreenBufferInfo( hStdOut, &csbi ));
	w = csbi.dwSize.X;
	h = csbi.dwSize.Y;
	currentCharAttribute = csbi.wAttributes;

	consoleData = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*w * h);
 
	clear();
}

void KConsole::aquireDefaultConsole()
{
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	hStdIn = GetStdHandle( STD_INPUT_HANDLE );
	SET_ERROR_IF(hStdOut == INVALID_HANDLE_VALUE);
	SET_ERROR_IF(hStdIn == INVALID_HANDLE_VALUE);
}

void KConsole::setConsoleWindowSize(int w,int h)
{
	SMALL_RECT rect; 
    rect.Top = 0; 
    rect.Left = 0; 
    rect.Bottom = h - 1; 
    rect.Right = w - 1; 
    // Set Window Size 
	SetConsoleWindowInfo(hStdOut, true, &rect);
}

void KConsole::setConsoleSize(int w,int h)
{
	COORD coord;
	coord.X = w;
	coord.Y = h;
	SetConsoleScreenBufferSize(hStdOut, coord);
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
		consoleData[i].Attributes = color;
	}

}

void KConsole::clearCharBuffer(char ch)
{
//	unsigned long temp;
//	FillConsoleOutputCharacter(hStdOut,ch,w*h,top,&temp);

	for (int i=0;i<w*h;++i)
	{
		consoleData[i].Char.UnicodeChar = 0;
		consoleData[i].Char.AsciiChar = ch;
	}
}

void KConsole::clear()
{
	clearCharBuffer(' ');
	clearColorBuffer(DEFAULT_ATTRIBUTE);

	if (cursorFollow)
	{
		setCursorPosition(top.X,top.Y);
	}
}

void KConsole::gotoxy(int x,int y)
{
	cursorX = x;
	cursorY = y;
}

void KConsole::flush()
{
	COORD size = { w, h };
	SMALL_RECT rect = { top.X, top.Y, size.X, size.Y };
	if (!WriteConsoleOutput(hStdOut, consoleData, size, top, &rect))
	{
		printf("Error");
	}
	if (cursorFollow)
	{
		setCursorPosition(cursorX,cursorY);
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

void KConsole::setCursorPosition(int x,int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(hStdOut,c);
}

void KConsole::printEndLine()
{
	cursorX = 0;
	cursorY++;
}

void KConsole::setEcho(bool echo_)
{
	SetConsoleMode( hStdOut, echo_ ? 1 : 0 );
}

bool KConsole::readKey(char *out)
{
	bool pr;
	int repcnt;
	return readKeyExtended(out,&pr,&repcnt);
}

bool KConsole::readKeyExtended(char *out,bool *pressing,int *repeatCount)
{
	INPUT_RECORD inrec;
	dword count;

	FlushConsoleInputBuffer( hStdIn );

	ReadConsoleInput( hStdIn, &inrec, 1, &count );
//	BOOL fResult = ReadConsole(hStdIn,&r,1,&count,0);
//	while ((inrec.EventType != KEY_EVENT) || !inrec.Event.KeyEvent.bKeyDown);
//	DWORD f = GetLastError();

	if (count > 0)
	{
		if (inrec.EventType == KEY_EVENT)
		{
			*out = inrec.Event.KeyEvent.uChar.AsciiChar;
			*pressing = inrec.Event.KeyEvent.bKeyDown != 0;
			*repeatCount = (int)inrec.Event.KeyEvent.wRepeatCount;
			return true;
		}
	}

	*out = 0;
	return false;
}

void KConsole::printChar(char ch)
{
	if (ch == '\n')
	{
		printEndLine();
	}
	else
	{
		CHAR_INFO chInfo;
		chInfo.Char.UnicodeChar = 0;
		chInfo.Char.AsciiChar = ch;
		chInfo.Attributes = currentCharAttribute;

		int t = cIndex();

		consoleData[cIndex()] = chInfo;

		cursorX++;
	}
}

void KConsole::printCharxy(char ch,int x,int y)
{
	gotoxy(x,y);
	printChar(ch);
}

}
