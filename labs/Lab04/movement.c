/*
 * movement.c
 *
 *  Created on: Feb 11, 2021
 *      Author: dwdodson
 */

#include "movement.h"
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_FindObjects.h"
#include "cyBot_uart.h"

double move_forward(oi_t *sensor_data, double distance_mm)
{

    oi_setWheels(500, 500); //move forward at full speed
    double sum = 0;

    while (sum <= distance_mm)
    {
        if (sensor_data->bumpLeft || sensor_data->bumpRight)
        {
            break;
        }
        else
        {
            oi_update(sensor_data);
            sum += sensor_data->distance;
            // use -> notation since pointer
        }
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

double move_backwards(oi_t *sensor_data, double distance_mm)
{
    oi_setWheels(-500, -500); //move forward at full speed
    double sum = 0;

    while ((-1 * sum <= distance_mm))
    {

        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer

    }

    oi_setWheels(0, 0); //stop

    return (sum);
}

double turn_right(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(100, -100); //move forward at full speed

    while (sum <= (degrees - 19))
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

double turn_right_dist(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(100, -100); //move forward at full speed

    while (sum <= (degrees - 8))
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

double turn_left(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-100, 100); //move forward at full speed

    while ((sum * -1) <= (degrees - 19))
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

double turn_left_dist(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-100, 100); //move forward at full speed

    while ((sum * -1) <= (degrees - 8))
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

double maneuver(double distance_mm, oi_t *sensor_data)
{
    double distance = 0;
    while (distance < distance_mm)
    {
        distance += move_forward(sensor_data, distance_mm - distance);

        //left and right
        if (sensor_data->bumpLeft && sensor_data->bumpRight)
        {
            move_backwards(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 400);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);

            distance += 250;
        }
        //left
        else if (sensor_data->bumpLeft)
        {
            move_backwards(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 400);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);

            distance += 250;
        }
        //right
        else if (sensor_data->bumpRight)
        {
            move_backwards(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 400);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);

            distance += 250;
        }
    }

    return 1;
}

void movet_peg(oi_t *sensor_data)
{
    int i;
    cyBot_Object_t object[20];
    int numObjects = cyBot_FindObjects(object, 20);

    outputPegData(object, numObjects);

    double smallWid = object[0].width;
    int smallAng = object[0].angle;
    double distance = object[0].distance * 10;
    double offset = 12.0 * 10;

    for (i = 0; i < numObjects; i++)
    {
        if (object[i].width < smallWid)
        {
            smallWid = object[i].width;
            distance = object[i].distance * 10;
            smallAng = object[i].angle;
        }
    }

    while (((distance - offset) ) > 0)
    {
        double mDistance = 500;
        if (smallAng <= 90)
        {
            if(distance > 500)
            {
                turn_left_dist(sensor_data, (90 - smallAng));
            }
            else
            {
                turn_left(sensor_data, (90 - smallAng));
            }
        }
        else if (smallAng > 90)
        {
            if(distance > 500)
            {
                turn_right_dist(sensor_data, (smallAng - 90));
            }
            else
            {
                turn_right(sensor_data, (smallAng - 90));
            }
        }

        if(distance - offset < 500)
        {
            mDistance = (distance - offset);
        }

        move_forward(sensor_data, mDistance);

        if (sensor_data->bumpRight)
        {
            move_backwards(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 270);
            turn_right(sensor_data, 90);
        }
        if (sensor_data->bumpLeft)
        {
            move_backwards(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 270);
            turn_left(sensor_data, 90);
        }
        numObjects = cyBot_FindObjects(object, 20);
        outputPegData(object, numObjects);

        smallWid = object[0].width;
        smallAng = object[0].angle;
        distance = object[0].distance * 10;

        for (i = 0; i < numObjects; i++)
        {
            if (object[i].width < smallWid)
            {
                smallWid = object[i].width;
                distance = object[i].distance * 10;
                smallAng = object[i].angle;
            }
        }
    }
}

void printPuttyString(const char *string)
{
    int i;
    for (i = 0; i < strlen(string); i++)
    {
        cyBot_sendByte(string[i]);
    }
}

void outputPegData(cyBot_Object_t object[], int numObjects)
{
    char string[30];
    int i;
    printPuttyString("Object#\t\tAngle\t\tDistance\tWidth\n");
    for (i = 0; i < numObjects; i++)
    {
        sprintf(string, "%d\t\t%d\t\t%f\t%f\n", i + 1, object[i].angle, object[i].distance, object[i].width);
        printPuttyString(string);
    }
}
