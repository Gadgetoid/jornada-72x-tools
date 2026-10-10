#include <windows.h>
#ifndef JORNADA_WRAPPED_WINGDI_H
#define JORNADA_WRAPPED_WINGDI_H

#ifdef JORNADA_INSIDE
#include_next <wingdi.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <wingdi.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
