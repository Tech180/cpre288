/*
*
*   uart.h
*
*   Used to set up the RS232 connector and WIFI module
*   Functions for communicating between CyBot and PC via UART1
*   Serial parameters: Baud = 115200, 8 data bits, 1 stop bit,
*   no parity, no flow control on COM1, FIFOs disabled on UART1
*
*   @author Dane Larson
*   @date 07/18/2016
*   Phillip Jones updated 9/2019, removed WiFi.h, Timer.h
*   Diane Rover updated 2/2020, changed receive return type to char
*/

#ifndef UART_H_
#define UART_H_

#include <inc/tm4c123gh6pm.h>

// UART1 device initialization for CyBot to PuTTY
void uart_init(void);

// Send a byte over UART1 from CyBot to PuTTY
void uart_sendChar(char data);

// CyBot waits (i.e. blocks) to receive a byte from PuTTY
// returns byte that was received by UART1
char uart_receive(void);

char uart_receive_nonblocking(void);

// Send a string over UART1
// Sends each char in the string one at a time
void uart_sendStr(const char *data);

#endif /* UART_H_ */
