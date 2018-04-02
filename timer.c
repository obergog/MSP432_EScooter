/*
 * timer.c
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */
#include "msp.h"
#include <stdint.h>
#include "timer.h"

void configure_clocks(void){
    //set the SMLK clock to 12MHz
    CS->KEY = 0x695A;
    CS->CTL0 = 0;
    CS->CTL0 = CS_CTL0_DCORSEL_3;   //set frequency range to 8 to 16 MHz
    CS->KEY = 0;

    //Configure Timer 0
    TIMER_A0->R = 0;         // Reset count
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID_3 | TIMER_A_CTL_IE;
    TIMER_A0->CCR[0] = 15000;    // Value to count to (each tick is 1/100 second)
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt enabled

    /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ(TA0_0_IRQn);
}

//interrupt handler for timer A0
void TA0_0_IRQHandler(void){
    __disable_irq();
    if(TIMER_A0->CCTL[0] & BIT0){
        timer_count++;
        total_time++;
        TIMER_A0->CCTL[0] &= ~BIT0;
        TIMER_A0->R = 0;
    }
    __enable_irq();
}
