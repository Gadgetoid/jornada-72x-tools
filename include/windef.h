#include <windows.h>
#ifndef JORNADA_WRAPPED_WINDEF_H
#define JORNADA_WRAPPED_WINDEF_H

#ifdef JORNADA_INSIDE
#include_next <windef.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <windef.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
