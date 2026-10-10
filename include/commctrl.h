#include <windows.h>
#ifndef JORNADA_WRAPPED_COMMCTRL_H
#define JORNADA_WRAPPED_COMMCTRL_H

#ifdef JORNADA_INSIDE
#include_next <commctrl.h>
#include <jornada/extras-commctrl.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/commctrl.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <commctrl.h>
#include <jornada/extras-commctrl.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/commctrl.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
