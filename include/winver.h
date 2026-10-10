#include <windows.h>
#ifndef JORNADA_WRAPPED_WINVER_H
#define JORNADA_WRAPPED_WINVER_H

#ifdef JORNADA_INSIDE
#include_next <winver.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winver.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
