#ifndef JORNADA_TIME_H
#define JORNADA_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TIME_T_DEFINED
typedef unsigned long time_t;
#define _TIME_T_DEFINED
#endif

double difftime(time_t end, time_t start);

#ifdef __cplusplus
}
#endif

#endif
