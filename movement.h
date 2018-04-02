/*
 * movement.h
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "msp.h"
#include <stdint.h>

#define SPOKENUMBER 14          //number of spokes in wheel
#define DIAMETER    100         //diameter of wheel (millimeters)
#define PI 3.14                 //define pi for calculations
#define CIRCUM (DIAMETER * PI)  //define the circumference

float distance;
float last_distance;
float velocity;
float avg_velocity;
uint8_t distance_string[6];
uint8_t velocity_string[6];

void _distance(void);
void _velocity(void);
void print_avg_velocity(void);
void print_distance(void);
void print_velocity(void);



#endif /* MOVEMENT_H_ */
