/*
 * timer.h
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "msp.h"
#include <stdint.h>

uint32_t timer_count;
uint32_t total_time;

void configure_clocks(void);


#endif /* TIMER_H_ */
