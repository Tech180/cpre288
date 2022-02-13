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
#include "adc.h"
#include "math.h"

// Uncomment or add any include directives that are needed
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	//resetSimulationBoard();
	uart_init();
	//cyBOT_init_Scan();
	adc_init();

	int rawr;
	float distance;
	//cyBOT_Scan(10, distance);

	//lcd_printf("Hello");
    while (1)
    {
        rawr = adc_read();
        distance = 21816 * pow(rawr, -0.852) - 19;
        timer_waitMillis(500);
        lcd_printf("Raw: %d \nActual Distance : %f", rawr, distance);
    }
}
