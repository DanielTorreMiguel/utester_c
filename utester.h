#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdbool.h>

#define ERROR_NULL_PARAMETER -1
#define ERROR_COULD_NOT_OPEN_FILE -2
#define LOGGING_NOT_ENABLED 1

/**
 * Disables logging, won't return error if logging is not enabled.
 */
void u_disable_logging();


/**
 * Enables the module to output test results to logs
 * @param filename name of the log file
 */
int u_enable_logging(char *filename);


/**
 * Prints error messages to console and logfile depending on test results.
 * @param message message to print on test failed (test == false)
 * @param test test result
 * @param test_name optional flavor, adds a name to TEST FAILED and TEST SUCCESS messages.
 */
int u_assert(char *message, bool test, char *test_name);

#endif