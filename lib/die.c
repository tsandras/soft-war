#include "lib.h"

void die(char* message)
{
  write(1, message, my_strlen(message));
  exit(0);
}
