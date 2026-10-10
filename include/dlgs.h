#include <windows.h>
#ifndef JORNADA_WRAPPED_DLGS_H
#define JORNADA_WRAPPED_DLGS_H

#ifdef JORNADA_INSIDE
#include_next <dlgs.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <dlgs.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
