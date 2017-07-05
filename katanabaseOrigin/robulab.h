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


#ifndef ROBULAB_H
#define ROBULAB_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define	MAX_BUFFER	1024

#define SEUIL_BATTERY 12. // mettre 10

#define WAIT 500000 /* en micro_secondes */
#define WAIT_query 10 /* en secondes */
#define WAIT_display 60 /* en secondes */

#define ADDR_IP "192.168.1.3" /* addresse du robulab */
#define PORT_robulab 10000 /* port utilise */

typedef	struct		s_msg
{
  int			seq_req;
  char			req[MAX_BUFFER];
  int			seq_ans;
  char			ans[MAX_BUFFER];
  struct s_msg		*next;
  struct s_msg		*prev;
}			t_msg;

typedef	struct		s_client
{
  int			sock;
  pthread_t		tid;
  int			*cur_seq;
  int			nr_alive;
  struct sockaddr_in	addr;
  t_msg			*msg;
  struct s_client	*next;
  struct s_client	*prev;
}			t_client;

class Robulab{

public :
	Robulab();
	~Robulab();
	static pthread_t *get_pthread();
	static void * pthread_check_battery(void *arg);

protected :
	static pthread_t thread_robulab;
	static bool check_battery(t_client *client, int* pid, char* msg);
	static void send_batt(t_client *client, int *pid);
	static bool read_answer_batt(t_client *client, char *buffer, int *pid, char* msg);
};



#endif



