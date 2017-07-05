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

#ifndef KATANA_H
#define KATANA_H

#include <vector>
#include <string>
#include <pthread.h>
#include <include/KNI_InvKin/ikBase.h>
#include "kniBase.h"
#include <iostream>
#include "cinematique.h"

#define MOTOR_NUM 6
#define SENSOR_NUM 16
#define PASSIVECHECK_MOTOR 4

/********************
structure contenants
les arguments pour les
appels de threads
********************/
typedef struct Arg{
  CLMBase *katana;
  std::auto_ptr<CCdlSocket> device;
  std::auto_ptr<CCplSerialCRC> protocol;
  int motor;
  int pos;
  int vel;
  int encoder;
  bool boolean;
  short version;
  short revision;
  int p;
  int d;
  int i;
} Arguments;

class Katana
{

public:
  /*contructor and destructor*/
   //~ Katana(const char* addr, int port, const char* config_file); /*pas de constructeur par defaut*/
   Katana(const char *filename);
  ~Katana();


  void calibrate();
  void freeze_motor(int num_of_motor);
  std::vector<int> get_all_position();
  Arm *get_cinematique();
	int get_desired_velocity(int num_of_motor);
  int get_encoder_max_pos(int num_of_motor);
  int get_encoder_min_pos(int num_of_motor);
  bool get_freeze_status();
  bool get_mode_katana();
  bool get_motor_state(int num_of_motor);
  int get_nb_motors();
  int get_nb_sensors();
  int get_position(int num_of_motor);
  int get_previous_velocity(int num_of_motor);
  int get_pwm(int num_of_motor);
  int *get_sensors();
  float get_tactile_sensor();
  int get_velocity(int num_of_motor);
  bool is_calibrated();
  bool is_refreshed(int num_of_motor);
  void read_master_firmware(short* vers, short* rev);
  void set_calibrated(bool calibration);
  void set_freeze_status(bool status);
  void set_motor_state(int num_of_motor, bool state);
  int set_position(int num_of_motor,int position,bool wait_until_reach);
	void set_desired_velocity(int num_of_motor,int velocity);
  void set_previous_velocity(int num_of_motor,int velocity);
  void set_refreshed(int num_of_motor, bool val);
  int set_velocity(int num_of_motor,int velocity);
  int switch_motor(int num_of_motor,bool activate);
  int switch_robot(bool activate);
  void set_passif(bool mode);
  int set_controller_parameters(int num_of_motor,int p, int d, int i);



  static Arguments *arguments; /* provisoire */
  
private:
  bool security_override;

protected:

  pthread_t thread_katana;
  static std::vector<int> encoders;
  bool motorOn[MOTOR_NUM];
  bool updated[MOTOR_NUM]; /* true if the pos has just been updated - used internally */
  bool refreshed[MOTOR_NUM]; /* true if the pos has just been updated but not sent - used externally*/
  /*on met la vitesse de ce moteur a velocity*/
  /*on ne peut pas mettre des vitesses negatives*/
  /*lorsqu'on rentre un nombre negatif la vitesse du moteur est tres rapide*/
  static int previous_velocity[MOTOR_NUM];
  static int desired_velocity[MOTOR_NUM];
  bool calibrated;
  bool passif;
  bool freeze; /*true if robot was frozen*/
  static int speed;
  static int nb_motors;
  static int nb_sensors;
  static int min;
  static int max;
  static int *sensors;
  static int pain_sensor;
  static int pwm;
  Arm *cinematique;

  static void gestion_mask_signaux();
  static void *thread_calibrate(void*);
  static void *thread_freeze_motor(void *);
  static void *thread_get_all_position(void *);
  static void *thread_get_encoder_max_pos(void*);
  static void *thread_get_encoder_min_pos(void*);
  static void *thread_get_position(void*);
  static void *thread_get_pwm(void*);
  static void *thread_get_sensors(void*);
  static void *thread_get_velocity(void*);
  static void *thread_read_master_firmware(void*);
  static void *thread_set_position(void*);
  static void *thread_set_velocity(void*);
  static void *thread_switch_motor(void*);
  static void *thread_switch_robot(void*);
  static void *thread_set_controller_parameters(void*);
};
#endif
