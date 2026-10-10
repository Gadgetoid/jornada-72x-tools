#include <windows.h>
#ifndef JORNADA_WRAPPED_COMMDLG_H
#define JORNADA_WRAPPED_COMMDLG_H

#ifdef JORNADA_INSIDE
#include_next <commdlg.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/commdlg.h>
#endif
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <commdlg.h>
#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/commdlg.h>
#endif
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
