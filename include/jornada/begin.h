#ifndef UNDER_CE
#define UNDER_CE
#endif
#ifndef JORNADA_SH3
#define JORNADA_SH3 0
#endif
#ifndef ARM
#define ARM
#endif
#ifndef _ARM_
#define _ARM_
#endif
#ifndef ARMV4
#define ARMV4
#endif
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __cdecl
#define __cdecl
#endif

#ifndef JORNADA_CE
#define JORNADA_CE 3
#endif
#ifndef JORNADA_WCE
#define JORNADA_WCE 300
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#pragma push_macro("_WIN32_WCE")
#undef _WIN32_WCE
#define _WIN32_WCE 0x300
