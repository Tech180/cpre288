/*
 * movement.h
 *
 *  Created on: Feb 10, 2021
 *      Author: rjlawson
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"

//#include "movement.c"

double move_forward (oi_t *sensor_data, double distance_mm);

void turn_right(oi_t *sensor_data, double degrees);

#endif /* MOVEMENT_H_ */
