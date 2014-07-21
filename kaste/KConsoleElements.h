#ifndef __KCONSOLEELEMENTS_H__
#define __KCONSOLEELEMENTS_H__

#include <vector>

namespace k
{
	class KConsole;

typedef struct _MenuData
{
	int x;
	int y;
	std::vector<std::string> str;
	int lBorder;
	int rBorder;
	int tBorder;
	int bBorder;

	_MenuData()
	{
		x = 0;
		y = 0;
		lBorder = rBorder = tBorder = bBorder = 1;
	}
} MenuData;

class KConsoleElements
{
public:
	KConsoleElements(KConsole *pConsole_);
	virtual ~KConsoleElements();

	void drawMenu(MenuData &data);

private:
	KConsole *pConsole;
};

}

#endif
