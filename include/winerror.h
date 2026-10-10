#include <windows.h>
#ifndef JORNADA_WRAPPED_WINERROR_H
#define JORNADA_WRAPPED_WINERROR_H

#ifdef JORNADA_INSIDE
#include_next <winerror.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winerror.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
