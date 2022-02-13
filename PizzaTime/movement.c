/*
 * movement.c
 *
 * The main functions of the autonomous pizza robot. This class moves the robot around the test field
 * and dodges obstacles as well as delivering pizza to the customer at the homebase
 *
 *  Created on: Feb 11, 2021
 *      Author: Brayden Lamb, Drake Dodson, Logan Miller, Riley Lawson
 *
 */


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
double move_forward(oi_t *sensor_data, double distance_mm)
{

    oi_setWheels(500, 500); //move forward at full speed
    double sum = 0;

    while (sum <= distance_mm)
    {
        oi_update(sensor_data);

        // breaks the function if a sensor is triggered
        if (sensor_data->cliffRightSignal > 2600
                || sensor_data->cliffLeftSignal > 2600
                || sensor_data->cliffFrontLeftSignal > 2600
                || sensor_data->cliffFrontRightSignal > 2600
                || sensor_data->bumpLeft
                || sensor_data->bumpRight
                || sensor_data->cliffRight
                || sensor_data->cliffLeft
                || sensor_data->cliffFrontLeft
                || sensor_data->cliffFrontRight)
        {
            break;
        }
        // otherwise adds to sum the distance that has been traveled
        else
        {
            sum += sensor_data->distance;
            oi_update(sensor_data);
        }
    }

    oi_setWheels(0, 0); //stop

    return sum;
}

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
double move_backwards(oi_t *sensor_data, double distance_mm)
{
    oi_setWheels(-500, -500); //move forward at full speed
    double sum = 0;

    // Move
    while ((-1 * sum <= distance_mm))
    {

        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer
    }

    oi_setWheels(0,0); //stop

    return (sum);
}

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
double turn_right(oi_t *sensor_data, double degrees)
{
    double angle = 0;
    oi_setWheels(250, -250); //move forward at full speed


    while (angle < (degrees - 7))
    {
        oi_update(sensor_data);
        angle += sensor_data->angle; // use -> notation since pointer
    }

    oi_setWheels(0,0); //stop

    return angle;
}

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
double turn_left(oi_t *sensor_data, double degrees)
{
    double angle = 0;
    oi_setWheels(-250, 250); //move forward at full speed

    while (angle < (degrees - 7))
    {
        oi_update(sensor_data);
        angle -= sensor_data -> angle; // use -> notation since pointer
    }


    oi_setWheels(0,0); //stop

    return angle;
}

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
void maneuver(oi_t *sensor_data, float distance_mm)
{
    float distance = 0;
    oi_update(sensor_data);
    while (distance < distance_mm)
    {
        oi_update(sensor_data);
        distance += move_forward(sensor_data, distance);

        // Case for bumping left and right
        if (sensor_data->bumpLeft && sensor_data->bumpRight)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 100);
            turn_right(sensor_data, 90);
            distance += move_forward(sensor_data, 250);
        }
        // Case for bumping left
        else if (sensor_data->bumpLeft)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 100);
            turn_right(sensor_data, 90);
            distance += move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
        }
        // Case for bumping right
        else if (sensor_data->bumpRight)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 100);
            turn_left(sensor_data, 90);
            distance += move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);
        }

        // Case for when there is a cliff on the left
        else if (sensor_data->cliffLeft)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_right(sensor_data, 90);
            distance += move_forward(sensor_data, 300);
            turn_left(sensor_data, 90);
        }

        // Case for when there is a cliff on the right
        else if (sensor_data->cliffRight)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 90);
            distance += move_forward(sensor_data, 300);
        }
        // Case for when there is a cliff on the left
        else if (sensor_data->cliffFrontLeft)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_right(sensor_data, 90);
            distance += move_forward(sensor_data, 300);
        }
        // Case for when there is a cliff in the front right
        else if (sensor_data->cliffFrontRight)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 90);
            distance += move_forward(sensor_data, 300);
        }
        // Case for when the boundary is on the front right
        else if (sensor_data->cliffFrontRightSignal > 2600)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 113);
        }
        // Case for when the boundary is on the front left
        else if (sensor_data->cliffFrontLeftSignal > 2600)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 113);
        }
        // Case for when the boundary is on the right
        else if (sensor_data->cliffRightSignal > 2600)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 115);
        }
        // Case for when the boundary is on the left
        else if (sensor_data->cliffLeftSignal > 2600)
        {
            oi_update(sensor_data);
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 111);
        }
    }
}

