#include "utls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getln(void) {
  char *line, *linep;
  size_t lenmax, len;
  int c;

  line = (char *)malloc(1024 * sizeof(char));
  linep = line;
  lenmax = 1024;
  len = lenmax;

  if (!line)
    return NULL;

  for (;;) {
    c = fgetc(stdin);
    if (c == EOF)
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

bool is_exit(char *str) {
  int i;
  char *exit = "exit\n";
  for (i = 0; i < 5 && str[i]; ++i)
    if (str[i] != exit[i])
      return false;
  return true;
}

char** str_to_array(char* str, const char *sep){
  char **res = NULL;
  char *p = strtok(str, sep);
  int n_spaces = 0, i;

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
