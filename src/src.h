#ifndef SRC_H
#define SRC_H

#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
// Pour le Select()
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

typedef struct s_arg_cb
{
  char * name;
  int has_param;
  void (*cb)();
} t_arg_cb;

typedef struct s_data_soft_war
{
  unsigned int port;
  unsigned int cycle;
  int verbose;
  char * log;
  unsigned int size;
  int type;
} t_data_soft_war;

void die(char* message);
int create_server(int port);
int accept_client(int socker_desc);
int * accept_for_clients(int socket_desc);
void fd_set_client(int * clients, fd_set *readfs);
void fd_isset_for(int num, int * clients, fd_set * readfs, char * buffer);
void select_for_soft_war(int * clients, fd_set * readfs, char * buffer);
void handle_port(unsigned int port);
void handle_cycle(unsigned int cycle);
void handle_verbose();
void handle_log(char * log);
void handle_size(unsigned int size);
void handle_type();

#endif
