/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PinNames.h"
#include "mbed.h"

#define LD1_ON     {led1 = 1;}
#define LD1_OFF    {led1 = 0;}
#define LD1_TOG    {led1 = !led1;}

#define LD2_ON     {led2 = 1;}
#define LD2_OFF    {led2 = 0;}
#define LD2_TOG    {led2 = !led2;}

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
PwmOut led(PWM_OUT);
DigitalOut led1(D4);
DigitalOut led2(D2);

InterruptIn button(USER_BUTTON);

volatile float counter = 0.1f;

void button_released()
{
    counter+=0.3f;
    if (counter > 1.01) 
    {   
        counter = 0.1f;
    }
    else
    {
        LD1_TOG;
        LD2_TOG;
    }
    led.write(counter);
}

int main()
{
    LD1_ON;
    LD2_OFF;
    // specify period first
    led.period(0.005f);      // 0.05 second period
    led.write(0.1f);      // 50% duty cycle, relative to period
    //led = 0.5f;          // shorthand for led.write()
    //led.pulsewidth(2);   // alternative to led.write, set duty cycle time in seconds

    button.rise(&button_released); // Change led

    while (1);
}
