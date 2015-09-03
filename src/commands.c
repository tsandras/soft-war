#include "src.h"
#include "../lib/lib.h"

extern t_data_soft_war soft_war;

t_pos find_pos_client(int num)
{
  int i;
  int j;
  char * sign;
  t_pos pos;
  show_map();
  pos.x = 0;
  pos.y = 0;
  sign = malloc(sizeof(char) * 5);
  sign = my_strcat2("0x0", my_get_nbr_to_str(num));
  for (i = 0; i < soft_war.size; i++)
    for (j = 0; j < soft_war.size; j++)
      {
	if (!my_strcmp(soft_war.map[i][j], sign))
	  {
	    pos.x = i;
	    pos.y = j;
	    return (pos);
	  }
      }
  return (pos);
}

char * watch(int num, char * cmd)
{
  t_pos pos;
  char * res;
  char * res1;
  char * res2;
  char * res3;
  char * val;
  (void)* cmd;

  res = malloc(sizeof(char) * 128);
  res1 = malloc(sizeof(char) * 7);
  res2 = malloc(sizeof(char) * 128);
  res3 = malloc(sizeof(char) * 7);
  val = malloc(sizeof(char) * 6);
  pos = find_pos_client(num);
  if (pos.x >= soft_war.size || pos.y + 1 >= soft_war.size || pos.x < 0 || pos.y + 1 < 0)
    val = "";
  else
    val = soft_war.map[pos.x][pos.y + 1];
  res = my_strcat2("{", val);
  if (pos.x + 1 >= soft_war.size || pos.y + 2 >= soft_war.size || pos.x + 1 < 0 || pos.y + 2 < 0)
    val = "";
  else
    val= soft_war.map[pos.x][pos.y + 1];
  res1 = my_strcat2(",", val);
  if (pos.x >= soft_war.size || pos.y + 2 >= soft_war.size || pos.x < 0 || pos.y + 2 < 0)
    val = "";
  else
    val= soft_war.map[pos.x][pos.y + 1];
  res2 = my_strcat2(",", val);
  if (pos.x - 1 >= soft_war.size || pos.y + 2 >= soft_war.size || pos.x - 1 < 0 || pos.y + 2 < 0)
    val = "";
  else
    val= soft_war.map[pos.x][pos.y + 1];
  res3 = my_strcat2(",", val);
  res = my_strcat2(res, res1);
  res2 = my_strcat2(res2, res3);
  res = my_strcat2(res, res2);
  res = my_strcat2(res, "}");
  return (res);
}
