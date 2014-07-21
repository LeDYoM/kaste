#ifndef __KCONSOLEDRAW_H__
#define __KCONSOLEDRAW_H__

namespace k
{
	class KConsole;

typedef enum _LineMode
{
	Line_Simple = 0,
	Line_Double = 1,
	Line_Char
} LineMode;

typedef struct _LineData
{
	LineMode lMode;
	char ch;

	_LineData(LineMode mode = Line_Simple,char ch_=0)
	{
		lMode = mode;
		ch = ch_;
	}
} LineData;

class KConsoleDraw
{
public:
	KConsoleDraw(KConsole *pConsole_);
	virtual ~KConsoleDraw();

	void drawQuad(int x,int y,int lenx,int leny,const LineData &ld);
	void drawLineX(int x,int len,int y,char ch);
	void drawLineY(int y,int len,int x,char ch);

private:
	KConsole *pConsole;
};

}

#endif
