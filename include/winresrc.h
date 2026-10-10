#include <windows.h>
#ifndef JORNADA_WRAPPED_WINRESRC_H
#define JORNADA_WRAPPED_WINRESRC_H

#ifdef JORNADA_INSIDE
#include_next <winresrc.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winresrc.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
