/**
 *   \file main.c
 *   \brief Main file of the P8-shell
 *
 *  This file contains the main function of the P8-shell. Also contains the
 *  FIXMEs and TODOs of the project, and occasionally debug functions.
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
 *  turns them on, whilst the value 0 turns them off. With a decent compiler,
 * the debug features should not even compile if the value of DEB is set to 0.
 * The value is automatically set by the processor from the CMake values. If
 * you wish to have a debug compilation, use the command\n `cmake
 * -DCMAKE_BUILD_TYPE=Debug ..`\n in the `build` directory. This will compile
 * the P8-Shell in the `debug` directory. Otherwise, use the\n `cmake
 * -DCMAKE_BUILD_TYPE=Release ..`\n command in the `build` directory. This will
 * compile the P8-Shell in the `bin` directory.
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
*/

/* TODO:
   - Implement pipes
   - Evaluation of arguments beginnig with a dollar sign such as $HOME
   - Add the `!!` command
*/

/*****************************************************************************/
/*                                DEFINITIONS                                */
/*****************************************************************************/

extern char **environ; /*!< External variable to the POSIX environment */
pid_t pid = 0;         /*!< Global variable for the child process' PID */

/**
 *  \brief Displays current directory, used for debug purposes
 *  \return void
 */
void d_print_dir();

void kill_child(int sig);

/*****************************************************************************/
/*                               IMPLEMENTATION                              */
/*****************************************************************************/

void d_print_dir() {
  char directory[1024];

  getcwd(directory, sizeof(directory));
  printf("In directory %s\n", getenv("HOME"));
}

void kill_child(int sig) {
  if (pid != 0){
    kill(pid, SIGKILL);
    puts("\n");
  }
}

/*****************************************************************************/
/*                               MAIN FUNCTION                               */
/*****************************************************************************/

int main(void) {
  int i;
  char *ln;
  char **arg;

  signal(SIGQUIT, SIG_IGN);
  signal(SIGINT, kill_child);

  /* while `exit` has not been typed */
  while (1) {
    ln = getln();
    DEB { print_debug(ln); }

    /*
     * Changes the input string to an array of strings originally separated by a
     * whitespace character
     */
    arg = str_to_array(ln, " ");
    DEB {
      for (i = 0; arg[i]; ++i)
        printf("arg[%d] = %s\n", i, arg[i]);
    }

    if (strcomp(arg[0], "exit"))
      exit(0);

    /*************************************************************************/
    /*                  Testing first the built-in functions                 */
    /*************************************************************************/

    /* cd ********************************************************************/

    if (strcomp(arg[0], "cd")) {

      DEB {
        d_print_dir();
        printf("\"cd\" detected, passing argument \"%s\"\n", arg[1]);
      }

      if (!arg[1]) {
        if (chdir(getenv("HOME")) == 0) {
          DEB { d_print_dir(); }
        } else {
          printf("Could not execute `cd %s`\n", getenv("HOME"));
          continue;
        }
      } else {
        arg[1] = home_eval(arg[1]);
        if (chdir(arg[1]) == 0) {
          DEB { d_print_dir(); }
        } else {
          printf("Could not execute `cd %s`\n", arg[1]);
        }
      }
      continue;
    }

    /*************************************************************************/
    /*         Else, will try to execute local or installed binaries         */
    /*************************************************************************/

    pid = fork();

    /* host process **********************************************************/
    if (pid > 0) {
      int return_code;
      if (!to_background(arg)) /* waiting the child process to execute */
        waitpid(pid, &return_code, 0);
      else
        return_code = 0;

      DEB {
        printf(
            "Father process: Child process executed, waitpid(%d) returned %d\n",
            pid, return_code);
      }

    }
    /* hosted process ********************************************************/
    else if (pid == 0) {
      execvp(arg[0], arg);
      fprintf(stderr, "Error: command %s returned error code %d\n", arg[0], errno);
      exit(1);
    }
    /* fork failed ***********************************************************/
    else {
      fprintf(stderr, "Error, fork() failed, exiting...");
      exit(1);
    }

  }

  return 0;
}
