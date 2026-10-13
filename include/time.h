#ifndef JORNADA_TIME_H
#define JORNADA_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TIME_T_DEFINED
typedef unsigned long time_t;
#define _TIME_T_DEFINED
#endif

/**
 * Returns the difference between two times in seconds.
 *
 * @param end The later time.
 * @param start The earlier time.
 * @return end minus start, in seconds.
 */
double difftime(time_t end, time_t start);

#ifdef __cplusplus
}
#endif

#endif
