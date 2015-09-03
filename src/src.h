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
  int port;
  int cycle;
  int verbose;
  char * log;
  int size;
  int type;
  int clients_co;
  char *** map;
} t_data_soft_war;

void die(char* message);
int create_server(int port);
int accept_client(int socker_desc);
int * accept_for_clients(int socket_desc);
void fd_set_client(int * clients, fd_set *readfs);
void fd_isset_for(int num, int * clients, fd_set * readfs, char * buffer);
void select_for_soft_war(int * clients, fd_set * readfs, char * buffer);
void handle_port(char * port);
void handle_cycle(char * cycle);
void handle_verbose();
void handle_log(char * log);
void handle_size(char * size);
void handle_type();
void init_soft_war();
void show_info_server();
void build_map();
int accept_client_non_blocking(int socket_dec);
void message_started(int i, int * clients);
int nbs_clients(int * clients);
int find_free_pos(int * clients);
void fd_isset_for_quit(int num, int * clients, fd_set * readfs);
int max_file_desc(int * clients);
int * accept_for_clients(int socket_desc);
void fd_set_clients(int * clients, fd_set * readfs);

t_data_soft_war soft_war;

#endif
