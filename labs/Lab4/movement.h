/*
 * movement.h
 *
 *  Created on: Feb 11, 2021
 *      Author: dwdodson
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "movement.h"
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_FindObjects.h"
#include "cyBot_uart.h"

double move_forward(oi_t *sensor_data, double distance_mm);
//double move_forwardB(oi_t *sensor_data, double distance_mm, bool &bump);
double turn_left(oi_t *sensor_data, double degrees);
double turn_left_dist(oi_t *sensor_data, double degrees);
double turn_right(oi_t *sensor_data, double degrees);
double turn_right_dist(oi_t *sensor_data, double degrees);
double move_backwards(oi_t *sensor_data, double distance_mm);
double maneuver(double distance_mm, oi_t *sensor_data);
void movet_peg(oi_t *sensor_data);
void printPuttyString(const char *string);
void outputPegData(cyBot_Object_t object[], int numObjects);

#endif /* MOVEMENT_H_ */
