/*
Copyright  ETIS — ENSEA, Université de Cergy-Pontoise, CNRS (1991-2014)
promethe@ensea.fr

Authors: P. Andry, J.C. Baccon, D. Bailly, A. Blanchard, S. Boucena, A. Chatty, N. Cuperlier, P. Delarboulas, P. Gaussier, 
C. Giovannangeli, C. Grand, L. Hafemeister, C. Hasson, S.K. Hasnain, S. Hanoune, J. Hirel, A. Jauffret, C. Joulain, A. Karaouzène,  
M. Lagarde, S. Leprêtre, M. Maillard, B. Miramond, S. Moga, G. Mostafaoui, A. Pitti, K. Prepin, M. Quoy, A. de Rengervé, A. Revel ...

See more details and updates in the file AUTHORS 

This software is a computer program whose purpose is to simulate neural networks and control robots or simulations.
This software is governed by the CeCILL v2.1 license under French law and abiding by the rules of distribution of free software. 
You can use, modify and/ or redistribute the software under the terms of the CeCILL v2.1 license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license, 
users are provided only with a limited warranty and the software's author, the holder of the economic rights,  and the successive licensors have only limited liability. 
In this respect, the user's attention is drawn to the risks associated with loading, using, modifying and/or developing or reproducing the software by the user in light of its specific status of free software, 
that may mean  that it is complicated to manipulate, and that also therefore means that it is reserved for developers and experienced professionals having in-depth computer knowledge. 
Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured 
and, more generally, to use and operate it in the same conditions as regards security. 
The fact that you are presently reading this means that you have had knowledge of the CeCILL v2.1 license and that you accept its terms.
*/
#include "robulab.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 

// #define DEBUG

pthread_t Robulab::thread_robulab;

Robulab::Robulab() {}

Robulab::~Robulab() {}

bool Robulab::check_battery(t_client *client, int *pid, char *msg_display) {
  int			size = 0;
  char			buffer[MAX_BUFFER];
  char			ans[MAX_BUFFER];
  struct sockaddr_in	addr;
  socklen_t		addrlen = sizeof(struct sockaddr_in);
  int			seq_ans = 0;
  t_msg			*msg = NULL;

#ifdef DEBUG
  printf("we are checking battery level \n");
#endif

  /* send udp request to robulab */

  send_batt(client, pid);

#ifdef DEBUG
  printf("attente de reception du message\n");
#endif

  /* attend de recevoir un message */
  memset(buffer, 0, MAX_BUFFER * sizeof(char));
  if ((size = recvfrom(client->sock, buffer, MAX_BUFFER - 1, 0, (struct sockaddr*)&addr, (socklen_t *)&addrlen)) == -1)
  {
    printf("read_answer : recvfrom");
    printf("Erreur de reception du buffer pour le client port %i\n", client->addr.sin_port);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }
  buffer[size] = '\0';
#ifdef DEBUG
  printf("[%s] %s\n", inet_ntoa(addr.sin_addr), buffer);
#endif
  if ((sscanf(buffer, "[%i] %s", &seq_ans, ans)) != 2)
  {
    printf("-> read_answer : erreur de lecture du message fscanf pour le client port %i\n", client->addr.sin_port);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }


  bool test = read_answer_batt(client, buffer, pid,msg_display);

  return test;
}

pthread_t  *Robulab::get_pthread() {
  return &thread_robulab;
}


