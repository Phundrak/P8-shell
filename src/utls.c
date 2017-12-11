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

/* home_eval *****************************************************************/

char* home_eval(char *str) {
  char *res, *restemp;
  int i;

  /* If the string is not "~" nor does it begin with "~/", then do nothing */
  if (str[0] != '~' && !(str[1] == '/' || str[1] == '\0'))
    return str;

  char *home = getenv("HOME");

  DEB { printf("home: %s\n", home); }

  /* -1 to each, '~' removed in str, as well as the last null char in home */
  res = (char *)malloc(strlen(home - 1) + strlen(str - 1));
  restemp = res;

  for(i = 0; home[i]; ++i, ++restemp)
    *restemp = home[i];
  for(i = 1; str[i]; ++i, ++restemp)
    *restemp = str[i];
  /* final null char */
  *restemp = 0;
  printf("res: %s\n", res);

  restemp = NULL;

  return res;
}

/*****************************************************************************/
/*                         string analysis functions                         */
/*****************************************************************************/

/* strcomp *******************************************************************/

bool strcomp(char* str1, char* str2) {
  for(; *str1 && *str2 && *str1 == *str2; ++str1, ++str2)
    ;
  return *str1 == *str2;
}

/* to_background *************************************************************/
bool to_background(char** str) {
  int i;
  for(i = 0; str[i]; i++)
    ;
  if(!strcomp(str[i-1], "&"))
    return false;
  free(str[i]);
  str[i-1] = NULL;
  return true;
}

/*****************************************************************************/
/*                             build-in functions                            */
/*****************************************************************************/

/* cd ************************************************************************/

int cd(char* path) {
  return chdir(path);
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
