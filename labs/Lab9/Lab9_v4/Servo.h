


#ifndef SERVO_H_
#define SERVO_H_

#include "Timer.h"
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>

/* Initializing the servo motor, uses PB5 and Timer 1B */
void servo_init(void);

int servo_move(double degrees);


#endif
