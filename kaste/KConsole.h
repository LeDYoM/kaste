#ifndef __KCONSOLE_H__
#define __KCONSOLE_H__

#include <string>

#include "KConsoleTypes.h"
#include "KAttributes.h"
#include "KConsoleDraw.h"
#include "KConsoleElements.h"
#include "KConsoleDriver.h"

namespace k
{

class KConsole
{
public:
	KConsole(int w_=0,int h_=0);
	virtual ~KConsole();

	void clear();
	void gotoxy(int x,int y);

	void flush();
	void print(const std::string &str);
	void printxy(const std::string &str,int x,int y);
	void printChar(char ch);
	void printCharxy(char ch,int x,int y);
	void printEndLine();
	bool readKey(char *out);

	const KConsole &operator<<(const std::string &str);

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

	inline int index(int x,int y) const { return (y*w)+x; }
	inline int cIndex() const { return index(cursorX,cursorY); }
	void clearColorBuffer(int color);
	void clearCharBuffer(char ch);
	void createBuffers();
	void deleteBuffers();

	char *characterData;
	CharAttribute *attributeData;
	CharAttribute currentCharAttribute;

	KConsoleDraw *pConsoleDraw;
	KConsoleElements *pConsoleElements;
	KConsoleDriver *pConsoleDriver;
};

}

#endif