/**
 * The main code that runs the autonomous pizza delivery. The code
 * inches towards the closest small peg and then runs a check for the
 * homebase
 *
 * @param sensor_data
 *  the cybot sensor data
 *
 */
void find_HomeBase(oi_t *sensor_data)
{
    int i;
    bool pizzaDelivered = false;
    bool goHome = false;
    Object_data objectInfo[20];
    Object_data redPegData[20];
    Object_data whitePegData[20];
    Object_data closestPeg;

    // Runs until a pizza is delivered
    while(!pizzaDelivered)
    {
        // Scans the items
        int numObjects = findObjects(objectInfo, 20);
        // Updates the elements in the objectInfo array with their respective object type
        peg_check(objectInfo, numObjects);
        // Updates the white peg array and the red peg array
        int numRedPegs = updateRedPegArray(redPegData, objectInfo, numObjects);
        int numWhitePegs = updateWhitePegArray(whitePegData, objectInfo, numObjects);

        uart_sendStr("\n\rAll\n\r\n\r");
        outputPegData(objectInfo, numObjects);
        uart_sendStr("Red\n\r\n\r");
        outputPegData(redPegData, numRedPegs);
        uart_sendStr("White\n\r\n\r");
        outputPegData(whitePegData, numRedPegs);

        // Runs through all of the data in the red array and saves the closest value
        if (numRedPegs >= 1)
        {
            closestPeg = redPegData[0];
            for (i = 0; i < numRedPegs; i++)
            {
                if (redPegData[i].distance < closestPeg.distance)
                {
                    closestPeg = redPegData[i];
                }
            }
        }
        // if the distance of a red peg is within 32 cm then use the go home function
        if(numRedPegs >= 1)
        {

            for(i = 0; i < numRedPegs; i++)
            {
                if(redPegData[i].distance < 32)
                {
                    goHome = true;
                }
            }


            // Runs the go home function
            if(goHome)
            {
                // returns true if the pizza was delivered
                pizzaDelivered = homebase_check(sensor_data);
                closestPeg = redPegData[0];

                // if the homebase was not reached run this code
                if(!pizzaDelivered)
                {
                    // If we return from homebase scan again
                    move_backwards(sensor_data, 100);
                    uart_sendStr("\n\r*** Navigation Failed, Scanning Values again ***\n\r");
                    numObjects = findObjects(objectInfo, 20);
                    peg_check(objectInfo, numObjects);
                    numRedPegs = updateRedPegArray(redPegData, objectInfo, numObjects);
                    numWhitePegs = updateWhitePegArray(whitePegData, objectInfo,numObjects);

                    uart_sendStr("\n\rAll\n\r\n\r");
                    outputPegData(objectInfo, numObjects);
                    uart_sendStr("Red\n\r\n\r");
                    outputPegData(redPegData, numRedPegs);
                    uart_sendStr("White\n\r\n\r");
                    outputPegData(whitePegData, numWhitePegs);

                    // look for the closest peg again
                    for (i = 0; i < numRedPegs; i++)
                    {
                        if (redPegData[i].distance < closestPeg.distance)
                        {
                            closestPeg = redPegData[i];
                        }
                    }
                }
            }
            // Points towards the peg with a slight offset inorder to more
            // likely pick up a second peg for homebase_check
            if (closestPeg.angle <= 90 && !pizzaDelivered)
            {
                turn_left(sensor_data, (90 - angle - 5));
            }
            else if (closestPeg.angle > 90)
            {
                turn_right(sensor_data, (closestPeg.angle - 90 + 5));
            }
            // If the closest peg is a greater distance than thirty move 30 cm forward
            if(closestPeg.distance > 80 && !pizzaDelivered)
            {
                maneuver(sensor_data, 300);
            }
        }
        // If no pegs are detected move forward 30 cm
        else
        {
            maneuver(sensor_data, 300);
        }
    }
    // If the pizza has been delivered, run the pizza time protocol
    if(pizzaDelivered)
    {
        uart_sendStr("\n\rPizza Time!!!\n\r");
        PIZZATIME();
        lcd_printf("Pizza Time!");
    }

}


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
bool park(oi_t *sensor_data, float distance)
{
    int i = 0;
    int j = 0;
    Object_data object[20];
    Object_data redPegData[20];
    Object_data whitePegData[20];

    int numObjects = findObjects(object, 20);
    peg_check(object, numObjects);
    int numRedPegs = updateRedPegArray(redPegData, object, numObjects);
    int numWhitePegs = updateWhitePegArray(whitePegData, object, numObjects);

    // Sees how many objects there are on the sides or in the path of the cybot
    for(i = 0; i < numObjects; i++)
    {
        if((object[i].distance <= (distance + 5)) && (object[i].distance >= (distance - 5.0)))
        {
            j++;
        }
    }

    // If there is ever three objects then that means that there is an obstacle in the way
    if(j >= 3)
    {
        // Moves another side of the cybot
        uart_sendStr("\n\r *** Obstacle in way of Navigation *** \n\r");
        move_backwards(sensor_data, 50);
        turn_right(sensor_data, 90);
        maneuver(sensor_data, 700);
        turn_left(sensor_data, 90);
        move_forward(sensor_data, 80);
        return false;
    }

    // Move_forward the distance
    move_forward(sensor_data, (distance * 10) + 285);

    // checks to see if the robot ran into any other objects that may be in it's way
    //  i.e short pegs
    if (sensor_data->cliffRightSignal > 2600
            || sensor_data->cliffLeftSignal > 2600
            || sensor_data->cliffFrontLeftSignal > 2600
            || sensor_data->cliffFrontRightSignal > 2600
            || sensor_data->bumpLeft
            || sensor_data->bumpRight
            || sensor_data->cliffRight
            || sensor_data->cliffLeft
            || sensor_data->cliffFrontLeft
            || sensor_data->cliffFrontRight)
    {
        uart_sendStr("\n\r *** Obstacle in way of Navigation *** \n\r");
        move_backwards(sensor_data, 50);
        turn_right(sensor_data, 90);
        move_forward(sensor_data, 300);
        maneuver(sensor_data, 400);
        turn_left(sensor_data, 90);
        move_forward(sensor_data, 80);
        return false;
    }

    // Return true for a succesful park
    return true;
}

