#include <windows.h>

#ifndef JORNADA_RPC_H
#define JORNADA_RPC_H

#if !defined(RC_INVOKED) && !defined(JORNADA_NO_SDK)
#include <jornada/sdk/rpc.h>
#endif
#include <rpcdce.h>
#define JORNADA_RPC_H_CONTENT
#ifndef JORNADA_NO_CONSTANTS
#include <jornada/constants.h>
#endif

#endif
