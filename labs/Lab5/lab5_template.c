/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021
 */

#include "timer.h"
#include "lcd.h"
#include "cyBot_uart.h"
#include "uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1
#include "cyBot_FindObjects.h"  // Scan the CyBot sensors to find objects





int main(void) {
	//timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

	// initialize the cyBot UART1 before trying to use it
	// (Uncomment ME for UART init part of lab)
	//cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

	uart_init();
	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
//     SYSCTL_RCGCGPIO_R |= 0x02;
//	 while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
//	 GPIO_PORTB_DEN_R |= 0x03;
//	 GPIO_PORTB_AFSEL_R |= 0x03;
//     GPIO_PORTB_PCTL_R &= 0x03;     // Force 0's in the desired locations 0b000000xx
//     GPIO_PORTB_PCTL_R |= 0x03;     // Force 1's in the desired locations 0b00000011
     // Or see the notes for a coding alternative to assign a value to the PCTL field

     // (Uncomment ME for UART init part of lab)
     cyBot_uart_init_last_half();  // Complete the UART device configuration

//     char c;
    while (1)
    {
//         c = uart_receive();
//         lcd_printf("%c", c);
//     }

        int i = 0;
        char input[70];
        char c;

        //input[0] = 'A';
        //lcd_clear();
        while (i < 21)
        {
            c = uart_receive();
            if (i == 20)
            {
                input[20] = '\0';
                lcd_printf("%s", input);
                uart_sendChar('\n');
                uart_sendChar('\r');
                uart_sendStr(input);
                uart_sendChar('\n');
                uart_sendChar('\r');
                i = 0;
            }
            if (c == '\r')
            {
                input[i] = '\0';
                lcd_printf("%s", input);
                uart_sendStr(input);
                uart_sendChar('\n');
                uart_sendChar('\r');
                i = 0;
            }
            if (c != '\r')
            {
                input[i] = c;
                uart_sendChar(c);
                lcd_printf("%c", c);
                i++;
            }
        }
    }
}
