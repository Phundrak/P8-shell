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
 *  Reads from the console a whole line and returns it as a `char*` (C string).
 *  The string ends with a line break `\n` and is null-terminated. If memory
 *  could not be allocated for the returned string, `NULL` is then returned.
 *
 *  \return Returns the line typed by the user
 */
char *getln(void);

/**
 *  \brief Converts a string to an array of string
 *
 *  The fuction split the received string `str` into an array of string, each of
 *  them being originally separated by the character `sep`. The function returns
 *  then a NULL terminated array of C strings.
 *
 *  \param[in] str String to be split
 *  \param[in] sep Separator
 *  \return Returns an array of strings, separated by `sep` in the original
 *  string `str`
 */
char **str_to_array(char *str, const char *sep);

/*****************************************************************************/
/*                         string analysis functions                         */
/*****************************************************************************/

/**
 *  \brief Checks if two strings are identical
 *
 *  The function will return `true` if the two strings passed as arguments are
 *  identical, `false` otherwise. The strings are not modified by the function.
 *
 *  \param[in] str1 First string to compare
 *  \param[in] str2 Second string to compare
 *  \return Returns `true` if the strings are identical, `false` otherwise
 */
bool strcomp(char* str1, char* str2);

/**
 *  \brief Evaluates the tilde in a path as the value of $HOME
 *
 *  Evaluates the tilde `~` in the path passed as argument. The string passed as
 *  argument will be modified in order replace the tilde to the value held in the
 *  environment's variable `$HOME`. This will work only if the tilde is at the
 *  beginning of the string and is immediately followed by a slash or by the null
 *  character, i.e. this function won't do anything on strings such as `~me`,
 *  `temp~/` or `file.c~`
 *
 *  \param[in] str String in which the tilde has to be evaluated
 *  \return Returs the string with the `~` changed to the correct home folder
 */
char* home_eval(char *str);

/**
 *  \brief Checks if the command his to be waited or not
 *
 *  This function receives the array of strings that are to be evaluated. If the
 *  last element is a `&`, then the forked process will not be waited by the
 *  parent process. The string "&" will also be set to `NULL` and the next
 *  element will be freed.
 *
 *  \param str Array of character to be evaluated
 *  \return Returns wether the new process should be waited
 */
bool to_background(char **str);

/*****************************************************************************/
/*                             built-in functions                            */
/*****************************************************************************/

/**
 *  \brief cd command
 *
 *  Will change the working directory to the one specified in the `path`
 *  argument
 *
 *  \param[in] path Directory to change the working directory to
 *  \return int
 */
int cd(char* path);

/**
 *  \brief repeat (`!!`) command
 *
 *  This function recreates the behavior of the `!!` command, that is repeat the
 *  last command passed by the user. If the command passed in `str` is `!!`,
 *  then the last command (passed in `last`) will be repeated, and the function
 *  will return `true`. Else, the function will return `false`.
 *
 *  \param[in] str Most recent input by the user
 *  \param[in] last Last input by the user
 *  \return bool
 */
bool repeat(char *str, char** last);

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
 *  \param[in] str String to be printed.
 *  \return void
 */
void print_debug(char*);

#endif /* P8CONSOLE_SRC_UTILS_H_ */
