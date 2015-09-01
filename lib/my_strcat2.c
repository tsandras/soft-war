#include "lib.h"

char *my_strcat2(char *dest, char *src)
{
  int   i;
  int   j;
  int   k;
  char *out = malloc(my_strlen(dest) * sizeof(char) + my_strlen(src) * sizeof(char));
  j = 0;
  i = 0;
  k = 0;
  while (dest[i]) {
    out[k++] = dest[i++];
  }
  while (src[j]) {
    out[k++] = src[j++];
  }
  return (out);
}
