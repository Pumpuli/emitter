#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef _UNICODE
	#define _UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WIN32_IE
	#undef _WIN32_IE
#endif
#define _WIN32_IE 0x0400

#endif
