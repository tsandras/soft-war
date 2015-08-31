/*
** my_strlen.c for my_strlen.c in /Users/cicofran/Piscine/C/Jour_02/cicofr_d
** 
** Made by CICOFRAN David
** Login   <cicofr_d@etna-alternance.net>
** 
** Started on  Wed Oct 23 11:16:28 2013 CICOFRAN David
** Last update Wed Oct 23 21:12:18 2013 CICOFRAN David
*/
int	my_strlen(char *str)
{
  int co;
  for (co = 0;str[co] != '\0';co++);

  return (co);
}
