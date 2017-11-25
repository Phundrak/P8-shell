/**
 *   \file utls.c
 *   \brief Definition of the utility functions
 *
 *  Body file of \ref utls.h where the utility functions are implemented.
 *
 */

#include "utls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*****************************************************************************/
/*                        string manipulation function                       */
/*****************************************************************************/

/* getln *********************************************************************/

char *getln(void) {
  char *line, *linep;
  size_t lenmax, len;
  int c;

  printf("$ ");

  line = (char *)malloc(1024 * sizeof(char));
  linep = line;
  lenmax = 1024;
  len = lenmax;

  if (!line)
    return NULL;

  for (;;) {
    c = fgetc(stdin);
    if (c == EOF || c == '\n')
      break;

    if (--len == 0) {
      len = lenmax;
      char *linen = realloc(linep, lenmax *= 2);

      if (linen == NULL) {
        free(linep);
        return NULL;
      }
      line = linen + (line - linep);
      linep = linen;
    }

    if ((*line++ = c) == '\n')
      break;
  }
  *line = '\0';
  return linep;
}

/* str_to_array **************************************************************/

char **str_to_array(char *str, const char *sep) {
  char **res = NULL;
  char *p = strtok(str, sep);
  int n_spaces = 0;

  /* split string and apend tokens to `res` */

  while (p) {
    res = realloc(res, sizeof(char *) * ++n_spaces);

    if (!res) {
      printf("Failed to allocate memory, exiting...\n");
      exit(1);
    }

    res[n_spaces - 1] = p;
    p = strtok(NULL, sep);
  }

  /* realloc one extra element for the last NULL */
  res = realloc(res, sizeof(char *) * (n_spaces + 1));
  res[n_spaces] = NULL;
  return res;
}

/*****************************************************************************/
/*                         string analysis functions                         */
/*****************************************************************************/

/* is_exit *******************************************************************/

bool is_exit(char *str) {
  int i;
  char *exit = "exit";
  for (i = 0; i < 5 && str[i]; ++i)
    if (str[i] != exit[i])
      return false;
  return true;
}

/* is_cd *********************************************************************/

bool is_cd(char* str) {
  int i;
  char *cd = "cd";
  for(i = 0; i < 3 && str[i]; ++i)
    if(str[i] != cd[i])
      return false;
  return true;
}

/*****************************************************************************/
/*                             build-in functions                            */
/*****************************************************************************/

int cd(char* str) {
  return chdir(str);
}

/*****************************************************************************/
/*                              debug functions                              */
/*****************************************************************************/

/* print_debug ***************************************************************/

void print_debug(char *str) {
  char *strdeb = str;
  while (*strdeb) {
    printf("%c\t%02x\t%04d\n", *strdeb, *strdeb, *strdeb);
    strdeb++;
  }
}
