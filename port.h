/*
 * port.h
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#ifndef PORT_H_
#define PORT_H_

#include "msp.h"
#include <stdint.h>

uint32_t wheel_count;
uint8_t but_flag;

void port_configure(void);



#endif /* PORT_H_ */
