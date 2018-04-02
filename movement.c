/*
 * movement.c
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#include "msp.h"
#include <stdint.h>
#include "movement.h"
#include "port.h"
#include "timer.h"
#include "uart.h"

//calculate distance based on wheel count
void _distance(void){
    distance = ((CIRCUM/SPOKENUMBER)*wheel_count)/1000;
}

//calculate velocity based on distance and timer value
void _velocity(void){
    velocity = (distance - last_distance)/(timer_count/100);
    if (velocity < .01){
        velocity = 0;
    }
}

//print the average velocity over UART to the serial terminal
void print_avg_velocity(void){
    avg_velocity = distance/(total_time/100);
    UART_send_n("Average Velocity (m/s):",23);
    my_ftoa(avg_velocity,velocity_string,3);
    UART_send_n(velocity_string,sizeof(velocity_string)/sizeof(uint8_t));
    UART_send_byte('\r');

}

//print the distance over UART to the serial terminal
void print_distance(void){
    UART_send_n("Total Distance (meters):",24);
    my_ftoa(distance,distance_string,3);
    UART_send_n(distance_string,sizeof(distance_string)/sizeof(uint8_t));
    UART_send_byte('\r');
}

//print the current velocity over UART to the serial terminal
void print_velocity(void){
    UART_send_n("Current Velocity (m/s):",23);
    my_ftoa(velocity,velocity_string,3);
    UART_send_n(velocity_string,sizeof(velocity_string)/sizeof(uint8_t));
    UART_send_byte('\n');
}
