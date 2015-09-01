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
