/*
 * port.c
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */
#include "msp.h"
#include <stdint.h>
#include "port.h"
#include "movement.h"

void port_configure(void){
    NVIC_EnableIRQ(PORT1_IRQn);

    //Left Button
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;
    P1->DIR &= ~BIT1;
    P1->REN |= BIT1;
    P1->OUT |= BIT1;
    P1->IFG &= ~BIT1;
    P1->IES |= BIT1;
    P1->IE |= BIT1;

    //Right Button
    P1->SEL0 &= ~BIT4;
    P1->SEL1 &= ~BIT4;
    P1->DIR &= ~BIT4;
    P1->REN |= BIT4;
    P1->OUT |= BIT4;
    P1->IFG &= ~BIT4;
    P1->IES |= BIT4;
    P1->IE |= BIT4;

    //Red LED
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->REN &= ~BIT0;
    P1->OUT &= ~BIT0;
    P1->IFG &= ~BIT0;
    P1->IES |= BIT0;
    P1->IE &= ~BIT0;

    //RGB LED
    P2->SEL0 &= ~BIT0 & ~BIT1 & ~BIT2;
    P2->SEL1 &= ~BIT0 & ~BIT1 & ~BIT2;
    P2->DIR |= BIT0 | BIT1 | BIT2;
    P2->REN &= ~(BIT0 | BIT1 | BIT2);
    P2->OUT &= ~(BIT0 | BIT1 | BIT2);
    P2->IFG &= ~(BIT0 | BIT1 | BIT2);
    P2->IES |= BIT0 | BIT1 | BIT2;
    P2->IE &= ~BIT0 & ~BIT1 & ~BIT2;

    //Pin 1.6 encoder interrupt
    P1->SEL0 &= ~BIT6;
    P1->SEL1 &= ~BIT6;
    P1->DIR &= ~BIT6;
    P1->REN &= ~BIT6;
    P1->OUT |= BIT6;
    P1->IFG &= ~BIT6;
    P1->IES |= BIT6;
    P1->IE |= BIT6;

    //Pin 6.1 x accelerometer
    P6->SEL0 &= ~BIT1;
    P6->SEL1 &= ~BIT1;
    P6->DIR &= ~BIT1;
    P6->REN &= ~BIT1;
    P6->OUT |= BIT1;
    P6->IFG &= ~BIT1;
    P6->IES |= BIT1;
    P6->IE &= ~BIT1;

    //Pin 4.0 y accelerometer
    P4->SEL0 &= ~BIT0;
    P4->SEL1 &= ~BIT0;
    P4->DIR &= ~BIT0;
    P4->REN &= ~BIT0;
    P4->OUT |= BIT0;
    P4->IFG &= ~BIT0;
    P4->IES |= BIT0;
    P4->IE &= ~BIT0;

    //Pin 4.2 z accelerometer
    P4->SEL0 &= ~BIT2;
    P4->SEL1 &= ~BIT2;
    P4->DIR &= ~BIT2;
    P4->REN &= ~BIT2;
    P4->OUT |= BIT2;
    P4->IFG &= ~BIT2;
    P4->IES |= BIT2;
    P4->IE &= ~BIT2;
}

//interrupt handler port 1
void PORT1_IRQHandler(void){
    __disable_irq();
    if(P1IFG & BIT6){
        wheel_count++;
        P1->OUT ^= BIT0;
        P1->IFG &= ~BIT6;
    }
    if(P1IFG & BIT4){
        but_flag = 1;
        P2->OUT = BIT1;
        P1->IFG &= ~BIT4;
    }
    if(P1IFG & BIT1){
        but_flag = 0;
        P2->OUT = BIT2;
        P1->IFG &= ~BIT1;
    }

    __enable_irq();
}
