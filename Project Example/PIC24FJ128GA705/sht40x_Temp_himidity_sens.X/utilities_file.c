

#include "utilies_file.h"
#define UTILITY_VERSION     2

static  uint8_t utility_index;

/**
 * @brief     tick count
 * @return    status code
 *            - system tick in milli seconds
 * @note      none
 */
uint32_t millis(void) {
    return u32MillisCounter;
}

/**
 * @brief     delay function in milli seconds
 * @param[in] msTime is time delay
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t delay_ms(uint32_t msTime) {

    volatile uint32_t delayCheck = millis();
    while ((millis() - delayCheck) < msTime);

    if (millis() - delayCheck < msTime) {
    }
    return 0;
}

/**
 * @brief     led toggle  non blocking callback
 * @param[in] *toggle_function is the led toggle function
 * @param[in] timeout is time toggle time interval
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 success
 *            - 1 failed
 * @note      none
 */
uint8_t led_toggle_non_blocking(void (*toggle_function)(void), uint32_t timeout, uint32_t tickCheck) {

    volatile bool statusComplete = false;
    if ((millis() - tickCheck) > (timeout)) {
        (*toggle_function)();
        statusComplete = true;
    }

    return statusComplete;
}

/**
 * @brief     Non blocking task callback function
 * @param[in] *task point to the task function callback
 * @param[in] timeout is time interval to run task routine
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t non_blocking_task(void (*task)(void), uint32_t timeout, uint32_t tickCheck) {
    volatile bool statusComplete = false;
    if ((millis() - tickCheck) > (timeout)) {
        (*task)();
        statusComplete = true;
    }
    return 0;
}

/**
 * @brief     Non blocking task callback function with address pointer to pass in
 * @param[in] *task point to the task function callback
 * @param[in] timeout is time interval to run task routine
 * @param[in] *parameter point to the argument to pass in
 * @param[in] tickCheck is the time track for system tick expiry time
 * @return    status code
 *            - 0 delay success
 *            - 1 delay failed
 * @note      none
 */
uint8_t non_blocking_task2(void (*task)(int), uint32_t timeout, uint32_t tickCheck, int *parameter) {
    volatile bool statusComplete = false;
    if ((millis() - tickCheck) > (timeout)) {
        (*task)((int*)&parameter);
        statusComplete = true;
    }
    return 0;
}

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
uint8_t non_blocking_task3(void (*task)(int, char*), uint32_t timeout, uint32_t tickCheck, int *pParameter, char *pTaskName) {
    volatile bool statusComplete = false;
    if ((millis() - tickCheck) > (timeout)) {
        (*task)((int*)&pParameter, pTaskName);
        statusComplete = true;
    }
    return 0;
}


/**
 * @brief convert hexadecimal to binary
 * @param[in] hex_number_in in the number to pass into the function
 * @param[out] *bin_number_out point to converted binary string
 * @return status code
 * @note the function currently support 2 byte greater
 */
void hex_to_bin(uint8_t hex_number_in, char *bin_number_out) {
    for (utility_index = 0; utility_index < 8; utility_index++) {
        if (hex_number_in & (0x80 >> utility_index))
            *bin_number_out = '1';
        else
            *bin_number_out = '0';

        bin_number_out++;
    }
    *bin_number_out = '\0';   /**<< end of line when convertion completes*/
}

