/*****************************************************************************
*
* Copyright (C) 2013 - 2016 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* Project created by Alex Johnson
* In Fall 2017 For CU Boulder Class ECEN 2440
* Project uses various peripheral sensors to read and display information
* on a moving scooter
*
******************************************************************************/

#include "msp.h"
#include <stdint.h>
#include "uart.h"
#include "timer.h"
#include "movement.h"
#include "port.h"
#include "adc.h"

#define ENABLE_SLEEPONEXIT (0x00000002)

int main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    //configure peripheral registers
    port_configure();
    UART_configure();
    configure_clocks();
    configure_adc();
    __enable_irq();
    SCB->SCR &= ~ENABLE_SLEEPONEXIT;            //wake up on exit from ISR

    //initialize values to zero or space
    wheel_count = 0;
    timer_count = 0;
    total_time = 0;
    last_distance = 0;
    avg_velocity = 0;
    but_flag = 1;
    uint8_t direction_flag = 0;
    for(int i=0; i < sizeof(distance_string)/sizeof(uint8_t);i++){
        distance_string[i] = ' ';
    }
    for(int i=0; i < sizeof(velocity_string)/sizeof(uint8_t);i++){
        velocity_string[i] = ' ';
    }

    while(1){
        //find distance and velocity
        _distance();
        _velocity();
        ADC14->CTL0 |= ADC14_CTL0_SC;       //start conversion

        //poll accelerometer and print all data every second
        if(timer_count > 100){
            //print distance and velocity
            if(but_flag == 1){
                print_distance();
                print_velocity();

            }
            else{
                print_avg_velocity();
                UART_send_byte('\n');
            }
            timer_count = 0;
            last_distance = distance;

            //find accelerometer values
            if(velocity == 0){
                direction_flag = 0;
            }
            else if(bit_accel_z < 8000){
                direction_flag = 1;
            }
            else if(bit_accel_z > 9000){
                direction_flag = 2;
            }

            //print direction moving based on values
            if(direction_flag == 0){
                UART_send_n("Stopped\n",8);
            }
            else if(direction_flag == 1){
                UART_send_n("Forward\n",8);
            }
            else if(direction_flag == 2){
                UART_send_n("Backward\n",9);
            }
            UART_send_byte('\n');

        }

    }
	
    return 0;
}
