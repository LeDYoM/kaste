#ifndef __KCONSOLETYPES_H__
#define __KCONSOLETYPES_H__

#ifdef WIN32
	#include <Windows.h>
	typedef HANDLE hndl;
	typedef CHAR_INFO charInfo;
	typedef WORD word;
	typedef DWORD dword;

	typedef word CharAttribute;
#endif


#endif
