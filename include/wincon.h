#include <windows.h>
#ifndef JORNADA_WRAPPED_WINCON_H
#define JORNADA_WRAPPED_WINCON_H

#ifdef JORNADA_INSIDE
#include_next <wincon.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <wincon.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
