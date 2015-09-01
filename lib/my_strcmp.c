#include "lib.h"

int     my_strcmp(char *s1, char *s2)
{
  int i;
  int j;
  int k;

  i = my_strlen(s1);
  j = my_strlen(s2);
  for (k = 0; (k != i) || (k != j); k++)
    {
      if (s1[k] != s2[k])
	{
	  return (s1[k] - s2[k]);
	}
    }
  return (0);
}
