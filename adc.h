/*
 * adc.h
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "msp.h"

uint16_t bit_accel_x;
uint16_t bit_accel_y;
uint16_t bit_accel_z;

void configure_adc(void);



#endif /* ADC_H_ */
