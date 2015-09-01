#include "src.h"

void send_to_server(int s)
{
  char buff[512];
  int size;

  while (1)
    {
      if ((size = read(0, buff, 512)) < 0)
	die("read");
      if (send(s, buff, size, 0) < 0)
	die("send");
    }
}

void recv_form_server(int s)
{
  char buff[512];
  int size;

  while (1)
    {
      if ((size = recv(s, buff, 512, 0)) < 0)
	die("recv");
      if (write(1, buff, size) < 0)
	die("write");
    }
}
