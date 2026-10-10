#include <windows.h>
#ifndef JORNADA_WRAPPED_MMSYSTEM_H
#define JORNADA_WRAPPED_MMSYSTEM_H

#ifdef JORNADA_INSIDE
#include_next <mmsystem.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <mmsystem.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
