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

/**
 *  \ref DEB acts as a switch to turn on and off debug features. The value 1
 *  turns them on, whilst the value 0 turns them off. With a decent compiler, the
 *  debug features should not even compile if the value of DEB is set to 0. The
 *  value is automatically set by the processor from the CMake values.
 *  If you wish to have a debug compilation, use the command\n
 *  `cmake -DCMAKE_BUILD_TYPE=Debug ..`\n
 *  in the `build` directory. This will compile the P8-Shell in the `debug`
 *  directory. Otherwise, use the\n
 *  `cmake -DCMAKE_BUILD_TYPE=Release ..`\n
 *  command in the `build` directory. This will compile the P8-Shell in the `bin`
 *  directory.
 */
#ifdef Debug
#define DEB if (1)
#else
#define DEB if (0)
#endif

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

/**
 *  \brief Checks if console input is the cd command
 *
 *  The fuction will return true if the string is identical to the C string
 *  "cd", false otherwise.
 *
 *  \param str C string to check
 *  \return bool
 */
bool is_cd(char *str);

/**
 *  \brief Evaluates the tilde in a path as the value of $HOME
 *
 *  Evaluates the tilde in the path passed as argument. The string passed as
 *  argument will be modified in order replace the tilde to the value held in the
 *  environment's variable $HOME. This will work only if the tilde is at the
 *  beginning of the string and is immediately followed by a slash or by the null
 *  character, i.e. this function won't do anything on strings such as "~me",
 *  "temp~/" or "file.c~"
 *
 *  \param str String in which the tilde has to be evaluated
 *  \return void
 */
char* home_eval(char *str);

/*****************************************************************************/
/*                             built-in functions                            */
/*****************************************************************************/

/**
 *  \brief cd command
 *
 *  Will change the working directory to the one specified in the path argument
 *
 *  \param path Directory to change the working directory to
 *  \return Returns 0 if succeeded, -1 otherwise
 */
int cd(char* path);

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
