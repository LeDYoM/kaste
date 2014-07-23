#ifndef __KCONSOLETYPES_H__
#define __KCONSOLETYPES_H__

#ifdef WIN32
	#define USE_M_API
#endif

#ifdef USE_M_API
	#include <Windows.h>
	typedef HANDLE hndl;
	typedef WORD word;
	typedef DWORD dword;

	typedef word CharAttribute;
	typedef COORD coord;
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termio.h>
#include <err.h>	/* err */
#include <fcntl.h>	/* open */
#include <stdio.h>	/* printf */
#include <unistd.h>	/* close */
    typedef void* hndl;
    typedef unsigned short word;
    typedef unsigned long dword;
    typedef word CharAttribute;

	typedef struct _COORD {
	    short X;
	    short Y;
	} COORD;
	typedef COORD coord;

#endif


#endif
