#include <windows.h>
#ifndef JORNADA_WRAPPED_EXCPT_H
#define JORNADA_WRAPPED_EXCPT_H

#ifdef JORNADA_INSIDE
#include_next <excpt.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <excpt.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
