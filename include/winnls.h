#include <windows.h>
#ifndef JORNADA_WRAPPED_WINNLS_H
#define JORNADA_WRAPPED_WINNLS_H

#ifdef JORNADA_INSIDE
#include_next <winnls.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winnls.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
