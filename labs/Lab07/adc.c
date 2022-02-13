#include "adc.h"



void adc_init()
{
    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x02;

    while((SYSCTL_PRGPIO_R & 0x02) != 0x02);
    //while((SYSCTL_PRADC_R & 0x0001) != 0x0001) {};

    GPIO_PORTB_DIR_R &= ~0x10; // Setting PB4 as and input 0b xxx0 xxxx
    GPIO_PORTB_AFSEL_R |= 0x10; // PB4
    GPIO_PORTB_DEN_R &= ~0x10; // 0b1110 1111 &
    GPIO_PORTB_AMSEL_R |= 0x10;

    while((SYSCTL_PRADC_R & 0x0001) != 0x0001) {};

    ADC0_PC_R = 0x1;
    ADC0_SSPRI_R &= 0x3210;
    ADC0_SSPRI_R |= 0x3210; // 0b 0011 0010 0001 0000
    //ADC0_SSPRI_R = 0x3210;

    ADC0_ACTSS_R &= ~0x0001; // 0b 1110
    ADC0_EMUX_R &= ~0x000F;

    ADC0_SSMUX0_R &= ~0x000F;
    //ADC0_SSMUX0_R &= 0xFFF0;// 0b1111 1111 0000

    //ADC0_SSMUX0_R |= 0xFFFA; // 0b1111 1111 1010
    ADC0_SSMUX0_R += 10;

    ADC0_SSCTL0_R &= 0x0006;
    ADC0_SSCTL0_R |= 0x0006;

    ADC0_ACTSS_R |= 0x0001;

}

int adc_read()
{
    ADC0_PSSI_R &= 0x0001;
    ADC0_PSSI_R |= 0x0001;

    while((ADC0_RIS_R & 0x01) == 0) {};

    int result = ADC0_SSFIFO0_R & 0xFFF;

    ADC0_ISC_R = 0x0001;

    return result;
}
