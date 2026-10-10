#include <windows.h>
#ifndef JORNADA_WRAPPED_DDE_H
#define JORNADA_WRAPPED_DDE_H

#ifdef JORNADA_INSIDE
#include_next <dde.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <dde.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
