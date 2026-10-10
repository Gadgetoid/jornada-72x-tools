#include <windows.h>
#ifndef JORNADA_WRAPPED_BASETSD_H
#define JORNADA_WRAPPED_BASETSD_H

#ifdef JORNADA_INSIDE
#include_next <basetsd.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <basetsd.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
