#define _GNU_SOURCE
#include "utls.h"
#include <errno.h>
#include <linux/binfmts.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define DEB if (0)

extern char **environ;

void print_debug(char *str) {
  char *strdeb = str;
  while (*strdeb) {
    printf("%c\t%02x\t%04d\n", *strdeb, *strdeb, *strdeb);
    strdeb++;
  }
}

int main(void) {
  int i;
  char *ln;

  ln = getln();

  /* while "exit" has not been typed */
  while (!is_exit(ln)) {
    DEB { print_debug(ln); }

    char **arg = str_to_array(ln, " ");
    DEB {
      for (i = 0; arg[i]; ++i)
        printf("arg[%d] = %s\n", i, arg[i]);
    }

    pid_t pid = fork();

    if(pid > 0) { /* host process */
      int return_code;
      /* waiting the child process to execute */
      waitpid(pid, &return_code, WUNTRACED);

      DEB {
        printf(
            "Father process: Child process executed, waitpid(%d) returned %d\n",
            pid, return_code);
      }
    } else if(pid == 0) { /* hosted process */
      execvp(arg[0], arg);
      perror("Could not execute execvp()");
    } else { /* fork failed */
      fprintf(stderr, "Error, fork() failed, exiting...");
      exit(1);
    }


    ln = getln();
    /* execvp(arg[0], arg); */
  }

  return 0;
}
