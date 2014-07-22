#include <stdio.h>
#include "KConsole.h"

int main(int argc, char* argv[])
{
	k::KConsole kc(80,25);

//	kc.print("safsaf");

//	kc.getConsoleDraw()->drawQuad(1,1,10,10);
	k::MenuData md;
	md.str.push_back("Element1");
	md.str.push_back("Element2");
	md.x = 2;
	md.y = 1;
	while (!kc.getConsoleElements()->drawMenu(md)) { kc.flush(); }
	kc.flush();
	return 0;
}

