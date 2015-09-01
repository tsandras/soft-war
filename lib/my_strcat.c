char*my_strcat(char *str1, char *str2)
{
  int i;
  int j;
  i = my_strlen(str1);
  j = 0;
  while (str2[j])
    {
      str1[i] = str2[j];
      i++;
      j++;
    }
  str1[i] = '\0';
  return (str1);
}
