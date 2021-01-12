#include <stdio.h>
#include <stdbool.h>
#include "utester.h"

static bool enable_log = false;   //true when logging is enabled
static char *log_filename = NULL; //can't be NULL if logging is enabled

/**
 * Prints message to logfile
 * @param message message to print
 * @param filename name of logfile
 * @return ERROR_NULL_PARAMETER if one of them are NULL
 * @return ERROR_COULD_NOT_OPEN_FILE if file couldn't be opened for reasons other than filename = NULL
 * @return 0 on success
 */
static int print_to_logfile(char *message, char *filename)
{
    FILE *file;
    if (!enable_log)
    {
        return LOGGING_NOT_ENABLED;
    }
    if (NULL == message || NULL == filename) //check params
    {
        return ERROR_NULL_PARAMETER;
    }
    file = fopen(filename, "a"); //open logfile
    if (NULL == file)
    {
        return ERROR_COULD_NOT_OPEN_FILE;
    }
    fprintf(file, message);
    fflush(file);
    fclose(file);
    return 0;
}

/**
 * Prints error messages to console and logfile depending on test results.
 * @param message message to print on test failed (test == false)
 * @param test test result
 * @param test_name optional flavor, adds a name to TEST FAILED and TEST SUCCESS messages.
 */
int u_assert(char *message, bool test, char *test_name)
{
    char msg[100];
    int  err = 0;
    if (!test)
    {
        if (NULL != test_name) //optional flavor, prints test name
        {
            sprintf(msg, "TEST FAILED: %s\n", test_name);
            printf(msg);
            err = print_to_logfile(msg, log_filename);
            if (err < 0)
            {
                return err;
            }
        }
        else
        {
            //print message to console and optionally to file
            sprintf(msg, "TEST FAILED\n", test_name);
            printf(msg);
            err = print_to_logfile(message, log_filename);
            if(err < 0)
            {
                return err;
            }
        }
        printf(message);
        err = print_to_logfile(message, log_filename);
    }
    else
    {
        if (NULL != test_name) //optional
        {
            sprintf(msg, "TEST PASSED: %s\n", test_name);
            printf(msg);
            err = print_to_logfile(msg, log_filename);
        }
        else
        {
            sprintf(msg, "TEST PASSED\n");
            printf(msg);
            err = print_to_logfile(msg, log_filename);
        }
    }
    return err;
}

/**
 * Enables the module to output test results to logs
 * @param filename name of the log file
 */
int u_enable_logging(char *filename)
{
    //error check
    FILE *file;
    if (NULL == filename)
    {
        return ERROR_NULL_PARAMETER;
    }
    //enable loggin
    enable_log = true;
    log_filename = filename;
    //open logfile and error check
    file = fopen(filename, "a");
    if (NULL == file)
    {
        return ERROR_COULD_NOT_OPEN_FILE;
    }

    fprintf(file, "Logging enabled\n");
    fclose(file);
    return 0;
}

/**
 * Disables logging, won't return error if logging is not enabled.
 */
void u_disable_logging()
{
    FILE *file;
    if (enable_log)
    {
        //log it to file
        file = fopen(log_filename, "a");
        if (NULL != file)
        {
            fprintf(file, "logging disabled");
        }
        //Disable logging
        enable_log = false;
        log_filename = NULL;
    }
}