void *Robulab::pthread_check_battery(void *arg) {
  bool test = true;
  int *pid = (int*)arg;
  int seq =0;
  char msg[255];

  t_client *client = NULL;

  /** time vals */
  struct timeval initial;
  struct timeval last;
  struct timeval now;
  double elapsed_time=0;

  /** set initial and last time val */
  gettimeofday(&last,NULL);
  gettimeofday(&initial,NULL);

  printf("CHECK BATTERY THREAD LAUNCHED\n\n");

  if ((client = (t_client*)malloc(sizeof(t_client))) == NULL)
  {
    printf("init_client : malloc");
    printf("-> init_client : erreur d allocation de memoire pour le client port %d\n", PORT_robulab);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }
  memset(client, 0, sizeof(t_client));

  if ((client->sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
  {
    printf("init_net : socket");
    printf("-> init_net : erreur de creation de la socket pour le client port %d\n", PORT_robulab);
    free(client);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }

  memset(&client->addr, 0, sizeof(struct sockaddr_in));
  client->addr.sin_family = AF_INET;
  client->addr.sin_port = htons(PORT_robulab);

  if (inet_aton(ADDR_IP, &(client->addr.sin_addr)) == 0)
  {
    printf("-> init_net : erreur inet_aton pour le client port %d\n", PORT_robulab);
    free(client);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);	      
  }


  client->cur_seq = &seq;

  /** print initial status */
  check_battery(client, pid, msg);
  printf("\n   [%.1f / %.1f] : %s > %.3f \n\n",0.,0.,msg,SEUIL_BATTERY);

  while(test) {

    test = check_battery(client, pid, msg);
    if (test == false) {    

      /** Display last battery value */
      gettimeofday(&now,NULL);
      elapsed_time=(now.tv_sec - last.tv_sec)+(now.tv_usec - last.tv_usec)/1000000;
      printf("\n\t[%.1f / %.1f] : %s < %.3f \n\n",elapsed_time,(double)((now.tv_sec - initial.tv_sec)+(now.tv_usec - initial.tv_usec)/1000000),msg,SEUIL_BATTERY);

      printf("battery low -> shutdown !\n");
      kill(*pid,SIGUSR1); /* warning signal for low battery */
    }
    /** set now time val */
    gettimeofday(&now,NULL);
    /** test on display period*/  
    elapsed_time=(now.tv_sec - last.tv_sec)+(now.tv_usec - last.tv_usec)/1000000;
    if(elapsed_time >= WAIT_display) {
      printf("\n   [%.1f / %.1f] : %s > %.3f \n\n",elapsed_time,(double)((now.tv_sec - initial.tv_sec)+(now.tv_usec - initial.tv_usec)/1000000),msg,SEUIL_BATTERY);
      last = now;
    }
    sleep(WAIT_query);
  }

  printf("EXIT BECAUSE LOW BATTERY - CHECK POSITION OF THE ARM AND RECHARGE BATTERY OF ROBULAB\n");
  pthread_exit(NULL);
}




/*
** Envoie une demande pour obtenir le niveau des batteries
*/
void	Robulab::send_batt(t_client *client, int *pid)
{
  int	size = 0;
  int	size_sent = 0;
  t_msg	*mesg = NULL;
  
  if ((mesg = (t_msg*)malloc(sizeof(t_msg))) == NULL)
  {
    printf("send_batt : malloc");
    printf("-> send_batt : erreur d allocation d un message pour le client port %i\n", client->addr.sin_port);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }

  memset(mesg->req, 0, MAX_BUFFER * sizeof(char));
  size = snprintf(mesg->req, MAX_BUFFER, "[%i] GetBattery", *(client->cur_seq));
  mesg->seq_req = *(client->cur_seq);
  (*(client->cur_seq))++;
  while (size)
  {
    size_sent = sendto(client->sock, mesg->req + size_sent, size, 0, (struct sockaddr *)&client->addr, sizeof(struct sockaddr));
    if(size_sent < 0) {
      perror("sendto");
      printf("erreur a l'envoi du paquet (%d)\n",size_sent);
      kill(*pid, SIGUSR1);
      pthread_exit(NULL);
    }
    size -= size_sent;
  }

  if (client->msg != NULL)
    client->msg->prev = mesg;
  mesg->next = client->msg;
  mesg->prev = NULL;
  client->msg = mesg;
}

/*
** Recois le niveau de batterie qui a ete demande
*/
bool Robulab::read_answer_batt(t_client *client, char *buffer, int *pid, char *msg_display)
{
  int	seq;
  char	cmd[MAX_BUFFER];
  float	batt;
  bool test = true;

  memset(cmd, 0, MAX_BUFFER * sizeof(char));
  if ((sscanf(buffer, "[%i] %s %f", &seq, cmd, &batt)) != 3)
  {
    printf("Erreur de lecture de la batterie\n%s", buffer);
    kill(*pid, SIGUSR1);
    pthread_exit(NULL);
  }
#ifdef DEBUG
  fprintf(stdout, "Read : Batterie = %.3f\n", batt);
#endif

  sprintf(msg_display,"Batterie = %.3f", batt);
  if(batt<SEUIL_BATTERY)
    test = false;
  return test;
}
