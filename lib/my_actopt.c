#include "lib.h"

void long_opt(int *i, t_arg_cb *tab, int len, char **av)
{
  int j;
  
  for (j = 0; j < len; ++j)
    {
      if (my_strcmp(tab[j].name, av[*i]+2) == 0)
	{
	  if (tab[j].has_param == 1)
	    {
	      tab[j].cb(av[*i + 1]);
	      ++(*i);
	    }
	  else
	    tab[j].cb(NULL);
	}
    }
}

void short_opt(int *i, t_arg_cb *tab, int len, int ac, char **av)
{
  int j;

  for (j = 0; j < len; ++j)
    {
      if (*i < ac && my_isalpha(av[*i][1]) && av[*i][1] == tab[j].name[0])
	{
	  if (tab[j].has_param == 1)
	    {
	      tab[j].cb(av[*i + 1]);
	      ++(*i);
	    }
	  else
	    tab[j].cb(NULL);
	}
    }
}

void my_actopt(t_arg_cb *tab, int len, int ac, char **av)
{
  int i;

  for (i = 1; i < ac; ++i)
    {
      if (av[i][0] == '-' && my_strlen(av[i]) == 2)
	{
	  short_opt(&i, tab, len, ac, av);
	}
      else if (av[i][0] == '-' && av[i][1] != '\0' && av[i][1] == '-')
	{
	  long_opt(&i, tab, len, av);
	}
    }
}
