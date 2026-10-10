#ifndef JORNADA_WRAPPED_WINDOWS_H
#define JORNADA_WRAPPED_WINDOWS_H

#ifdef JORNADA_INSIDE
#include_next <windows.h>
#ifndef RC_INVOKED
#include <stdint.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>
#include <time.h>
#include <windbase.h>
#if JORNADA_WCE == 101
#include <windowsx.h>
#endif
#if JORNADA_CE >= 2 || JORNADA_WCE == 101
#include <tchar.h>
#endif
#endif
#include <jornada/extras.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/windows.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <windows.h>
#ifndef RC_INVOKED
#include <stdint.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>
#include <time.h>
#include <windbase.h>
#if JORNADA_WCE == 101
#include <windowsx.h>
#endif
#if JORNADA_CE >= 2 || JORNADA_WCE == 101
#include <tchar.h>
#endif
#endif
#include <jornada/extras.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/windows.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
