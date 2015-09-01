
#include "src.h"
#include "../lib/lib.h"

void die(char* message){
  printf(message);
  exit(0);
}

int main(int argc , char *argv[])
{
  printf("coucou");
  int socket_desc;
  int * clients= malloc(sizeof(int) * 4);
  char buffer[20];
  int nread;
  fd_set readfs;
  
  socket_desc = create_server(81);
  printf("socker creer");
  clients = (int *) accept_for_clients(socket_desc);
  
  while (1)
    {
      FD_ZERO(&readfs);
      FD_SET(clients[0], &readfs);
      FD_SET(clients[1], &readfs);
      FD_SET(0, &readfs);
      select(6, &readfs, NULL, NULL, NULL);
      if (FD_ISSET(clients[0], &readfs))
	{
	  printf("client1\n");
	  memset(buffer, 0, 20);
	  nread = read(clients[0], buffer, 20);
	  buffer[nread] = '\0';
	  write(clients[1], buffer, strlen(buffer));
	  FD_CLR(clients[0], &readfs);
	}
      if (FD_ISSET(clients[1], &readfs))
	{
	  printf("client2\n");
	  memset(buffer, 0, 20);
	  nread = read(clients[1], buffer, 20);
	  buffer[nread] = '\0';
	  write(clients[0], buffer, strlen(buffer));
	  FD_CLR(clients[1], &readfs);
	}
      if (FD_ISSET(0, &readfs))
	{
	  close(clients[0]);
	  close(clients[1]);
	  return (EXIT_SUCCESS);
	}
    }  
  return (0);
}
