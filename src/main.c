
#include "src.h"
#include "../lib/lib.h"

static t_arg_cb g_tab[] =
  {
    {"port", 1, &handle_port},
    {"cycle", 1, &handle_cycle},
    {"v", 0, &handle_verbose},
    {"log", 1, &handle_log},
    {"size", 1, &handle_size},
    {"c", 0, &handle_type},
  };

void die(char* message){
  write(1, message, my_strlen(message));
  exit(0);
}

extern t_data_soft_war soft_war;

void init_soft_war()
{
  soft_war.port = 81;
  soft_war.cycle = 500000;
  soft_war.verbose = 0;
  soft_war.size = 10;
  soft_war.log = "";
  soft_war.type = 0;
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

int main(int argc , char *argv[])
{
  int socket_desc;
  int * clients = malloc(sizeof(int) * 4);
  char buffer[20];
  fd_set readfs;
  init_soft_war();
  my_actopt(g_tab, 6, argc, argv);
  show_info_server();
  if (soft_war.type == 0)
    {
      socket_desc = create_server(81);
      clients = accept_for_clients(socket_desc);
      while (1)
	 {
	   select_for_soft_war(clients, &readfs, buffer);
	 }
    }
  else
    {
      write(1, "client", 6);
    }
  return (0);
}
