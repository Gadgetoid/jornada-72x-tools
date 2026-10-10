#include <windows.h>
#ifndef JORNADA_WRAPPED_SHELLAPI_H
#define JORNADA_WRAPPED_SHELLAPI_H

#ifdef JORNADA_INSIDE
#include_next <shellapi.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <shellapi.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
