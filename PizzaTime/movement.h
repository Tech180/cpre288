/*
 * movement.h
 *
 * The main functions of the autonomous pizza robot. This class moves the robot around the test field
 * and dodges obstacles as well as delivering pizza to the customer at the homebase
 *
 *  Created on: Feb 11, 2021
 *      Author: Brayden Lamb, Drake Dodson, Logan Miller, Riley Lawson
 *
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "movement.h"
#include "lcd.h"
#include "open_interface.h"
#include "Scan.h"
#include "uart.h"

/**
 * Moves the cybot forward
 *
 * @param sensor_data
 *  the cybot data package
 * @param distance_mm
 *  the distance in millimeters to move forward
 * @return
 *  the distance traveled
 */
double move_forward(oi_t *sensor_data, double distance_mm);

/**
 * Moves the cybot backwards
 *
 * @param sensor_data
 *  the cybot data package
 * @param distance_mm
 *  the distance in millimeters to move backwards
 * @return
 *  the distance travelled
 */
double move_backwards(oi_t *sensor_data, double distance_mm);

/**
 * Angles the cybot right or clockwise the given degrees
 *
 * @param sensor_data
 *  the cybot data package
 * @param distance_mm
 *  the distance in millimeters to move forward
 * @return
 *  the degrees turned right
 */
double turn_right(oi_t *sensor_data, double degrees);

/**
 * Angles the cybot left or counterclockwise the given degrees
 *
 * @param sensor_data
 *  the cybot data package
 * @param distance_mm
 *  the distance in millimeters to move forward
 * @return
 *  the degrees turned left
 */
double turn_left(oi_t *sensor_data, double degrees);

/**
 * Has various functions for moving the cybot across the field
 *
 * @param sensor_data
 *  the cybot data package
 * @param distance_mm
 *  the distance in millimeters to move forward
 * @return
 *  the degrees turned left
 */
void maneuver(oi_t *sensor_data, float distance_mm);

/**
 * The main code that runs the autonomous pizza delivery. The code
 * inches towards the closest small peg and then runs a check for the
 * homebase
 *
 * @param sensor_data
 *  the cybot sensor data
 *
 */
void find_HomeBase(oi_t *sensor_data);

/**
 * This helper method is ran if the robot is directly perpendicular (or close enough) to the entrance
 * to the home base
 *
 * @param
 *  the cybot sensor information
 * @param
 *  the distance between the cybot and the entrance
 *  calculated in homebase_check
 * @return
 *  true if parking was succesful, false otherwise
 */
bool park(oi_t *sensor_data, float distance);

/**
 * Helper method for detecting cliffs (and objects) when navigating to specific locations
 *
 * @param sensor_data
 *  cybot sensor information
 * @return
 *  if a cliff was detected or if it wasn't detected
 */
bool cliff_detected(oi_t *sensor_data);

/**
 * This function does a lot of trigonometry to figure out specific angles for the
 * cybot to move in order to make it into the home base
 *
 * @param sensor_data
 *  cybot sensor information
 * @return
 *  true if the function has delievered the pizza, false otherwise
 */
bool homebase_check(oi_t *sensor_data);



/**
 * Updates an array of white pegs with all of the white pegs found in a search
 *
 * @param whitepegs
 *  and array of whitepegs
 * @param scandata
 *  the data from the last scan
 * @param sizeofObjects
 *  the amount of objects in scandata
 * @return
 *  the number white pegs
 */
int updateRedPegArray(Object_data *redpegs, Object_data *scandata, int sizeofObjects);

/**
 * Updates an array of red pegs with all of the white pegs found in a search
 *
 * @param rd pegs
 *  and array of red pegs
 * @param scandata
 *  the data from the last scan
 * @param sizeofObjects
 *  the amount of objects in scandata
 * @return
 *  the number red pegs
 */
int updateWhitePegArray(Object_data *whitepegs, Object_data *scandata, int sizeofObjects);

/**
 * The following helper method is a lookup table of ranges of values that are generally red pegs
 *
 * @param distance
 *  the distance of the object to be surveyed
 * @param width
 *  the width of the object to be surveyed
 * @param angle
 *  the angle of the object to be surveyed
 * @return
 *  true if the object is a red peg, false otherwise
 */
bool whiteOrRed(float distance, float width, int angle);

/**
 * Runs through all of the elements in a search and updates their value with
 *
 * @param objectArr
 *  the data to be looked through
 * @param objectSize
 *  the number of objects in objectArr
 */
void peg_check(Object_data *objectArr, int objectSize);

/**
 * Outputs the peg data of a given array, excluding their type
 *
 * @param object
 *  the array of type Object_data to be output
 * @param numObjects
 *  the number of objects that are withing object
 *
 */
void outputPegData(Object_data object[], int numObjects);

/**
 * The most important part of the whole code. Outputs the Pizza time image to the uart when the pizza has been delivered
 */
void PIZZATIME();

#endif /* MOVEMENT_H_ */
