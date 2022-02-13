/*
 * resetSimulation.c
 *
 *  Created on: Apr 30, 2020
 *      Author: Jacob Aspinall
 */

#include "Timer.h"

void resetSimulationBoard(){
    //Turn on clock to port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //Set PB6 as output
    GPIO_PORTB_DIR_R |= 0x40;
    //Enable Digital on PB6
    GPIO_PORTB_DEN_R |= 0x40;

    //Set PB6 high
    GPIO_PORTB_DATA_R |= 0x40;
    timer_waitMicros(10);
    GPIO_PORTB_DATA_R &= ~0x40;
    GPIO_PORTB_DEN_R &= ~(0x40);
    timer_waitMillis(3000);//Let the simulation board reset


}


