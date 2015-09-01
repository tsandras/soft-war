#include "lib.h"
// Only for signed number
char *my_get_str_to_nbr(int nb)
{
  int i;
  int nbtest;
  char * tab = malloc(sizeof(char) * 20);

  i = 0;
  if (nb < 10)
    {
      tab[0] = nb + 48;
      i++;
    }
  while (nb > 10)
    {
      if (i == 0)
	{
	  i++;
	  tab[0] = nb % 10 + 48;
	}
      nb = nb / 10;
      nbtest = nb % 10;
      tab[i] = nbtest + 48;
      i++;
    }
  //for (i = my_strlen(&tab[0]); i != 0; i--)
  //my_putchar((tab[i - 1] >= '0' && tab[i - 1] <= '9') ? (tab[i - 1]) : ('\0'));
  tab[i] = '\0';
  return (tab);
}
