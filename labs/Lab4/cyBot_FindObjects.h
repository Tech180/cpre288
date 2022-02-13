/*
 * cyBot_FindObjects.h
 *
 *  Created on: Feb 17, 2021
 *  Updated on: Feb 22, 2021 (changes to width units)
 *      Author: Alexis Aurandt and Jackson Lopata
 */

#ifndef CYBOT_FINDOBJECTS_H_
#define CYBOT_FINDOBJECTS_H_

typedef struct{
    int angle; //degrees
    float distance; //cm
    float width; //cm
} cyBot_Object_t;

/**
  * @brief Finds objects during 0 to 180 degree scan
  * @param getObjects[]: passed in to store the results of the scan
  * @param size_of_input: size of getObjects[] array that was passed in
  * @retval Returns the number of objects found
  */
int cyBot_FindObjects(cyBot_Object_t getObjects[], int size_of_input);


#endif /* CYBOT_FINDOBJECTS_H_ */
