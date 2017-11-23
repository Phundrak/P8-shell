#include "utls.h"
#include <linux/binfmts.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEB if (1)

void print_debug(char *str) {
  char* strdeb = str;
  while(*strdeb){
    printf("%c\t%02x\t%04d\n", *strdeb, *strdeb, *strdeb);
    strdeb++;
  }
}

int main(void) {
  int i;
  char *ln = "dummy";

  /* while "exit" has not been typed */
  while(!is_exit(ln)) {
    printf("$ ");
    ln = getln();
    DEB {
      print_debug(ln);
    }

    char **res = str_to_array(ln, " ");
    DEB {
      for (i = 0; res[i]; ++i)
        printf("res[%d] = %s\n", i, res[i]);
    }
  }

  return 0;
}
