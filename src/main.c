/**
 *   \file main.c
 *   \brief Main file of the P8-shell
 *
 *  This file contains the main function of the P8-shell. Also contains the
 *  FIXMEs and TODOs of the project.
 *
 */

#define _GNU_SOURCE
#include "utls.h"
#include <errno.h>
#include <linux/binfmts.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 *  \ref DEB acts as a switch wether the debug features should be activated or
 *  not. The value 1 turns them on, while the value 0 turns them off. In release
 *  builds, the debug features should be turned off.
 */

/**
 *  \ref DEB acts as a switch to turn on and off debug features. The value 1
 *  turns them on, whilst the value 0 turns them off. With a decent compiler, the
 *  debug features should not even compile if the value of DEB is set to 0. The
 *  value is automatically set by the processor from the CMake values.
 *  If you wish to have a debug compilation, use the command\n
 *  `cmake -DCMAKE_BUILD_TYPE=Debug ..`\n
 *  in the `build` directory. This will compile the P8-Shell in the `debug`
 *  directory. Otherwise, use the\n
 *  `cmake -DCMAKE_BUILD_TYPE=Release`\n
 *  command in the `build` directory. This will compile the P8-Shell in the `bin`
 *  directory.
 */
#ifdef Debug
#define DEB if (1)
#else
#define DEB if (0)
#endif

/*****************************************************************************/
/*                              FIXMEs and TODOs                             */
/*****************************************************************************/

/* FIXME:
   - Cannot handle whitespaces in arguments yet (such as escaped whitespaces or
     strings between quotation marks)
   - Change tilde (`~`) in paths with home directory from environment "HOME"
     variable
*/

/* TODO:
   - Implement pipes
   - Implement keyboard shortcuts such as C-c to stop current process, but not
     the console itself
*/

/*****************************************************************************/
/*                                DEFINITIONS                                */
/*****************************************************************************/

extern char **environ; /*!< External variable to the POSIX environment */

/*****************************************************************************/
/*                               MAIN FUNCTION                               */
/*****************************************************************************/

int main(void) {
  int i;
  char *ln;

  /* while "exit" has not been typed */
  while (1) {
    ln = getln();
    if(is_exit(ln))
      exit(0);

    DEB { print_debug(ln); }

    /* Changes the input string to an array of strings originally separated by a
     * whitespace character
     */
    char **arg = str_to_array(ln, " ");
    DEB {
      for (i = 0; arg[i]; ++i)
        printf("arg[%d] = %s\n", i, arg[i]);
    }

    /*
     * Testing first the built-in functions
     */

    /*
     * As for now, if there is a whitespace in the path, the shell will not be
     * able to detect is as part of the path, even if escaped or if the path is
     * quoted.
     */
    if (is_cd(arg[0])) {

      char directory[1024];

      getcwd(directory, sizeof(directory));
      printf("In directory %s\n", directory);

      DEB {
        getcwd(directory, sizeof(directory));
        printf("In directory %s\n", directory);
        printf("\"cd\" detected, passing argument \"%s\"\n", arg[1]);
      }

      if (chdir(arg[1]) == 0) {
        DEB {
          getcwd(directory, sizeof(directory));
          printf("In directory %s\n", directory);
        }
      } else {
        printf("Could not execute `cd %s`\n", arg[1]);
      }
      continue;
    }

    /*
     * Else will try to execute local or installed binaries
     */

    pid_t pid = fork();

    if (pid > 0) { /* host process */
      int return_code;
      /* waiting the child process to execute */
      waitpid(pid, &return_code, WUNTRACED);

      DEB {
        printf(
            "Father process: Child process executed, waitpid(%d) returned %d\n",
            pid, return_code);
      }

    } else if (pid == 0) { /* hosted process */
      execvp(arg[0], arg);
      perror("Could not execute execvp()");
      exit(1);
    } else { /* fork failed */
      fprintf(stderr, "Error, fork() failed, exiting...");
      exit(1);
    }
    /* execvp(arg[0], arg); */
  }

  return 0;
}
