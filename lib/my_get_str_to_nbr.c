#include "lib.h"

int get_len_of_nbr(int nb)
{
  int i;

  i = 1;
  if (nb < 10)
    return (i);
  while(nb >= 10)
    {
       nb = nb / 10;
       i++;
    }
  return (i);
}

int my_power_rec(int nb, int power)
{
  if (power <= 0)
    return ((power <= - 1) ? (0) : (1));
  return (nb * my_power_rec(nb, power - 1));
}

char *my_get_nbr_to_str(int nb)
{
  int i;
  int j;
  int len;
  int tmp;
  char * tab = "";

  if (nb < 0)
    return ("");
  len = get_len_of_nbr(nb);
  tab = malloc(sizeof(char) * len);
  for (i = len, j = 0; i > 0; i--, j++)
    {
      tmp = nb / my_power_rec(10, i-1);
      tab[j] = tmp + '0';
      nb = nb - tmp * my_power_rec(10, i-1);
    }
  tab[j+1] = '\0';
  return (tab);
}
