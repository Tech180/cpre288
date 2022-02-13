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
#include "cyBot_FindObjects.h"
#include "open_interface.h"

int main(void)
{
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBot_uart_init();
    // Don't forget to initialize the cyBot UART before trying to use it
    //resetSimulationBoard();
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()


    cyBot_Object_t object[20];
    //int numObjects = cyBot_FindObjects(object, 20);
    int i;
    //numObjects = cyBot_FindObjects(object, 20);


    //printPuttyString("Object#\tAngle\t\tDistance\tWidth\n");


    char string[30];

    // Putty Display
//    for (i = 0; i < numObjects; i++)
//    {
//        sprintf(string, "%d\t%d\t%f\t%f\n", i + 1, object[i].angle, object[i].distance, object[i].width);
//    }
//
//    printPuttyString(string);

    movet_peg(sensor_data);

}

