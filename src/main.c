
#include "src.h"
#include "../lib/lib.h"

void die(char* message){
  printf(message);
  exit(0);
}

int main(int argc , char *argv[])
{
  int socket_desc;
  int * clients = malloc(sizeof(int) * 4);
  char buffer[20];
  fd_set readfs;
  
  socket_desc = create_server(81);
  printf("socker creer");
  clients = accept_for_clients(socket_desc);
  
  while (1)
    {
      select_for_soft_war(clients, &readfs, buffer);
    }
  return (0);
}