/**
 * Helper method for detecting cliffs (and objects) when navigating to specific locations
 *
 * @param sensor_data
 *  cybot sensor information
 * @return
 *  if a cliff was detected or if it wasn't detected
 */
bool cliff_detected(oi_t *sensor_data){
    if(sensor_data->cliffRight || sensor_data->cliffLeft  || sensor_data->bumpLeft ||
            sensor_data->bumpRight || sensor_data->cliffFrontLeft || sensor_data->cliffFrontRight)
    {
        // Turns around and maneuvers away
        turn_right(sensor_data, 180);
        maneuver(sensor_data, 400);
        return true;
    }
    return false;
}

/**
 * This function does a lot of trigonometry to figure out specific angles for the
 * cybot to move in order to make it into the home base
 *
 * @param sensor_data
 *  cybot sensor information
 * @return
 *  true if the function has delievered the pizza, false otherwise
 */
bool homebase_check(oi_t *sensor_data)
{
    int i = 0;
    int j = 0;

    // pythAgorean distances A and B
    float pythA = 0.0;
    float pythB = 0.0;

    // The distance c or the distance of the base entrance
    float c = 0.0;
    bool pizzaDelivered = false;
    bool reset = false;

    // Law of cosines angles A, B, C
    int angleA = 0;
    int angleB = 0;
    int angleC = 0;

    Object_data closestPeg1;
    Object_data closestPeg2;

    Object_data objectInfo[20];
    Object_data redPegData[20];
    Object_data whitePegData[20];

    // Run until a reset to the find_homebase function is needed
    while (!pizzaDelivered && !reset)
    {
        // Scan the objects and update their respective arrays
        int numObjects = findObjects(objectInfo, 20);
        peg_check(objectInfo, numObjects);
        int numRedPegs = updateRedPegArray(redPegData, objectInfo, numObjects);
        int numWhitePegs = updateWhitePegArray(whitePegData, objectInfo, numObjects);

        outputPegData(objectInfo, numObjects);
        outputPegData(redPegData, numRedPegs);

        // If there are two redPegs detected, a move into the home base can be attempted
        if (numRedPegs >= 2)
        {
            // Initalize closestPeg1 and closestPeg2
            if (redPegData[1].distance > redPegData[0].distance)
            {
                closestPeg1 = redPegData[0];
                closestPeg2 = redPegData[1];
            }
            else
            {
                closestPeg1 = redPegData[1];
                closestPeg2 = redPegData[0];
            }

            // Check for two closest pegs
            for (i = 2; i < numRedPegs; i++)
            {
                if (redPegData[i].distance < closestPeg2.distance
                        || redPegData[i].distance < closestPeg1.distance)
                {
                    if (closestPeg1.distance > redPegData[i].distance)
                    {
                        closestPeg2 = closestPeg1;
                        closestPeg1 = redPegData[i];
                    }
                    else if (redPegData[i].distance < closestPeg2.distance)
                    {
                        closestPeg2 = redPegData[i];
                    }
                }
            }

            // Calculates the angle of C
            angleC = abs(closestPeg2.angle - closestPeg1.angle);

            // Uses law of cosines to find the distance c
            c = sqrtf(powf(closestPeg1.distance, 2) + powf(closestPeg2.distance, 2) - (2 * closestPeg2.distance * closestPeg1.distance
                     * cosf((angleC * M_PI) / 180)));

            char str1[20];
            sprintf(str1, "\n\r***   Distance between: %f  ***\n\r", c);

            // If C isn't approximately the same size as the real value of 60
            // then two pegs aren't the correct home base pegs
            if(c > 69 && c < 50)
            {
                reset = true;
            }

            uart_sendStr(str1);
            if (!reset)
            {
                uart_sendStr(str1);
                uart_sendStr("\n\r***           2 Red Pegs detected          ***\n\r");
                uart_sendStr("\n\r*** Path found attempting to deliver pizza ***\n\r");

                // Move into home base from the Left side, away from pegs
                if ((closestPeg1.angle < closestPeg2.angle) && (angleC < 50))
                {
                    angleB = (acos((pow(c, 2) + pow(closestPeg2.distance, 2)- pow(closestPeg1.distance, 2))
                                    / (2 * c * closestPeg2.distance))) * 180/ M_PI;

                    // Point to farthest away peg
                    if (closestPeg2.angle < 90)
                    turn_left(sensor_data, 90 - closestPeg2.angle);
                    else
                    turn_right(sensor_data, closestPeg2.angle - 90);

                    // Adjust parallel to C
                    turn_right(sensor_data, angleB);

                    // Use law of sins to get the distance B
                    pythB = (closestPeg1.distance * sinf((angleB + angleC) / 180.0 * M_PI));
                    // Use pythagoreans to
                    pythA = sqrt((powf(closestPeg1.distance, 2) - powf(pythB, 2)));


                    move_forward(sensor_data,(c / 2 * 10) + (pythA * 10) + 100);

                    if(!cliff_detected(sensor_data))
                    {
                        turn_left(sensor_data, 90);
                        pizzaDelivered = park(sensor_data, pythB);
                    }
                    else
                    {
                        pizzaDelivered = false;
                        reset = true;
                    }
                }
                // On right side away from both pegs
                else if ((closestPeg1.angle > closestPeg2.angle) && (angleC < 50))
                {
                    angleB = (acos((pow(c, 2) + pow(closestPeg2.distance, 2)- pow(closestPeg1.distance, 2))
                                    / (2 * c * closestPeg2.distance))) * 180/ M_PI;

                    // Point to farthest away peg
                    if(closestPeg2.angle < 90)
                    turn_left(sensor_data, 90 - closestPeg2.angle);
                    else
                    turn_right(sensor_data, closestPeg2.angle - 90);

                    // Adjust perpendicular
                    turn_left(sensor_data, angleB);
                    //float part1 = 1;
                    //float part2 = sinf((angleB + angleC) / 180.0 * M_PI);
                    pythB = (closestPeg1.distance * sinf((angleB + angleC) / 180.0 * M_PI));

                    pythA = sqrt((powf(closestPeg1.distance, 2) - powf(pythB, 2)));

                    move_forward(sensor_data, (c / 2 * 10) + (pythA * 10) + 80);

                    if(!cliff_detected(sensor_data))
                    {
                        turn_right(sensor_data, 90);
                        pizzaDelivered = park(sensor_data, pythB);
                    }
                    else
                    {
                        pizzaDelivered = false;
                        reset = true;
                    }
                }
                // On Left Side of cybot, in between pegs
                else if ((closestPeg1.angle > closestPeg2.angle) && (angleC >= 50))
                {
                    angleA = (acos((pow(c, 2) + pow(closestPeg2.distance, 2) - pow(closestPeg1.distance, 2))
                                    / (2 * c * closestPeg2.distance))) * 180/ M_PI;

                    // Adjust perpendicularly
                    if(closestPeg2.angle < 90)
                    turn_left(sensor_data, 90 - closestPeg2.angle);
                    else
                    turn_right(sensor_data, closestPeg2.angle - 90);
                    turn_left(sensor_data, angleA);
                    //float part1 = 1;
                    //float part2 = sinf((angleB + angleC) / 180.0 * M_PI);
                    pythB = (closestPeg1.distance * sinf((angleB + angleC) / 180.0 * M_PI));

                    pythA = sqrt((powf(closestPeg1.distance, 2) - powf(pythB, 2)));

                    move_forward(sensor_data, (c/2 * 10) - (pythA * 10) - 80);
                    if(!cliff_detected(sensor_data))
                    {
                        turn_right(sensor_data, 90);
                        pizzaDelivered = park(sensor_data, pythB);
                    }
                    else
                    {
                        pizzaDelivered = false;
                        reset = true;
                    }

                }
                // On Right Side of cybot, in between pegs
                else if ((closestPeg1.angle < closestPeg2.angle) && (angleC >= 54))
                {
                    angleA = (acos((pow(c, 2) + pow(closestPeg2.distance, 2) - pow(closestPeg1.distance, 2))/ (2 * c * closestPeg2.distance))) * 180/ M_PI;

                    // Adjust perpendicularly
                    if(closestPeg2.angle < 90){
                        turn_left(sensor_data, 90 - closestPeg2.angle);
                    }
                    else{
                         turn_right(sensor_data, closestPeg2.angle - 90);
                    }

                    turn_right(sensor_data, angleA);
                    pythB = (closestPeg1.distance * sinf((angleB + angleC) / 180.0 * M_PI));

                    pythA = sqrt((powf(closestPeg1.distance, 2) - powf(pythB, 2) + 10));

                    move_forward(sensor_data, (c/2 * 10) - (pythA * 10) - 80);
                    if(!cliff_detected(sensor_data))
                    {
                        turn_left(sensor_data, 90);
                        pizzaDelivered = park(sensor_data, pythB);
                    }
                    else
                    {
                        pizzaDelivered = false;
                        reset = true;
                    }
                }
            }
        }
        // Move backwards slightly a maximum of 4 times until either two pegs are found or nothing is found
        else if(numRedPegs == 1 && j <= 4 && !reset)
        {
            closestPeg1 = redPegData[0];
            if(j <= 4 && closestPeg1.distance < 45)
            {
                j++;
                move_backwards(sensor_data, 5);
            }
            else
            {
                reset = true;
            }
        }
        // Move backwards and move left slightly
        else if(!reset)
        {
            uart_sendStr("*** Re-Calibrating ***\n\r\n\r");
            move_backwards(sensor_data, 50);
            turn_left(sensor_data, 30);
            pizzaDelivered = false;
            reset = true;
        }
    }

    // The status of the pizza delivery
    return pizzaDelivered;
}

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
int updateWhitePegArray(Object_data whitepegs[], Object_data scandata[], int sizeofObjects)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < sizeofObjects; i++)
    {
        if(scandata[i].type == WhitePeg)
        {
            whitepegs[j] = scandata[i];
            j++;
        }
    }
    return j;
}

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
int updateRedPegArray(Object_data redpegs[], Object_data scandata[], int sizeofObjects)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < sizeofObjects; i++)
    {
        if(scandata[i].type == RedPeg)
        {
            redpegs[j] = scandata[i];
            j++;
        }
    }
    return j;
}

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
bool whiteOrRed(float distance, float width, int angle)
{
    if(angle > 30 && angle < 130)
    {
        if(width < 7.8 && width > 1.5 && distance <= 40)
        {
            return true;
        }
        else if(width < 7.8 && distance > 40 && distance <= 53)
        {
            return true;
        }
        else if(width < 7.8 && distance > 52 && distance <= 75)
        {
            return true;
        }
        else if(width < 7.8 && distance > 75 && distance <= 87.9)
        {
            return true;
        }
        else if(width < 7.8 && distance && width > 3.23 > 87.9)
        {
            return true;
        }
    }
    else
    {
        if(width < 7.8 && width > 1.9 && distance <= 40)
        {
            return true;
        }
        else if(width < 7.8 && distance > 40 && distance <= 60)
        {
            return true;
        }
        else if(width < 7.8 && distance > 60 && distance <= 86)
        {
            return true;
        }
        else if(width < 7 && width > 3.23 && distance > 86)
        {
            return true;
        }
    }

    return false;
}

