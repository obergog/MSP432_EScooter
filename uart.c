/*
 * uart.c
 * Created by Alex Johnson
 * In Fall 2017 for CU Boulder class ECEN 2440
 */
#include "msp.h"
#include "uart.h"
#include <stdint.h>

//configure the UART register to communicate properly
void UART_configure(void){
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~BIT2 & ~BIT3;

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;         //enable software reset
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_PEN;          //disable parity
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_MODE_0;         //UART mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SYNC;         //asynchronous mode
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;   //use SMLK clock
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_MSB;          //LSB first
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SEVENBIT;     //8 bit data
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SPB;          //1 stop bit

#ifdef BAUD9600                                     //use 9600 BAUD rate
    EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A0->BRW = 78;
    EUSCI_A0->MCTLW |= 2 << EUSCI_A_MCTLW_BRF_OFS;
    EUSCI_A0->MCTLW |= 0 << EUSCI_A_MCTLW_BRS_OFS;
#endif
#ifdef BAUD19200                                    //use 19200 BAUD rate
    EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A0->BRW = 39;
    EUSCI_A0->MCTLW |= 1 + EUSCI_A_MCTLW_BRF_OFS;
    EUSCI_A0->MCTLW |= 0 + EUSCI_A_MCTLW_BRS_OFS;
#endif
#ifdef BAUD38400                                    //use 38400 BAUD rate
    EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A0->BRW = 19;
    EUSCI_A0->MCTLW |= 8 << EUSCI_A_MCTLW_BRF_OFS;
    EUSCI_A0->MCTLW |= 0x65 << EUSCI_A_MCTLW_BRS_OFS;
#endif
#ifdef BAUD115200                                   //use 115200 BAUD rate
    EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A0->BRW = 6;
    EUSCI_A0->MCTLW |= 8 << EUSCI_A_MCTLW_BRF_OFS;
    EUSCI_A0->MCTLW |= 0x20 << EUSCI_A_MCTLW_BRS_OFS;
#endif
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;        //disable software reset
}

//send n number of bytes over UART
void UART_send_n(uint8_t * data, uint32_t length){
    uint32_t i=0;

    for(i=0; i < length; i++){
        UART_send_byte(data[i]);
    }
}

//send a single given byte over UART
void UART_send_byte(uint8_t data){
    while(!(EUSCI_A0->IFG & BIT1));
    EUSCI_A0->TXBUF = data;
}

/*the following reverse and itoa functions were found at:
  https://en.wikibooks.org/wiki/C_Programming/stdlib.h/itoa */
/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
      n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

//convert fnum to characters in s
void my_ftoa(float fnum, char str[], int precision_aft) {
    int i;
    int j;
    int k;
    int power = 1;
    int precision_bef;

    char pbef_char[15];

    if(fnum == 0){
        for(i=0; i<(sizeof(str)/sizeof(char)); i++){
            str[i] = '0';
        }
    }

    else{
        for (k = 0; k < precision_aft; k++) {
           power = power*10;
        }

        //precision_bef =
        itoa((int)fnum, pbef_char);
        precision_bef = strlen(pbef_char);

        // split integer and decimal parts into two ints
        int integer_part = (int)fnum;
        int decimal_part = ((int)(fnum*power)%power);

        // call itoa on each int
        char int_char[15];
        char dec_char[15];
        itoa(integer_part, int_char);
        itoa(decimal_part, dec_char);

        // concatenate strings with decimal
        //str = (int_char + "." + dec_char);
        for(i = 0; i < precision_bef; i++) {
            str[i] = int_char[i];
        }
        str[i++] = '.';
        for(j = 0; j < precision_aft; j++) {
            str[i++] = dec_char[j];
        }
        //str[i] = '\0';
    }

}
