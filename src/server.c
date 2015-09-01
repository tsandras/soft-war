#include "src.h"

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
  int size;

  size = sizeof(sin);
  if ((client = accept(socket_desc, (struct sockaddr *)&sin, &size)) < 0)
    die("accept");
  return (client);
}

char *my_itoa(int wert, int laenge) {
  char *ret =(char *) malloc(laenge+1 * sizeof(char));
  int i;

  for(i  =0; i < laenge; i++) {
    ret[laenge-i-1] = (wert % 10) + 48;
    wert = wert / 10;
  }
  ret[laenge]='\0';
  return ret;
}

int * accept_for_clients(int socket_desc)
{
  printf("On entre dans la fonction");
  int * clients = malloc (sizeof (int) * 4);
  int i;
  char * message =  malloc (sizeof (char) * 10);
  //char * nombre  =  malloc (sizeof (char) * 2);
  for (i = 0; i < 4; i++)
    {
      clients[i] = accept_client(socket_desc);
      if (clients[i] == -1)
	return (NULL);
      printf("le message %s", message);
      //message = "Client \0";
      snprintf(message, 10, "Client %d.", i);
      //message = strcat(message, nombre);
      write(clients[i], message, my_strlen(message));
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
  fd_set_clients(clients, readfs);
  select(8, readfs, NULL, NULL, NULL);
  fd_isset_for(0, clients, readfs, buffer);
  fd_isset_for(1, clients, readfs, buffer);
  fd_isset_for(2, clients, readfs, buffer);
  fd_isset_for(3, clients, readfs, buffer);
  if (FD_ISSET(0, readfs))
    {
      close(clients[0]);
      close(clients[1]);
      close(clients[2]);
      close(clients[3]);
      //return (EXIT_SUCCESS);
    }
}
