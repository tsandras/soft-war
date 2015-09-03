#include "src.h"
#include "../lib/lib.h"

int accept_client_non_blocking(int socket_dec)
{
  int client;
  struct timeval tv;
  fd_set rfds;

  FD_ZERO(&rfds);
  FD_SET(socket_dec, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 50;
  if(select(socket_dec + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv) > 0)
    {
      client = accept(socket_dec, NULL, NULL);
      return (client);
    }
  else
    return (-1);
}

void message_started(int i, int * clients)
{
  char * message =  malloc (sizeof (char) * 10);
  char *final_message = "";

  message = "Client";
  final_message = my_strcat2(message, my_get_nbr_to_str(i+1));
  final_message = my_strcat2(final_message, ".");
  write(clients[i], final_message, my_strlen(final_message));
  final_message = my_strcat2("Nbs Clients : ", my_get_nbr_to_str(soft_war.clients_co));
  write(clients[i], final_message, my_strlen(final_message));
  write(clients[i], "\n", 1);
}

int nbs_clients(int * clients)
{
  int i;
  int j;

  j = 0;
  for (i = 0; i < 4; i++)
    if (clients[i] != -1)
      j++;
  return (j);
}

int find_free_pos(int * clients)
{
  int i;

  for (i = 0; i < 4; i++)
    if (clients[i] == -1)
      return (i);
  return (-1);
}

void fd_isset_for_quit(int num, int * clients, fd_set * readfs)
{
  int nread;
  char buffer[128] = {0};
  int i;

  if (FD_ISSET(clients[num], readfs))
    {
      nread = read(clients[num], buffer, 128);
      write(1, "reread:", 7);
      write(1, my_get_nbr_to_str(nread), my_strlen(my_get_nbr_to_str(nread)));
      write(1, "\n", 1);
      if (nread <= 0  || !my_strcmp(buffer, "exit"))
	{
	  FD_CLR(clients[num], readfs);
	  close(clients[num]);
	  clients[num] = -1;
	  soft_war.clients_co = soft_war.clients_co - 1;
	  for (i = 0; i < 4; i++)
	    {
	      if (i != num && clients[i] != -1)
		message_started(i, clients);
	    }
	}
    }
}

int max_file_desc(int * clients)
{
  int i;
  int max;

  max = 0;
  for (i = 0; i < 4; i++)
    if (clients[i] > max)
      max = clients[i];
  return (max);
}

int * accept_for_clients(int socket_desc)
{
  int * clients;
  fd_set readfs;
  int i;

  clients = malloc(sizeof(int) * 4);
  for (i = 0; i < 4; i++)
    clients[i] = -1;
  while (soft_war.clients_co < 4)
    {
      i = find_free_pos(clients);
      clients[i] = accept_client_non_blocking(socket_desc);
      if (clients[i] != -1)
	{
	  write(1, "val:", 4);
	  write(1, my_get_nbr_to_str(clients[i]), my_strlen(my_get_nbr_to_str(clients[i])));
	  write(1, "\n", 1);
	  soft_war.clients_co = soft_war.clients_co + 1;
	  message_started(i, clients);
	}
      fd_set_clients(clients, &readfs);
      struct timeval tv = {0, 50000};
      select(1 + max_file_desc(clients), &readfs, NULL, NULL, &tv);
      for (i = 0; i < 4; i++)
	if (clients[i] != -1)
	  {
	    fd_isset_for_quit(i, clients, &readfs);
	  }
      if (FD_ISSET(0, &readfs))
	{
	  for (i = 0; i < 4; i++)
	    close(clients[i]);
      }
    }
  write(1, "fin accept", 10);
  return (clients);
}
