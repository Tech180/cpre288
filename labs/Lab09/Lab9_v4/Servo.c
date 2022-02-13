#include "servo.h"
#include "Timer.h"


void servo_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x2;
    while((SYSCTL_PRGPIO_R & 0x2) == 0);

    GPIO_PORTB_DEN_R |= 0x20;                   // Enabling bits 5 to be an input
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;                 // Setting bit 5 to be an alternate function
    GPIO_PORTB_PCTL_R |= 0x00700000;            // Alternate function set to T1CCP1

    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;  //0x00000002
    TIMER1_CTL_R &= ~0x100;                     // Disable TIMER1 for setup
    TIMER1_CFG_R = 0X4;

    TIMER1_TBMR_R = 0xA;                        //Setting tbams to 0x1 tbcmr to 0x0 tbmr 0x2

    TIMER1_TBILR_R |= 0xE200;                   //timer load load bits 0 - 15
    TIMER1_TBPR_R |= 0x04;                      //pre scale loads bits 16 - 23 - turns the counter into a 24bit counter

    //TIMER1_TBMATCHR_R = 0x8440;                 //Load match register with match value -> 320 - 24 = 296,000

    TIMER1_CTL_R |= 0x100;                      //Re-enable clock
}


int servo_move(float degrees)
{
    // Nothing catching the servo from going beyond 180 degrees
    unsigned long new_match = 319000 + (296000 - 319000) * (degrees/180); // 296000 = 18.5 ms  19.9375 320000

    TIMER1_TBMATCHR_R = new_match;          // Sets the match register to be the value

    TIMER1_TBPMR_R = (new_match >> 16);     // Sets match bits 19 - 23

    return new_match;

}
