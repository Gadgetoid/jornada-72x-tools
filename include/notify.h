#include <windows.h>
#ifndef JORNADA_WRAPPED_NOTIFY_H
#define JORNADA_WRAPPED_NOTIFY_H

#ifdef JORNADA_INSIDE
#include_next <notify.h>
#include <jornada/extras-notify.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/notify.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <notify.h>
#include <jornada/extras-notify.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/notify.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
