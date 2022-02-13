/*
 * timer.h
 *
 *  Created on: Mar 15, 2019
 *      @author Isaac Rex
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"

/**
 * @brief Initialize and start the clock at 0. If the clock is
 * already running on a call, reset the time count back to 0. Uses TIMER5.
 *
 */
void timer_init(void);

/**
 * @brief Stop the clock and free up TIMER5. Resets the value returned by
 * getMillis() and getMicros().
 *
 */
void timer_stop(void);

/**
 * @brief Pauses the clock at the current value.
 *
 */
void timer_pause(void);

/**
 * @brief Resumes the clock after a call to pauseClock().
 *
 */
void timer_resume(void);

/**
 * @brief Returns the number milliseconds that have passed since startClock()
 * was called. Value rolls over after about 49 days.
 *
 * @return unsigned int number of milliseconds since a call to
 * timer_startClock()
 */
unsigned int timer_getMillis(void);

/**
 * @brief Returns the number of microseconds passed since a call to
 * startClock(). Value rolls over after about 71 minutes.
 *
 * @return unsigned int number of microseconds since a call to startClock()
 */
unsigned int timer_getMicros(void);

/**
 * @brief Pauses execution for the specified number of milliseconds.
 *
 * @param delay_time number of milliseconds to pause for
 */
void timer_waitMillis(unsigned int delay_time);

/**
 * @brief Pauses execution for the specified number of microseconds.
 *
 * @param delay_time number of microseconds to pause for
 */
void timer_waitMicros(unsigned int delay_time);

// TODO: Implement
/**
 * @brief Sets up an interrupt to call the given function once every given
 * milliseconds. Uses TIMER4 for the countdown. Function f executes inside an
 * ISR, so keep the passed function as short as possible. Maximum interval time
 * is TODO: calculate
 *
 * @param f the function to call
 * @param millis the interval between calls
 */
void timer_fireEvery(void (*f)(void), int millis);

// TODO: Implement
/**
 * @brief Sets up an interrupt to call the given function after the given number
 * of milliseconds. Uses TIMER4 for the countdown, and thus can only be used
 * when timer_fireEvery() and timer_fireFor() are not being used. Function f
 * executes inside an ISR and should be kept as short as possible.
 *
 * @param f the function to call
 * @param millis milliseconds until call
 */
void timer_fireOnce(void (*f)(void), int millis);

// TODO: Implement
/**
 * @brief Sets up an interrupt to call the given function after the given number
 * of milliseconds for the given number of times. Uses TIMER4 for the countdown,
 * and thus can only be used when fireOnce() and fireEvery() are not being used.
 * Function f executes inside an ISR and should be kept as short as possible.
 * Maximum interval time is TODO: calculate
 *
 * @param f the function to call
 * @param millis milliseconds until call
 * @param times number of times to call f
 */
void timer_fireFor(void (*f)(void), int millis, int times);

/**
 * @brief ISR handler to increment the timeout variable for tracking total
 * milliseconds
 *
 */
static void timer_clockTickHandler();

#endif /* TIMER_H_ */
