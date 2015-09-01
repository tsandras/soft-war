#ifndef SRC_H
#define SRC_H

#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
// Pour le Select()
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

void die(char* message);
int create_server(int port);
int accept_client(int socker_desc);
int * accept_for_clients(int socket_desc);
void fd_set_client(int * clients, fd_set *readfs);
void fd_isset_for(int num, int * clients, fd_set * readfs, char * buffer);
void select_for_soft_war(int * clients, fd_set * readfs, char * buffer);

#endif
