#include "src.h"
#include "../lib/lib.h"

extern t_data_soft_war soft_war;

void handle_port(char * port)
{
  if (my_getnbr(port) > 0)
    soft_war.port = my_getnbr(port);
}

void handle_cycle(char * cycle)
{
  if (my_getnbr(cycle) > 0)
    soft_war.cycle = my_getnbr(cycle);
}

void handle_verbose()
{
  soft_war.verbose = 1;
}

void handle_log(char * log)
{
  soft_war.log = log;
}

void handle_size(char * size)
{
  if (my_getnbr(size) > 0)
    soft_war.size = my_getnbr(size);
}

void handle_type()
{
  soft_war.type = 1;
}
