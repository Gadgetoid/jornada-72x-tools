#include <windows.h>
#ifndef JORNADA_WRAPPED_WINUSER_H
#define JORNADA_WRAPPED_WINUSER_H

#ifdef JORNADA_INSIDE
#include_next <winuser.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winuser.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
