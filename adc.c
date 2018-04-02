/*
 * adc.c
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */

#include <stdint.h>
#include "msp.h"
#include "adc.h"

void configure_adc(void){

    ADC14->CTL0 &= ~ADC14_CTL0_ENC;                  //disable conversions

    while(REF_A->CTL0 & REF_A_CTL0_GENBUSY);        //wait while generator is busy
    REF_A->CTL0 = REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON;//enable internal 1.2V ref

    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_3 | ADC14_CTL0_SHT0_5 | ADC14_CTL0_ON | ADC14_CTL0_SHP;
    ADC14->CTL1 |= ADC14_CTL1_CH2MAP | ADC14_CTL1_RES__14BIT;
    //x direction accelerometer A16
    ADC14->MCTL[1] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_16 | ADC14_CTL1_CSTARTADD_MASK;
    ADC14->IER0 |= ADC14_IER0_IE1;                               //enable interrupts
    //y direction accelerometer A13
    ADC14->MCTL[2] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_13 | ADC14_CTL1_CSTARTADD_MASK;
    ADC14->IER0 |= ADC14_IER0_IE2;                               //enable interrupts
    //z direction accelerometer A11
    ADC14->MCTL[3] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_11 | ADC14_CTL1_CSTARTADD_MASK;
    ADC14->MCTL[3] |= ADC14_MCTLN_EOS;                           //make this the end of sequence
    ADC14->IER0 |= ADC14_IER0_IE3;                               //enable interrupts

    while(!(REF_A->CTL0 & REF_A_CTL0_GENRDY));      //wait for generator to settle
    ADC14->CTL0 |= ADC14_CTL0_ENC;                  //enable conversions
    NVIC_EnableIRQ(ADC14_IRQn);
}

//interrupt handler for the 14bit ADC
void ADC14_IRQHandler(void){
    __disable_irq();
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1){
        bit_accel_x = ADC14->MEM[1];
    }
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG2){
        bit_accel_y = ADC14->MEM[2];
    }
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG3){
        bit_accel_z = ADC14->MEM[3];
    }
    __enable_irq();
}

