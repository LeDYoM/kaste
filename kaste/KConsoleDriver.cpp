#include "KConsoleDriver.h"

namespace k
{

KConsoleDriver::KConsoleDriver():hStdOut(0),hStdIn(0)
{
}


KConsoleDriver::~KConsoleDriver()
{
}

bool KConsoleDriver::aquireDefaultConsole()
{
#ifdef USE_M_API
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	hStdIn = GetStdHandle( STD_INPUT_HANDLE );
	return hStdOut != INVALID_HANDLE_VALUE && hStdIn != INVALID_HANDLE_VALUE;
#endif
	return true;
}

bool KConsoleDriver::getConsoleSize(int *w,int *h)
{
#ifdef USE_M_API
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo( hStdOut, &csbi ))
	{
		*w = (int)csbi.dwSize.X;
		*h = (int)csbi.dwSize.Y;
		return true;
	}
	return false;
#else
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    w = ws.ws_col;
    h = ws.ws_row;
	return true;
#endif
}

void KConsoleDriver::setConsoleWindowSize(int w,int h)
{
#ifdef USE_M_API
	SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = h - 1;
    rect.Right = w - 1;
    // Set Window Size
	SetConsoleWindowInfo(hStdOut, true, &rect);
#endif
}

void KConsoleDriver::setConsoleSize(int w,int h)
{
	coord coord;
	coord.X = w;
	coord.Y = h;
#ifdef USE_M_API
	SetConsoleScreenBufferSize(hStdOut, coord);
#endif
}

bool KConsoleDriver::flushCharacters(int fromX,int fromY,int toX,int toY,const char *characters)
{
#ifdef USE_M_API
	coord top = { (SHORT)fromX, (SHORT)fromY };
	dword result;
	if (!WriteConsoleOutputCharacter(hStdOut, characters, toX * toY, top, &result))
	{
		return false;
	}
#endif
	return true;
}

bool KConsoleDriver::flushAttributes(int fromX,int fromY,int toX,int toY,const CharAttribute *attributes)
{
#ifdef USE_M_API
	coord top = { (SHORT)fromX, (SHORT)fromY };
	dword result;
	if (!WriteConsoleOutputAttribute(hStdOut, attributes, toX * toY, top, &result))
	{
		return false;
	}
#endif
	return true;
}

void KConsoleDriver::setCursorPosition(int x,int y)
{
	coord c;
	c.X = x;
	c.Y = y;
#ifdef USE_M_API
	SetConsoleCursorPosition(hStdOut,c);
#endif
}

void KConsoleDriver::setEcho(bool echo)
{
#ifdef USE_M_API
	SetConsoleMode( hStdOut, echo ? 1 : 0 );
#endif
}

bool KConsoleDriver::readKeyExtended(char *out,bool *pressing,int *repeatCount)
{
#ifdef USE_M_API
	INPUT_RECORD inrec;
	dword count;

	FlushConsoleInputBuffer( hStdIn );
	ReadConsoleInput( hStdIn, &inrec, 1, &count );

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
#endif
	*out = 0;
	return false;
}

}
