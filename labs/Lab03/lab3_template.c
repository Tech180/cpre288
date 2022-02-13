/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "resetSimulation.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1




int main(void) {
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBot_uart_init();
    // Don't forget to initialize the cyBot UART before trying to use it
    resetSimulationBoard();
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

    while(1)
    {
//        if(cyBot_getByte() == 119)
//        {
//            move_forward(sensor_data, 100);
//        }
//        if(cyBot_getByte() == 100)
//        {
//            turn_right(sensor_data, 30);
//        }
//        if(cyBot_getByte() == 97)
//        {
//            turn_left(sensor_data, 100);
//        }
//        if(cyBot_getByte() == 115) // S not X lol
//        {
//            move_backwards(sensor_data, 30);
//        }
        char c = cyBot_getByte();
        lcd_printf("%c", c);
        timer_waitMillis(5000);

        if(button_getButton() == 4)
        {
            lcd_printf("Button 4 pressed");
            //timer_waitMillis(300);
            cyBot_sendByte('4');
        }
        else if(button_getButton() == 3)
        {
            lcd_printf("Button 3 pressed");
            //timer_waitMillis(300);
            cyBot_sendByte('3');
        }
        else if(button_getButton() == 2)
        {
            lcd_printf("Button 2 pressed");
            //timer_waitMillis(300);
            cyBot_sendByte('2');
        }
        else if(button_getButton() == 1)
        {
            lcd_printf("Button 1 pressed");
            //timer_waitMillis(300);
            cyBot_sendByte('1');
        }
        else //if(button_getButton() == 0)
        {
            //timer_waitMillis(300);
            lcd_printf("No button pressed");
        }
    }
}
