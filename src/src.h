#ifndef SRC_H
#define SRC_H

#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <errno.h>
#include <netinet/in.h>

void die(char* message);
int create_server(int port);

#endif
