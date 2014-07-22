#ifndef __KCONSOLETYPES_H__
#define __KCONSOLETYPES_H__

#ifdef WIN32
	#include <Windows.h>
	typedef HANDLE hndl;
	typedef CHAR_INFO charInfo;
	typedef WORD word;
	typedef DWORD dword;

	typedef word CharAttribute;
	typedef COORD coord;
#else
    #include <termios.h>
    typedef void* hndl;
    typedef unsigned short word;
    typedef unsigned long dword;
    typedef word CharAttribute;

    typedef struct _CHAR_INFO
    {
        union {
            unsigned short UnicodeChar;
            char AsciiChar;
        } Char;
        word Attributes;
    } CHAR_INFO;
	typedef CHAR_INFO charInfo;

	typedef struct _COORD {
	    short X;
	    short Y;
	} COORD;
	typedef COORD coord;

#endif


#endif
