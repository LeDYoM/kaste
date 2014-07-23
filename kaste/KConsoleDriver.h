#ifndef __KCONSOLEDRIVER_H__
#define __KCONSOLEDRIVER_H__

#include "KConsoleTypes.h"

namespace k
{

class KConsoleDriver
{
public:
	KConsoleDriver();
	virtual ~KConsoleDriver();

	bool aquireDefaultConsole();
	bool getConsoleSize(int *w,int *h);

	void setConsoleWindowSize(int w,int h);
	void setConsoleSize(int w,int h);

	bool flushCharacters(int fromX,int fromY,int toX,int toY,const char *characters);
	bool flushAttributes(int fromX,int fromY,int toX,int toY,const CharAttribute *attributes);

	void setCursorPosition(int x,int y);
	void setEcho(bool echo);

	bool readKeyExtended(char *out,bool *pressing,int *repeatCount);
private:
	hndl hStdOut;
	hndl hStdIn;

};

}

#endif
