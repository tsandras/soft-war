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
