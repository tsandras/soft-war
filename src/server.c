#include "src.h"
#include "../lib/lib.h"

extern t_data_soft_war soft_war;

static t_cmd cmds[] =
{
  {"watch", &watch}
};

int create_server(int port)
{
  int socket_desc;
  struct sockaddr_in sin;

  if ((socket_desc = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      die("socket");
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(socket_desc, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
      die("bind");
    }
  if (listen(socket_desc, 42) < 0)
    {
      die("listen");
    }
  return (socket_desc);
}

int accept_client(int socket_desc)
{
  int client;
  struct sockaddr_in sin;
  socklen_t size;

  size = sizeof(sin);
  if ((client = accept(socket_desc, (struct sockaddr *)&sin, &size)) < 0)
    die("accept");
  return (client);
}

void fd_set_clients(int * clients, fd_set * readfs)
{
  int i;
  
  FD_ZERO(readfs);
  for (i = 0; i < 4; i++)
    if (clients[i] != -1)
      FD_SET(clients[i], readfs);
  FD_SET(0, readfs);
}

void fd_isset_for(int num, int * clients, fd_set * readfs, char * buffer)
{
  int nread;
  char * res;
  int i;

  res = malloc(sizeof(char) * 128);
  if (FD_ISSET(clients[num], readfs))
    {
      nread = read(clients[num], buffer, 32);
      buffer[nread] = '\0';
      for (i = 0; i < NBS_CMD; i++)
	{
	  if (my_strcmp(cmds[i].name, buffer) == 0)
	    res = cmds[i].cb(num, buffer);
	 }
      write(clients[num], res, strlen(res));
    }
}

void select_for_soft_war(int * clients, fd_set * readfs, char * buffer)
{
  int i;
  
  fd_set_clients(clients, readfs);
  select(8, readfs, NULL, NULL, NULL);
  for (i = 0; i < 4; i++)
    fd_isset_for(i, clients, readfs, buffer);
  if (FD_ISSET(0, readfs))
    {
      for (i = 0; i < 4; i++)
	close(clients[i]);
    }
}