/**
 * Runs through all of the elements in a search and updates their value with
 *
 * @param objectArr
 *  the data to be looked through
 * @param objectSize
 *  the number of objects in objectArr
 */
void peg_check(Object_data objectArr[], int objectSize)
{
    int i = 0;
    for(i = 0; i < objectSize; i++)

    // If values are less than 3.1 they are considered incomplete
    if(objectArr[i].width < 3.1)
    {
        objectArr[i].type = Incomplete;
    }
    else if(whiteOrRed(objectArr[i].distance, objectArr[i].width, objectArr[i].angle))
    {
        objectArr[i].type = RedPeg;
    }
    else
    {
        objectArr[i].type = WhitePeg;
    }
}

/**
 * Outputs the peg data of a given array, excluding their type
 *
 * @param object
 *  the array of type Object_data to be output
 * @param numObjects
 *  the number of objects that are withing object
 *
 */
void outputPegData(Object_data object[], int numObjects)
{
    char string[300] = "";
    int i = 0;
    uart_sendStr("Object#\t\tAngle\t\tDistance\tWidth\n\r");
    for (i = 0; i < numObjects; i++)
    {
        sprintf(string, "%d\t\t%d\t\t%f\t%f\n\r", i + 1, object[i].angle, object[i].distance, object[i].width);
        uart_sendStr(string);
    }
}

