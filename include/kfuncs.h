#include <windows.h>
#ifndef JORNADA_WRAPPED_KFUNCS_H
#define JORNADA_WRAPPED_KFUNCS_H

#ifdef JORNADA_INSIDE
#include_next <kfuncs.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <kfuncs.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
