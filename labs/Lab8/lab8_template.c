/**
 * @file lab8_template.c
 * @author
 * Template file for CprE 288 Lab 8
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed

#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	float distance = 0;

	while(1)
	{
	    distance = ping_getDistance();
	    lcd_printf("%5.2f %d", distance, overflow_count);
	    timer_waitMillis(500);

	}
}
