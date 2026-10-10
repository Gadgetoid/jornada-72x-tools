#include <windows.h>
#ifndef JORNADA_WRAPPED_DBGAPI_H
#define JORNADA_WRAPPED_DBGAPI_H

#ifdef JORNADA_INSIDE
#include_next <dbgapi.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <dbgapi.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
