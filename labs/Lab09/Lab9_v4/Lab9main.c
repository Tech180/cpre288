




#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include <math.h>
#include <inc/tm4c123gh6pm.h>
#include "resetSimulation.h"

int main (void) {
    resetSimulationBoard();
    lcd_init();
    timer_init();
    servo_init();

    servo_move(30);
    servo_move(150);
    servo_move(90);

	return 0;
}
