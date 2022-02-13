/*
 * movement.c
 *
 *  Created on: Feb 11, 2021
 *      Author: dwdodson
 */


#include "movement.h"
#include "lcd.h"
#include "open_interface.h"

double move_forward(oi_t *sensor_data, double distance_mm)
{
    oi_setWheels(500, 500); //move forward at full speed
    double sum = 0;

    while (sum <= distance_mm)
    {
        if(sensor_data-> bumpLeft || sensor_data-> bumpRight){
            break;
        }
        else
        {
            oi_update(sensor_data);
            sum += sensor_data->distance;
            // use -> notation since pointer
        }
    }

    oi_setWheels(0,0); //stop

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

    oi_setWheels(0,0); //stop

    return (sum);
}

double turn_right(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(250, -250); //move forward at full speed

    while (sum <= (degrees - 7))
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0,0); //stop

    return sum;
}

double turn_left(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-250, 250); //move forward at full speed

    while ((sum * -1)<= (degrees - 7))
    {
        oi_update(sensor_data);
        sum += sensor_data -> angle; // use -> notation since pointer
    }


    oi_setWheels(0,0); //stop

    return sum;
}

double maneuver(double distance_mm, oi_t *sensor_data)
{
    double distance = 0;
    while(distance < distance_mm)
    {
        distance += move_forward(sensor_data, distance_mm - distance);

        if(sensor_data->bumpLeft && sensor_data->bumpRight)
        {
            move_backwards(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data,90);
            distance -= 150;
        }
        else if(sensor_data->bumpLeft)
        {
            move_backwards(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data,90);
            distance -= 150;
        }
        else if(sensor_data->bumpRight)
        {
            move_backwards(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data,90);
            distance -= 150;
        }
    }

    return 1;
}

