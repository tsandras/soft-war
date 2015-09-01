char*my_strcat(char *str1, char *str2)
{
  int i;
  int j;

  for (i = 0; str1[i] != '\0'; i++)
    {
    }
  for (j = 0; str2[j] != '\0'; j++)
    {
      str1[i + j] = str2[j];
    }
  str1[i + j] = '\0';
  return (str1);
}
