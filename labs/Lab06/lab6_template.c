/**
 * lab6_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"

// Uncomment or add any include directives that are needed
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_init();

	cyBOT_init_Scan();

	// YOUR CODE HERE

	 int i = 0;

	 char str[200];

	 cyBOT_Scan_t *point;

	 char header[] = "\nAngle\tPING Distance\tIR raw value\n\r";

	 char g;

	 cyBOT_Scan_t cybot;

	 point = &cybot;

	 int j = 0;

	 while(1) {

	    g = '\0';
	    j = 0;

	    g = uart_receive();

	    if(g == 'g') {
	       uart_sendStr(header);
	       for(i = 0; i <= 180; i += 5) {
	           g = uart_receive_nonblocking();
	           if(g != 's') {
                   cyBOT_Scan(i, point);
                   sprintf(str, "%d\t%f\t%d\n\r", i, point->sound_dist, point->IR_raw_val);
                   uart_sendStr(str);
                   j++;
	           }
	       }
	    }


	}

}
