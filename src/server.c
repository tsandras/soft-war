#include "src.h"
#include "../lib/lib.h"

extern t_data_soft_war soft_war;

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

int * accept_for_clients(int socket_desc)
{
  printf("On entre dans la fonction");
  int * clients = malloc (sizeof (int) * 4);
  int i;
  char * message =  malloc (sizeof (char) * 10);
  char *final_message = "";
  
  for (i = 0; i < 4; i++)
    {
      clients[i] = accept_client(socket_desc);
      if (clients[i] == -1)
	return (NULL);
      soft_war.clients_co = soft_war.clients_co + 1;
      message = "Client";
      final_message = my_strcat2(message, my_get_nbr_to_str(i));
      final_message = my_strcat2(final_message, ".");
      write(clients[i], final_message, my_strlen(final_message));
      final_message = my_strcat2("Nbs Cs : ", my_get_nbr_to_str(soft_war.clients_co));
      write(clients[i], final_message, my_strlen(final_message));
      write(clients[i], "\n", 1);
    }
  return (clients);
}

void fd_set_clients(int * clients, fd_set * readfs)
{
  int i;
  FD_ZERO(readfs);
  for (i = 0; i < 4; i++)
    FD_SET(clients[i], readfs);
  FD_SET(0, readfs);
}

void fd_isset_for(int num, int * clients, fd_set * readfs, char * buffer)
{
  int nread;
  int i;
  
  if (FD_ISSET(clients[num], readfs))
    {
      memset(buffer, 0, 20);
      nread = read(clients[num], buffer, 20);
      buffer[nread] = '\0';
      for (i = 0; i < 4; i++)
	{
	  if (i != num)
	    write(clients[i], buffer, strlen(buffer));
	}
      FD_CLR(clients[0], readfs);
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
      //return (EXIT_SUCCESS);
    }
}
