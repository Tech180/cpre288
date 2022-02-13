/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping.h"
#include "Timer.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

void ping_init (void){

  // YOUR CODE HERE
   SYSCTL_RCGCTIMER_R |= 0x08;
   SYSCTL_RCGCGPIO_R |= 0x02;

   GPIO_PORTB_DEN_R |= 0x08;
   GPIO_PORTB_DIR_R |= 0x08;

   GPIO_PORTB_AFSEL_R &= ~0x08;

   //GPIO_PORTB_AFSEL_R &= ~0x08;

   TIMER3_CTL_R &= 0xFEFF;

   TIMER3_CFG_R |= 0x04;

   TIMER3_TBMR_R &= ~0x10;
   TIMER3_TBMR_R |= 0x07;

   TIMER3_CTL_R |= 0x0C00;

   TIMER3_TBPR_R |= 0xFF;

   TIMER3_TBILR_R |= 0xFFFF;

   //TIMER3_GPTBIMR_R |= 0x400;

   TIMER3_CTL_R |= 0x0100;



   IntRegister(INT_TIMER3B, TIMER3B_Handler);

   IntMasterEnable();

    // Configure and enable the timer
    TIMER3_CTL_R ???;
}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R ???;
    TIMER3_IMR_R ???;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R ???;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R ???
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R ???;
    TIMER3_IMR_R ???;
    TIMER3_CTL_R ???;
}

void TIMER3B_Handler(void){

  // YOUR CODE HERE

}

float ping_getDistance (void){

    // YOUR CODE HERE

}
