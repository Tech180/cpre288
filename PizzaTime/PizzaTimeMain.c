/*
 * movement.c
 *
 * Honestly not much here. The function initalizes values and then calls find_HomeBase
 *
 *  Created on: Feb 11, 2021
 *      Author: Brayden Lamb, Drake Dodson, Logan Miller, Riley Lawson
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include <math.h>
#include <inc/tm4c123gh6pm.h>
#include "Scan.h"
#include "resetSimulation.h"
#include "uart.h"
#include "movement.h"
#include "open_interface.h"



int main(void)
{
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    uart_init();
    scan_init();
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()


    find_HomeBase(sensor_data);
 }
