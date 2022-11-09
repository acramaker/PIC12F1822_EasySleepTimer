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

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char g_timer_count = 0;
unsigned char g_kick = 0;
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    unsigned char last_key_state = 0;
    unsigned char cur_key_state = 0;
    unsigned char key_count = 0;
    unsigned char disp_count = 0;
    unsigned char pow_state = 0;
    long timer_count = 0;
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    while(1)
    {
        SLEEP();
        g_kick = 0;
        TMR1 = 0;
        T1CONbits.TMR1ON = 1;   // Timer1 start
        pow_state = LATA2;      // for debug
        
        // Device power check
        if(pow_state == 0)
        {   // Device is ON
            RA2 = 1;    // Device OFF
            while(RA5 == 1);
            
            // suppress chatter
            g_kick = 0;
            while(!g_kick);     //wait 100ms
            g_kick = 0;
            while(!g_kick);     //wait 100ms
            while(RA5 == 1);
            
            T1CONbits.TMR1ON = 0;   // Timer1 stop
            continue;
        }
        RA2 = 0;    // Device power ON
        RA4 = 1;    // Display ON
        cur_key_state = last_key_state = RA5;

        g_timer_count = 0;
        key_count = 0;
        
        // Sleep timer operation
        while(g_timer_count < 30)
        {   // button operation loop
            while(!g_kick);     //wait 100ms
            g_kick = 0;

            cur_key_state = RA5;
            if(last_key_state == 1 && cur_key_state == 0)
            {
                if(key_count < 11)  // Max 10 times
                    key_count++;
                g_timer_count = 0;
            }
            last_key_state = cur_key_state;
        }

        // Brink LED by sleep times
        if(key_count == 0)
            disp_count = 0;
        else
            disp_count = (key_count-1) * 10;
        
        while(disp_count > 0)
        {   // result display loop
            disp_count--;
            while(!g_kick);     //wait 100ms
            g_kick = 0;
            
            if(disp_count % 10 < 5)
                RA4 = 1;
            else
                RA4 = 0;
        }
        RA4 = 0;
        
        // Wait for sleep
        if(key_count > 1)
        {
            // timer count
            timer_count = ((long)key_count-1L) * 30L * 60L * 10L;
            while(timer_count > 0)
            {
                while(!g_kick);     //wait 100ms
                g_kick = 0;
                cur_key_state = RA5;

                // check button during timer
                if(last_key_state == 1 && cur_key_state == 0)
                    break;
                last_key_state = cur_key_state;
                timer_count--;
            }
            RA2 = 1;    // Radio OFF
        }
        T1CONbits.TMR1ON = 0;   // Timer1 stop
    }
}

