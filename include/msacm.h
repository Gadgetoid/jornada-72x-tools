#include <windows.h>
#ifndef JORNADA_WRAPPED_MSACM_H
#define JORNADA_WRAPPED_MSACM_H

#ifdef JORNADA_INSIDE
#include_next <msacm.h>
#include <jornada/extras-msacm.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/msacm.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <msacm.h>
#include <jornada/extras-msacm.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/msacm.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