/**
 * The most important part of the whole code. Outputs the Pizza time image to the uart when the pizza has been delivered
 */
void PIZZATIME()
{
    uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....                 ....,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,.       ..,,,*****,.,*****,,,.        .,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,.      .,**************,.,**************,.     ..,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,..    .,*******************,.,*******************,.    .,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,.   .,,**********************,.,**********************,.    .,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,.    ,**************************,.,*************************,.   .,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,.    .,***************************,.,***************************,    .,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,.   ,*,,***************************,.,***************************,.*.   .,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,.   .***..***************************. .***************************..***.   ,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,.   ,****,.,***********************,..,.,.,************************,.,****,   .,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,.  .,*****,.,*********************,.,,*,.,*,..,*********************,.******,   .,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,.  .,*******.,*******************,.,****,.,****,.,*******************,,*******,   .,,,,,,,,\n\r");
     uart_sendStr(",,,,,.  .,********,.,**************,..,*******,.,*******,.,,**************,.*********,   ,,,,,,,,\n\r");
     uart_sendStr(",,,,,.  ,**********..********,  .,************,.************,,.  .,,*****,.,**********,  .,,,,,,,\n\r");
     uart_sendStr(",,,,.  .***********. ,************************,.************************,. ,***********.  ,,,,,,,\n\r");
     uart_sendStr(",,,,. .,***********...,***********************,.************************,...***********,. .,,,,,,\n\r");
     uart_sendStr(",,,,  .***********,.*,.***********************,.,**********************,.,,.,***********. .,,,,,,\n\r");
     uart_sendStr(",,,,  .**********,.,**,.**********************,.,*********************,.,**,.,**********. .,,,,,,\n\r");
     uart_sendStr(",,,,  .*********..*****,.*********************,.,********************,.,****,.,*********.  ,,,,,,\n\r");
     uart_sendStr(",,,,  .***..,,..,*******,.,*******************,.********************,.,*******,.,*,..***. .,,,,,,\n\r");
     uart_sendStr(",,,,  .**.    ,**********,.,*****************,. .,*****************,.,**********,    .,*. .,,,,,,\n\r");
     uart_sendStr(",,,,  .,,       ,*********,.,*************,..,,.,,..,*************.,**********.      .,,. .,,,,,,\n\r");
     uart_sendStr(",,,,  .*,          .,*******,.********,..,,***,.****,,.,,********.,*******,.          ,*. .,,,,,,\n\r");
     uart_sendStr(",,,,  .*.             .,*****,.,....,,********,.*********,,......,*****,.             ,*. .,,,,,,\n\r");
     uart_sendStr(",,,,  .,.      ##*.      .,*,...,*************,.**************,.,.,*,.      ,/%/      .*. .,,,,,,\n\r");
     uart_sendStr(",,,,. .,.     .&&@&@&#,     .***.,,***********,.************,.,**,.    .*#@@&&@%.     .,. .,,,,,,\n\r");
     uart_sendStr(",,,,.  ,.     *@@&@@@&&@&(.   .,**.,**********,.***********,.,*,    .#&@@@&&@@&&.     ,,  .,,,,,,\n\r");
     uart_sendStr(",,,,,  ,,.    *@@&@@@@&@@&@&(.   ,,.,*********,.,*********,.,.   ,#&@&&&&&@&&&@&.    .*.  ,,,,,,,\n\r");
     uart_sendStr(",,,,,  .*.    .&&@&&@@@&&@&&@&#.   ,..********,.,*******,...   ,%@&@@&@&&&@&&&@%.    ,*. .,,,,,,,\n\r");
     uart_sendStr(",,,,,. .,*.    #@&@@&&&&@@&&@@&@#.  ...,******,.,******,..   ,%@&@&&&@&@@&@&&&@*    .*,  .,,,,,,,\n\r");
     uart_sendStr(",,,,,.  ...    .%@&@&&@@@@@@@&@@&&(   ..,*****,.,*****..   .(&&@&&@@@@@&&@&@@@#.   ....  .,,,,,,,\n\r");
     uart_sendStr(",,,,,,. .**,.   .%@@@@@@@@@@&@@&@&&#,   ..,***,.,**,,..   ,%@&&&&@@@@@@&&&&&&#.   .**,. .,,,,,,,,\n\r");
     uart_sendStr(",,,,,,.  ,***.   .#&@@@@@@@@@&&@&@&@%,    .,**,.,**..    *&@&@&@@@@@@@@&&@&&(    ,***.  .,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,. .****,.   *%@&@@&&@@&&&&@&&@#,     .,...,.     ,&@&&@&&@&&@@@@&@@%*   .****,. .,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,.  ,*****,    *#&@&@@&@&@@&&@&(.  .,*, **,.,*,   .#&@@&&&@&&&&&&&#,   .,*****.  .,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,. .,******,.    ,/#%&&&&&%(*.   ,***, ... ,***.   .*#%&&&&&%#/,    .,******,  .,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,.  .*********,.              .,****,.,***,.*****,.              .,*********. .,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,.  ,**********,.....    ..,*******.,*****.,*******,..    ....,,**********.  ,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,.  ,******,..********,..,,*****,,,*******.,*******..,********,..,******,  .,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,.  ,**,.,***************,.,***,.,********.,***..,***************..,**.  .,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,.   ,********************,.,,.,**,,,,***,.,,.*********************.   ,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,.  ,*********************. ..,,*****,,.  .********************,.  .,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,   ,*******************.,*************,.*******************,   ,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,   ,****************..***************,,****************,   ,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,.   ,*************..****************,.,*************.   ,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,.  .**********,.******************,.,**********.  .,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,.  .,******,.,*******************,.,******,.  .,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,.  .,****.,,,,,,...........,,,,,,.****,   .,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,.  .*..,,*******************,,.,,.  .,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.   .,*********************,.   ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..    ....,,,,,,....     ..,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.............,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n\r");
     uart_sendStr("\n\r");
}

