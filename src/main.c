#include "src.h"
#include "../lib/lib.h"

void die(char* message){
  printf(message);
  exit(0);
}

int main(int argc , char *argv[])
{
  int socket_desc;
  
  socket_desc = create_server(81);

  return 0;
}
