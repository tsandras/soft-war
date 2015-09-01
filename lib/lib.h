#ifndef LIB_H
#define LIB_H

#include<stdlib.h>
#include "../src/src.h"

int    my_strlen(char *str);
char *my_strcat(char *str1, char *str2);
char *my_strcat2(char *dest, char *str);
char *my_get_str_to_nbr(int nb);
int my_isalpha(char c);
void my_actopt(t_arg_cb *tab, int len, int ac, char **av);
int     my_strncmp(char *s1, char *s2, int n);
int     my_strcmp(char *s1, char *s2);

#endif
