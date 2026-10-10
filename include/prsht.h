#include <windows.h>
#ifndef JORNADA_WRAPPED_PRSHT_H
#define JORNADA_WRAPPED_PRSHT_H

#ifdef JORNADA_INSIDE
#include_next <prsht.h>
#else
#define JORNADA_INSIDE
#include <jornada/begin.h>
#include_next <prsht.h>
#include <jornada/end.h>
#undef JORNADA_INSIDE
#endif

#endif
