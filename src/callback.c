#include "src.h"

t_data_soft_war soft_war;

void handle_port(unsigned int port)
{
  soft_war.port = port;
}

void handle_cycle(unsigned int cycle)
{
  soft_war.cycle = cycle;
}

void handle_verbose()
{
  soft_war.verbose = 1;
}

void handle_log(char * log)
{
  soft_war.log = log;
}

void handle_size(unsigned int size)
{
  soft_war.size = size;
}

void handle_type()
{
  soft_war.type = 1;
}
