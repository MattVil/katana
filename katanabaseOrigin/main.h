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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <getopt.h>
#include <ivy.h>
#include <ivyloop.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <include/KNI_InvKin/ikBase.h>
#include <pthread.h>

#include "cinematique.h"
#include "katana.h"
#include "kniBase.h"
#include "keyboard.h"
#include "ivy_bus.h"
#include "robulab.h"

//extern int pos_min[6]={-12000,-30000,-26000,7000,-16600,12000};     /*position min que peuvent atteindre les butees*/
//extern int pos_max[6]={30000,-10000,1000,19000,30000,30000};        /*position max que peuvent atteindre les butees*/
extern struct sigaction act;                                          /*gestion des signaux*/
extern Katana *katana;                                                /* classe d'interface avec le bras Katana*/


class Broker
{
public:  
   Broker(const char *filename);
  ~Broker();
  
  void init_robulab();
  bool is_robulab_defined();
  bool is_ivy_needed();
private:
  bool robulab;
  bool ivy;
  int port;
  char addr[32];
};

int is_calibrated();
//const TMotSCP mygetscp(int idx);
//void readpid_pos();
//void readpid_spd();
//const TMotPVP mygetpvp(int idx);
//void readpvp();
void goinitialposition();
void positionMinMaxEncodeur();
void go_to_neutral_position_from_init(Arm *katana_arm);
void gomovemotor(int idx, int step, int sens);
void read_vitesse();
void read_encodeur();
void write_vitesse_all_encoder(int velocity);
void controle_moteur_vitesse(int idx, int velocity);
void controle_moteur_vitesse(int idx, int velocity,int *encoder);
void controle_moteur_activation(int idx, float a1, float a2, int *encoder);
float position_to_angle(int position, int idx);
int angle_to_encoders(float angle, int idx);
float distAngle_to_encoders(float distAngle, int idx);
float compute_acceleration(float angleArtic2, float a1, float a2, int bDisp);
void gochoosemotor_controle_vitesse();
void gochoosemotor();
void aller_pos_max();
void aller_pos_min();
void aller_pos_calibration();
void manualcalibrate(int idx);
void goreadencodersvalues();
void gocalibrate();
void readsensorvalue();
int prise_objet();
void fermer_pince();
void readidentificationstring();
short readmasterfirmware();
void alarm(int sig);
int is_calibrated();
void switchrobot(int activate);
void switchmotor(int idx, int activate);
void test();
int check_security_plan(void);
bool passif_function(std::vector<int> encod);
