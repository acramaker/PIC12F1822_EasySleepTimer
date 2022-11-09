/*******************************************************************************
MIT License

Copyright (c) 2022 akrmkw

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <pic12f1822.h>
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISA2 = 0;             // RA2 output
    RA2 = 1;                // Device OFF
    
    TRISA4 = 0;             // RA5 output
    ANSA2 = 0;              // RA2 analog disable
    ANSA4 = 0;              // RA4 analog disable
    
    T1CONbits.TMR1CS = 0b00;        // Clock = fosc/4
    T1CONbits.T1CKPS = 0b10;        // Prescale = 1:4
    
    CCPR1 = 3125;                   // Interrupt 100ms
    CCP1CONbits.CCP1M = 0b1011;     // Compare mode - software interrupt
    CCP1IF = 0;            // Clear Interrupt Flag
    CCP1IE = 1;            // CCP interrupt enable
    PEIE = 1;            // Peripheral interrupt enable
    GIE = 1;             // Global interrupt enable
    
    IOCAF5 = 0;                     // RA4 interrupt flag clear
    IOCAP5 = 1;                     // RA4 interrupt enable
    IOCIE = 1;                      // I/O interrupt enable
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
}

