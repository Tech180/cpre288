/*
 * Scan.h
 *
 * This class does scans of a test field, either at specific points or in a 180 sweep
 *
 *  Created on: Apr 14, 2021
 *      Author: Drake Dodson, Brayden Lamb, Logan Miller, Riley Lawson
 */
#include "Scan.h"

void scan_init()
{
    uart_init();
    ping_init();
    adc_init();
    servo_init();
}

/**
 * Scans at the particular point given in angle and updates that data point
 *
 * @param angle
 *  the angle that the scan will be taken at
 * @param data
 *  the data that is updated with the scan results
 */
void scan(int angle, Scan_data *data)
{
    int raw = 0;
    int i = 0;

    servo_move(angle);
    data->sound_dist = ping_getDistance();

    for(i = 0; i < 64; i++)
    {
        raw += adc_read();
    }
    raw = raw / 64;


    // formula for calculating real values from the IR values
    int distance = 97397* pow(raw, -1.141);
    data->IR_raw_val = distance;

   // For testing purposes
//    char str[200];
//    sprintf(str, "%d\t%f\t%d\n\r", angle, data->sound_dist, data->IR_raw_val);
//    uart_sendStr(str);

}

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
int findObjects(Object_data objects[], int sizeOfObject)
{
    int i = 0;
    int objectNum = 0;
    int widthAngle = 0;
    int startingAngle = 0;
    double distance = 0;

    // Scan data for the first scan
    Scan_data *data;
    Scan_data point;
    data = &point;

    // Scan data for second scan
    Scan_data *data2;
    Scan_data point2;
    data2 = &point2;


    // Runs through a 180 sweep
    for(i = 0; i <= 180; i = i + 3)
    {

        // Scan until an object is found
        scan(i, data);

        // An object has been found if the ir values are less than 100 and the ir values are within that of the sound distance values
        if(data->IR_raw_val < 100 && objectNum < sizeOfObject && (data->IR_raw_val <= (int)data->sound_dist + 5) &&
                (data->IR_raw_val >= (int)data->sound_dist - 5))
        {
            widthAngle = 0;
            distance = data->sound_dist;
            startingAngle = i;
            // Checks to see if at least one of the scans are within the same ranges. Due to the glitchyness of the scan and it's tendency
            // to give unreliable or gaps in data this is necessary. This means that the loop stops keeping track of locations as soon as both data1 and data2 don't have close values
            while(((data->IR_raw_val <= (int)distance + 6 && data->IR_raw_val >= (int)distance - 6) || (data2->IR_raw_val <= (int)distance + 6 && data2->IR_raw_val >= (int)distance - 6)) && distance < 100 && i <= 180)
            {
                // Scan data 1 at i
                scan(i, data);
                widthAngle += 2;
                // Scan data 2 at i + 1
                scan(i + 1, data2);
                i += 2;
            }

            // Added in to attempt to counteract the potential increase in width angle from having to stop when there are two different values
            if(widthAngle > 2)
            {
                widthAngle -= 2;
            }

            // Doesn't add objects of with a width of 1
            if(widthAngle > 1)
            {
                // adds to the object count
                objectNum++;

                objects[objectNum - 1].distance = distance;
                // Calculates the width using arc length
                objects[objectNum - 1].width = 2 * M_PI * distance * ((double)(widthAngle) / 360);
                // Calculates the midpoint of the range of angles
                objects[objectNum - 1].angle = startingAngle + ((widthAngle)  / 2);
            }
        }
    }

    // Move the servo back to center
    servo_move(90);

    // Return the number of objects that have been found
    return objectNum;
}

