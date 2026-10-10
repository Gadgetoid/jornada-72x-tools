#include <windows.h>
#ifndef JORNADA_WRAPPED_LMCONS_H
#define JORNADA_WRAPPED_LMCONS_H

#ifdef JORNADA_INSIDE
#include_next <lmcons.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <lmcons.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
