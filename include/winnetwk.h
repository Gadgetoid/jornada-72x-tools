#include <windows.h>
#ifndef JORNADA_WRAPPED_WINNETWK_H
#define JORNADA_WRAPPED_WINNETWK_H

#ifdef JORNADA_INSIDE
#include_next <winnetwk.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winnetwk.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
