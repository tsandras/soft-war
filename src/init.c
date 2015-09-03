#include "src.h"
#include "../lib/lib.h"

extern t_data_soft_war soft_war;

void init_soft_war()
 { 
   soft_war.port = 81;
   soft_war.cycle = 500000;
   soft_war.verbose = 0;
   soft_war.size = 10;
   soft_war.log = "";
   soft_war.type = 0;
   soft_war.clients_co = 0;
 }

void show_info_server()
{
  char *message = "";
  char *message2 = "";
  message = my_strcat2("Port:", my_get_nbr_to_str(soft_war.port));
  write(1, message, my_strlen(message));
  write(1, "\n", 1);
  message2 = my_strcat2("Size:", my_get_nbr_to_str(soft_war.size));
  write(1, message2, my_strlen(message2));
  write(1, "\n", 1);
}

void build_map()
{
  int i;
  int j;

  for (i = 0; i < soft_war.size; i++)
    {
      soft_war.map[i] = malloc(sizeof(char*) * soft_war.size);
      for (j = 0; j < soft_war.size; j++)
	{
	  soft_war.map[i][j] = malloc(sizeof(char) * 5);
	  soft_war.map[i][j] = "empty";
	}
    }
}
