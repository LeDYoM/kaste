#ifndef __KCONSOLE_H__
#define __KCONSOLE_H__

#include <string>

#define DEFAULT_FOREGROUND_COLOR 7
#define DEFAULT_BACKGROUND_COLOR 0

#include "KConsoleTypes.h"
#include "KConsoleDraw.h"
#include "KConsoleElements.h"

namespace k
{

class KConsole
{
public:
	KConsole(int w_=0,int h_=0);
	virtual ~KConsole();

	void aquireDefaultConsole(void);
	void clear();
	void gotoxy(int x,int y);

	void flush();
	void print(const std::string &str);
	void printxy(const std::string &str,int x,int y);
	void printChar(char ch);
	void printCharxy(char ch,int x,int y);
	void printEndLine();
	void setCursorPosition(int x,int y);

	const KConsole &operator<<(const std::string &str);

	void setConsoleWindowSize(int w,int h);
	void setConsoleSize(int w,int h);

	void resize();

	KConsoleDraw *getConsoleDraw();
	KConsoleElements *getConsoleElements();

	inline void setCharAttribute(CharAttribute cha) { currentCharAttribute = cha; }
	inline CharAttribute getCharAttribute() const { return currentCharAttribute; }

private:
	int cursorX;
	int cursorY;
	int w;
	int h;

	bool cursorFollow;

	inline int index(int x,int y) { return (y*w)+x; }
	inline int cIndex() { return index(cursorX,cursorY); }
	void clearColorBuffer(int color);
	void clearCharBuffer(char ch);
	void createBuffers();
	void deleteBuffers();

	hndl hStdOut;
	charInfo *consoleData;
	CharAttribute currentCharAttribute;

	KConsoleDraw *pConsoleDraw;
	KConsoleElements *pConsoleElements;
};

}

#endif
