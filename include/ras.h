#include <windows.h>
#ifndef JORNADA_WRAPPED_RAS_H
#define JORNADA_WRAPPED_RAS_H

#ifdef JORNADA_INSIDE
#include_next <ras.h>
#include <jornada/extras-ras.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/ras.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <ras.h>
#include <jornada/extras-ras.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/ras.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
