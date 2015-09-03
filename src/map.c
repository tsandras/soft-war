#include "src.h"
#include "../lib/lib.h"

void put_clients_on_map()
{
  soft_war.map[0][0] = "#0x00\0";
  soft_war.map[0][soft_war.size - 1] = "#0x01";
  soft_war.map[soft_war.size - 1][0] = "#0x02";
  soft_war.map[soft_war.size - 1][soft_war.size - 1] = "#0x03";
}

void show_map()
{
  int i;
  int j;

  for (i = 0; i < soft_war.size; i++)
    for (j = 0; j < soft_war.size; j++)
      {
	write(1, soft_war.map[i][j], my_strlen(soft_war.map[i][j]));
	write(1, "|", 1);
	if (j + 1 == soft_war.size)
	  write(1, "\n", 1);
      }
}
