/**
 *   \file utls.h
 *   \brief Header of the utility functions
 *
 *  This file contains the declaration of most of the functions. Each one of
 *  them are stored by category thanks to the comments, and they are also
 *  documented here.
 *
 */

#ifndef P8CONSOLE_SRC_UTILS_H_
#define P8CONSOLE_SRC_UTILS_H_

#include <stdbool.h>

/*****************************************************************************/
/*                        string manipulation function                       */
/*****************************************************************************/

/**
 *  \brief Reads line input
 *
 *  Reads from the console a whole line and returns it as a char* (C string).
 *  The string ends with a line break '\n' and is null-terminated. If memory
 *  could not be allocated for the returned string, NULL is then returned.
 *
 *  \param void
 *  \return char*
 */
char *getln(void);

/**
 *  \brief Converts a string to an array of string
 *
 *  The fuction split the received string STR into an array of string, each of
 *  them being originally separated by the character SEP. The function returns
 *  then an array of string of type char**
 *
 *  \param str String to be split
 *  \param sep Separator
 *  \return char**
 */
char **str_to_array(char *str, const char *sep);

/*****************************************************************************/
/*                         string analysis functions                         */
/*****************************************************************************/

/**
 *  \brief Checks if console input is the exit command
 *
 *  The function will return true if the string is identical to the C string
 *  "exit", false otherwise.
 *
 *  \param str C string to check
 *  \return bool
 */
bool is_exit(char *str);

bool is_cd(char *str);

/*****************************************************************************/
/*                             built-in functions                            */
/*****************************************************************************/

int cd(char* str);

/*****************************************************************************/
/*                              debug functions                              */
/*****************************************************************************/

/**
 *  \brief Prints the received string
 *
 *  Prints the received string, one character per line, on each line as a
 *  character, as its hexadecimal value and as its decimal value. This function
 *  was made for debugging purposes and will not be included in release builds.
 *
 *  \param str String to be printed.
 *  \return void
 */
void print_debug(char*);

#endif /* P8CONSOLE_SRC_UTILS_H_ */
