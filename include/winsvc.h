#include <windows.h>
#ifndef JORNADA_WRAPPED_WINSVC_H
#define JORNADA_WRAPPED_WINSVC_H

#ifdef JORNADA_INSIDE
#include_next <winsvc.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winsvc.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
