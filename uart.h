/*
 * uart.h
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */
#include "msp.h"
#include <stdint.h>

#ifndef UART_H_
#define UART_H_

//#define BAUD9600
//#define BAUD19200
//#define BAUD38400
#define BAUD115200

void UART_configure(void);      //configure UART registers
void UART_send_n(uint8_t * data, uint32_t length);
void UART_send_byte(uint8_t data);

void reverse(char s[]);
void itoa(int n, char s[]);
void my_ftoa(float fnum, char str[], int precision_aft);

#endif /* UART_H_ */
