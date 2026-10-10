#include <windows.h>
#ifndef JORNADA_WRAPPED_WINBASE_H
#define JORNADA_WRAPPED_WINBASE_H

#ifdef JORNADA_INSIDE
#include_next <winbase.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winbase.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
