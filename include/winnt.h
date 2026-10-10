#include <windows.h>
#ifndef JORNADA_WRAPPED_WINNT_H
#define JORNADA_WRAPPED_WINNT_H

#ifdef JORNADA_INSIDE
#include_next <winnt.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winnt.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
