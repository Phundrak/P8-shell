#ifndef P8CONSOLE_SRC_UTILS_H_
#define P8CONSOLE_SRC_UTILS_H_

#include <stdbool.h>

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
char* getln(void);

/**
 *  \brief Checks if console input is the exit command
 *
 *  The function will return true if the string is identical to the C string
 *  "exit\n", false otherwise.
 *
 *  \param str C string to check
 *  \return bool
 */
bool is_exit(char *str);

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
char** str_to_array(char* str, const char *sep);

#endif /* P8CONSOLE_SRC_UTILS_H_ */
