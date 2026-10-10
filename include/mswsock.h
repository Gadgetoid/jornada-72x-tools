#include <windows.h>
#include <winsock.h>
#ifndef JORNADA_WRAPPED_MSWSOCK_H
#define JORNADA_WRAPPED_MSWSOCK_H

#ifdef JORNADA_INSIDE
#include_next <mswsock.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <mswsock.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
