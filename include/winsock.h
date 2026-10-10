#include <windows.h>
#ifndef JORNADA_WRAPPED_WINSOCK_H
#define JORNADA_WRAPPED_WINSOCK_H

#ifdef JORNADA_INSIDE
#include_next <winsock.h>
#include <jornada/extras-winsock.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/winsock.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <winsock.h>
#include <jornada/extras-winsock.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/winsock.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
