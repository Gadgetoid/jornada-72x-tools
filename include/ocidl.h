#include <windows.h>

#ifndef JORNADA_OCIDL_H
#define JORNADA_OCIDL_H

#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/ocidl.h>
#endif
#include <rpc.h>
#include <rpcndr.h>
#include <ole2.h>
#include <oleidl.h>
#include <oaidl.h>
#define JORNADA_OCIDL_H_CONTENT
#ifndef JORNADA_NO_CONSTANTS
#include <jornada/constants.h>
#endif

#endif
