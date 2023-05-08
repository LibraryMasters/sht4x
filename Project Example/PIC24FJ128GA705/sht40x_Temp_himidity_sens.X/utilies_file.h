/* 
 * File:   utilies_file.h
 * Author: Cedricm
 *
 * Created on July 5, 2022, 12:59 PM
 */

#ifndef UTILIES_FILE_H
#define	UTILIES_FILE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define tickOffset     2 

#define _1000_MS_TIMEOUT     1000
#define _500_MS_TIMEOUT      500
#define _300_MS_TIMEOUT      300
#define _200_MS_TIMEOUT      200
#define _100_MS_TIMEOUT      100
#define _50_MS_TIMEOUT       50
#define _25_MS_TIMEOUT       25
#define _10_MS_TIMEOUT       10


extern volatile uint32_t u32MillisCounter; /**< increment every ms (elapse time since power reset)*/

/**
 * @brief     tick count
 * @return    status code
 *            - system tick in milli seconds
 * @note      none
 */
uint32_t millis(void);

/**
 * @brief     delay function in milli seconds
 * @param[in] msTime is time delay
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t delay_ms(uint32_t msTime);

/**
 * @brief     led toggle non blocking callback
 * @param[in] *toggle_function is the led toggle function
 * @param[in] timeout is time toggle time interval
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t led_toggle_non_blocking(void (*toggle_function)(void), uint32_t timeout, uint32_t tickCheck);

/**
 * @brief     Non blocking task 1 callback funct
 * @param[in] *task point to the task function callback
 * @param[in] timeout is time interval to run task routine
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t non_blocking_task(void (*task)(void), uint32_t timeout, uint32_t tickCheck);

/**
 * @brief     Non blocking task 2 callback function with address pointer to pass in
 * @param[in] *task point to the task function callback
 * @param[in] timeout is time interval to run task routine
 * @param[in] *parameter point to the argument to pass in
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t non_blocking_task2(void (*task)(int), uint32_t timeout, uint32_t tickCheck, int *parameter);

/**
 * @brief     Non blocking task callback function with address pointer and task name
 * @param[in] *task point to the task function callback
 * @param[in] timeout is time interval to run task routine
 * @param[in] *pParameter point to the argument to pass in
 * @param[in] tickCheck is the time track for system tick expiry time
 * @param[in] pTaskName point to the task name
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t non_blocking_task3(void (*task)(int, char*), uint32_t timeout, uint32_t tickCheck, int *pParameter, char *pTaskName);

/**
* @brief convert hexadecimal to binary
* @param[in] hex_number_in in the number to pass into the function
* @param[out] *bin_number_out point to converted binary string
* @return status code
* @note the function currently support 2 byte greater
*/
void hex_to_bin(uint8_t hex_number_in, char *bin_number_out);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILIES_FILE_H */

