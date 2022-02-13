/*
*
*   uart.h
*
*   Used to set up the RS232 connector and WIFI module
*   uses UART1 at 115200
*
*
*   @author Dane Larson
*   @date 07/18/2016
*   @ Phillip Jones updated: 9/11/2019
*/

#ifndef CYBOT_UART_H_
#define CYBOT_UART_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inc/tm4c123gh6pm.h>


// Initialize the UART to communciate between CyBot and PuTTy
void cyBot_uart_init(void);

// Send a byte over the UART from CyBot and PuTTy (Buad Rate 115200, No Parity, No Flow Control)
void cyBot_sendByte(char data);

// Cybot WAITs to recive a byte from PuTTy (Buad Rate 115200, No Parity, No Flow Control).
// In other words, this is a blocking fucntion.
int cyBot_getByte(void);


#endif /* CYBOT_UART_H_ */
