#include <windows.h>
#ifndef JORNADA_WRAPPED_TLHELP32_H
#define JORNADA_WRAPPED_TLHELP32_H

#ifdef JORNADA_INSIDE
#include_next <tlhelp32.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <tlhelp32.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
