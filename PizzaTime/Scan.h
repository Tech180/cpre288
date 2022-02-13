/*
 * Scan.h
 *
 * This class does scans of a test field, either at specific points or in a 180 sweep
 *
 *  Created on: Apr 14, 2021
 *      Author: Drake Dodson, Brayden Lamb, Logan Miller, Riley Lawson
 */

#ifndef SCAN_H_
#define SCAN_H_

#include "Servo.h"
#include "adc.h"
#include "ping.h"
#include "uart.h"
#include <math.h>

typedef enum {RedPeg, WhitePeg, Incomplete}Peg_dat;

/**
 * Struct for the scan data
 *  Packages together the ir values and
 *  sound distance values
 *
 */
typedef struct{
    float sound_dist;  // Distance from Ping Sensor
    int IR_raw_val;    // Raw ADC value from IR sensor
} Scan_data;

/**
 * Struct for all of the object values
 *  contains a width, distance, angle, and object
 *  typ
 */
typedef struct{
    int angle; //degrees
    float distance; //cm
    float width; //cm
    Peg_dat type;
} Object_data;

void scan_init();

/**
 * Does a 180 degree sweep of the test field and creates an array of all of the
 * objects that have been found in the sweep
 *
 * @param
 *  the object data for the sweep to store it's values to
 * @param sizeOfObject
 *  the size of the object array
 * @return
 *  the number of objects that have been found by the scan
 */
void scan(int angle, Scan_data* data);

int findObjects(Object_data objects[], int sizeOfObject);



#endif /* SCAN_H_ */
