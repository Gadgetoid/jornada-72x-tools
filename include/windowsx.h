#include <windows.h>
#ifndef JORNADA_WRAPPED_WINDOWSX_H
#define JORNADA_WRAPPED_WINDOWSX_H

#ifdef JORNADA_INSIDE
#include_next <windowsx.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <windowsx.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
