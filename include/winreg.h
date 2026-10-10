#include <windows.h>
#ifndef JORNADA_WRAPPED_WINREG_H
#define JORNADA_WRAPPED_WINREG_H

#ifdef JORNADA_INSIDE
#include_next <winreg.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winreg.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
