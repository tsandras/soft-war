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

extern t_data_soft_war soft_war;

int main(int argc , char *argv[])
{
  int socket_desc;
  int * clients = malloc(sizeof(int) * 4);
  char buffer[20];
  fd_set readfs;
  
  init_soft_war();
  my_actopt(g_tab, 6, argc, argv);
  build_map();
  show_info_server();
  if (soft_war.type == 0)
    {
      socket_desc = create_server(soft_war.port);
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
