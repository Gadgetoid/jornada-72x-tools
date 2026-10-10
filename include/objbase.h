#include <windows.h>

#ifndef JORNADA_OBJBASE_H
#define JORNADA_OBJBASE_H

#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/objbase.h>
#endif
#include <rpc.h>
#include <rpcndr.h>
#include <wtypes.h>
#include <unknwn.h>
#include <objidl.h>
#define JORNADA_OBJBASE_H_CONTENT
#ifndef JORNADA_NO_CONSTANTS
#include <jornada/constants.h>
#endif

#endif
