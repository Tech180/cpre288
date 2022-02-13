/*
 * movement.c
 *
 *  Created on: Feb 10, 2021
 *      Author: rjlawson
 */

//#ifndef MOVEMENT_C_
//#define MOVEMENT_C_

//#include "open_interface.h"

#include "movement.h"

double move_forward (oi_t *sensor_data, double distance_mm) {

    double sum = 0; // distance member in oi_t struct is type double

    oi_setWheels(500, 500); //move forward at full speed

    while (sum < distance_mm) {
        oi_update(sensor_data);

        sum += sensor_data -> distance;
        //sum += oi_getDistance(sensor_data); // use -> notation since pointer

    }

    oi_update(sensor_data);

    if(sensor_data -> bumbLeft){
        oi_setWheels(0,0);

        oi_t structure(bumbLeft);

        move_backwards(sensor_data, 150);

        turn_
    }

    oi_setWheels(0,0); //stop

    return distance_mm;

}

double move_backwards (oi_t *sensor_data, double distance_mm) {

    double sum = 0; // distance member in oi_t struct is type double

    oi_setWheels(500, 500); //move forward at full speed

    while (sum < distance_mm) {
        oi_update(sensor_data);

        sum += sensor_data -> distance;
        //sum += oi_getDistance(sensor_data); // use -> notation since pointer

    }

    oi_setWheels(0,0); //stop

    return distance_mm;

}


void turn_right(oi_t *sensor_data, double degrees) {

    double rotate = 0;

    oi_setWheels(100, -100);

    while (rotate < (degrees - 2) ) {

        oi_update(sensor_data);

        rotate += sensor_data -> angle;

    }

    oi_setWheels(0,0);

    //oi_free(sensor);

}

/*
void turn_left(oi_t *sensor, double degrees) {

    double rotate = 0;

    oi_setWheels(200, -200);

    while (rotate < (degrees - 2) ) {

        oi_update(sensor_data);

        rotate += sensor_data -> angle;

     }

    oi_setWheels(0,0);

}
*/
