#include "src.h" 

#define OK 0
#define WATCH 1
#define INSPECT 2

char* vision[16] = {"","","",""};

int connect_to(char *hostname, int port)
{
  int s;
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(hostname);
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    die("socket");
  if (connect(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
    die("connect");
  return (s);
}

void send_to_server(int s, char* req, int size)
{
  if (send(s, req, size, 0) < 0)
    die("send");
}

int recv_from_server(int s, int action)
{
  char buff[512];
  int size, i, j, k;
  int enemy_energy;
  
  enemy_energy = 0;

  if ((size = recv(s, buff, 512, 0)) < 0)
    die("recv");

  if (!strcmp(buff,"die"))
    {
      printf("coucouVous êtes mort. %s \n", buff);
      exit(0);
    }

  if (!strcmp(buff, "win"))
    {
      printf("Vous avez gagné.\n");
      exit(0);
    }

  if (action == WATCH)
    {
      i = 1;
      j = 0;
      k = 0;
      vision[0] = "";
      vision[1] = "";
      vision[2] = "";
      vision[3] = "";

      while (i < size-1)
	{
	  if (buff[i] != '{')
	    {
	      if (buff[i] == ',')
		{
		  j++;
		  k=0;
		}
	      vision[j][k] = buff[i];
	      k++;
	    }
	  i++;
	}
    }

  else if (action == INSPECT)
    {
      enemy_energy = atoi(buff);
      return (enemy_energy);
    }
  return (0);
}

int play(int ac, char **av)
{
  int s;
  char buff[512];
  int size;
  int cur_energy = 50;
  char enemy_energy = 0;
  int demi_act;
  int fuite_right = 0;
  char* direc;
  char* inspect = "inspect #0x00";

  if (ac != 3)
    {
      printf("Usage: %s host port\n", av[0]);
      return (0);
    }
  s = connect_to(av[1], atoi(av[2]));

  // on attend le début de la partie
  while (1)
    {
      if ((size = recv(s, buff, 512, 0)) < 0)
	die("recv");
      if (!strcmp(buff,"go"))
	break;
    }

  while (1)
    {
      cur_energy -= 2;
      demi_act = 2;

      send_to_server(s, "watch", 5);
      recv_from_server(s, WATCH);
      printf("%s %s %s %s\n", vision[0], vision[1], vision[2], vision[3]);

      // face à de l'énergie
      if (!strcmp(vision[0], "energy"))
	{
	  send_to_server(s, "gather", 5);
	  recv_from_server(s, OK);
	  demi_act = 0;
	}

      // face à un mur
      else if (!strcmp(vision[0], ""))
	{
	  send_to_server(s, "right", 5);
	  recv_from_server(s, OK);
	  send_to_server(s, "right", 5);
	  recv_from_server(s, OK);
	  demi_act = 0;
	}

      // face à une case vide
      else if (!strcmp(vision[0], "empty"))
	{
	  if (!strcmp(vision[2], ""))
	    {
	      send_to_server(s, "rightfwd", 5);
	      recv_from_server(s, OK);
	    }
	  else if (!strcmp(vision[4], ""))
	    {
	      send_to_server(s, "leftfwd", 5);
	      recv_from_server(s, OK);
	    }
	  else
	    {
	      send_to_server(s, "forward", 5);
	      recv_from_server(s, OK);
	    }
	}

      // face à un ennemi
      else
	{
	  if (fuite_right)
	    {
	      direc = "right";
	      fuite_right = 1;
	    }
	  else
	    {
	      direc = "left";
	      fuite_right = 0;
	    }

	  //inspect
	  inspect[11] = vision[0][3];
	  inspect[12] = vision[0][4];
	  send_to_server(s, "forward", 5);
	  enemy_energy = recv_from_server(s, OK);

	  // collision
	  if (enemy_energy > cur_energy)
	    {
	      send_to_server(s, "forward", 5);
	      recv_from_server(s, OK);
	      send_to_server(s, direc, 5);
	      recv_from_server(s, OK);
	    }

	  //fuite
	  else
	    {
	      send_to_server(s, direc, 5);
	      recv_from_server(s, OK);
	      send_to_server(s, "forward", 5);
	      recv_from_server(s, OK);
	    }
	}

      // fin du cycle
      if (demi_act != 0)
	{
	  send_to_server(s, "next", 5);
	  recv_from_server(s, OK);
	}
    }
}
