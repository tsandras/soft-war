int my_sign(char *str, int *pos)
{
  int nbs_less;
  int i;

  nbs_less = 1;
  i = 0;
  while (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
    {
      (*pos)++;
      if (str[i] == '-')
	nbs_less *= -1;
      i++;
    }
  return (nbs_less);
}

int my_getnbr(char *str)
{
  int i;
  int sign;
  int value;

  i = 0;
  value = 0;
  sign = my_sign(str, &i);
  while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
    {
      value = value * 10 + (str[i] - '0');
      i++;
    }
  return (sign * value);
}
