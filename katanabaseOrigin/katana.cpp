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
#include "katana.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mxml.h>

/*definition des variables statiques*/
std::vector<int> Katana::encoders;
int Katana::previous_velocity[MOTOR_NUM] = {-10000, -10000, -10000, -10000, -10000, -10000};
int Katana::desired_velocity[MOTOR_NUM] = {-10000, -10000, -10000, -10000, -10000, -10000};
int Katana::speed;
int Katana::min;
int Katana::max;
int *Katana::sensors;
int Katana::nb_sensors=SENSOR_NUM;
int Katana::nb_motors=MOTOR_NUM;
int Katana::pwm;
Arguments *Katana::arguments;



Katana::Katana(const char *filename)
{
	mxml_node_t *tree=NULL;
	mxml_node_t *node=NULL;
	calibrated =false;
	arguments = new Arguments();
	arguments->katana = new CLMBase();
	char *p=NULL, addr[32], config_file[64];
	int port=5566;
	FILE *f=NULL;

	for (int i = 0; i< nb_motors; i++)
	{
		updated[i] = false;
		motorOn[i]=false;
		refreshed[i]=false;
	}
	sensors = new int[nb_sensors];
	strcpy(addr, "192.168.168.232");
	port = 5566;
	passif = true; /* modif : toujours passif a la base:: old =false*/

	f=fopen(filename, "r");
	if(f==NULL)
	{
		printf("unable to open %s", filename);
		exit(EXIT_FAILURE);
	}
	tree = mxmlLoadFile(NULL, f, MXML_TEXT_CALLBACK);
	fclose(f);
	if(tree == NULL)
	{
		std::cout << "unable to load from %s" << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	node = mxmlFindElement(tree, tree, "katana", NULL, NULL, MXML_DESCEND);
	p=(char*)mxmlElementGetAttr(node, "ip");
	if(p == NULL)
	{
		std::cout << "error, no ip found in" << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	strncpy(addr, p, sizeof(addr));
	p=(char*)mxmlElementGetAttr(node, "port");
	if(p == NULL)
	{
		std::cout << "error, no port found in" << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	if (sscanf(p, "%d", &port) != 1)
	{
		printf("The value '%s' of attribute 'ip' in node '%s' is not a int", p, node->value.element.name);
		exit(EXIT_FAILURE);
	}
  /*mode passif*/
	p=(char*)mxmlElementGetAttr(node, "passif");
	if(p == NULL)
	{
		std::cout << "error, no passif found in" << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	if(strncmp(p, "false", 5*sizeof(char)))
    passif = false;
  
	p=(char*)mxmlElementGetAttr(node, "config_file");
	if(p == NULL)
	{
		std::cout << "error, no config file found in" << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	strncpy(config_file, p, sizeof(config_file));
	node = mxmlFindElement(tree, tree, "obstacles", NULL, NULL, MXML_DESCEND);
	cinematique = new Arm(tree);

	std::cout << "Initialisation en cours (trying to connect to " << addr << ":" << port << ")...\n";
	try
	{
		arguments->device.reset(new CCdlSocket((char*)addr,port));
		std::cout <<"reset device\n";
		arguments->protocol.reset(new CCplSerialCRC());
		std::cout <<"reseted device\n";
		arguments->protocol->init(arguments->device.get());
		std::cout <<"init device\n";
		arguments->katana->create(config_file, arguments->protocol.get());
		std::cout <<"config file device\n";

		/* tester la valeur par defaut quand on allume les moteurs : actifs ou pas */

	}
	catch (Exception &e)
	{
		std::cout << "ERROR: " << e.message() << std::endl;
		exit(1);
	}

	std::cout<<"Creation de la cinematique pour la securite"<<std::endl;
	node = mxmlFindElement(tree, tree, "obstacles", NULL, NULL, MXML_DESCEND);
	cinematique = new Arm(node);

	mxmlDelete(tree);

	std::cout << "... Fin initialisation\n";
}


Katana::~Katana()
{
	std::cout << "bug hunting: destroy Katana" << std::endl;
	delete[] arguments;
	delete[] sensors;
}


void Katana::calibrate()
{
	int join_ok;

	if (pthread_create(&thread_katana, NULL, thread_calibrate, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join(thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}

	for (int i = 0; i< nb_motors; i++) {
		motorOn[i]=true;
	}
	calibrated =true;
}

void Katana::freeze_motor(int num_of_motor)
{
	int join_ok;
	/* TODO : modifier freeze ? juste un moteur pas tout le robot...*/
	arguments->motor = num_of_motor;
	if (pthread_create(&thread_katana, NULL, thread_freeze_motor, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join(thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
}

Arm* Katana::get_cinematique() {
	return cinematique;
}

bool Katana::get_mode_katana()
{
	return this->passif;
}
void Katana::set_passif(bool mode)
{
	passif = mode;
}

std::vector<int> Katana::get_all_position()
{
	int join_ok;
	if (pthread_create(&thread_katana, NULL, thread_get_all_position, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	else
	{
		for(int i=0; i<nb_motors;i++) {
			updated[i] = false;
			refreshed[i] = true;
		}
		return encoders;
	}
}


bool Katana::get_freeze_status() {
	return freeze;
}

bool Katana::get_motor_state(int num_of_motor) {
	return motorOn[num_of_motor];
}

int Katana::get_encoder_max_pos(int num_of_motor)
{
	int join_ok;
	arguments->motor = num_of_motor;

	if (pthread_create(&thread_katana, NULL, thread_get_encoder_max_pos, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	else
		return max;
}

int Katana::get_encoder_min_pos(int num_of_motor)
{
	int join_ok;

	arguments->motor = num_of_motor;
	if (pthread_create(&thread_katana, NULL, thread_get_encoder_min_pos, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	else
		return min;
}


int Katana::get_nb_motors() {
	return nb_motors;
}

int Katana::get_nb_sensors() {
	return nb_sensors;
}

int Katana::get_position(int num_of_motor)
{
	if(!updated[num_of_motor])
	{
		int join_ok;
		if (pthread_create(&thread_katana, NULL, thread_get_position, (void *)arguments)!= 0)
		{
			std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
			exit(1);
		}

		join_ok = pthread_join( thread_katana, NULL);
		if (join_ok != 0){
			std::cerr << "Thread_katana not joined!\n"<<std::endl;
			exit(1);
		}
		for(int i=0; i<nb_motors;i++) {
			updated[i] = true;
		}
	}
	updated[num_of_motor] = false;
	refreshed[num_of_motor] = true;
	return encoders[num_of_motor];
}

int Katana::get_previous_velocity(int num_of_motor) {
	return previous_velocity[num_of_motor];
}

int *Katana::get_sensors()
{
	int join_ok;

	if (pthread_create(&thread_katana, NULL, thread_get_sensors, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	else
		return sensors;
}


float Katana::get_tactile_sensor()
{
	return cinematique->get_tactile_sensor();
}

int Katana::get_velocity(int num_of_motor)
{
	int join_ok;
	arguments->motor = num_of_motor;

	if (pthread_create(&thread_katana, NULL, thread_get_velocity, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	return speed;
}

int Katana::get_pwm(int num_of_motor)
{
	int join_ok;
	arguments->motor = num_of_motor;

	//std::cout<< "Debug pwm !" << std::endl;


	if (pthread_create(&thread_katana, NULL, thread_get_pwm, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}

	return pwm;
}

bool Katana::is_calibrated() {
	return calibrated;
}


bool Katana::is_refreshed(int num_of_motor) {
	return refreshed[num_of_motor];
}

void Katana::read_master_firmware(short* vers, short* rev)
{
	int join_ok;

	if (pthread_create(&thread_katana, NULL, thread_read_master_firmware, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join(thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}

	*vers = arguments->version;
	*rev = arguments->revision;
}

void Katana::set_calibrated(bool calibration) {
	calibrated = calibration;
	if(calibrated) {
		for (int i = 0; i< nb_motors; i++) {
			switch_motor(i,true);
			motorOn[i]=true;
		}
  }
}

void Katana::set_desired_velocity(int num_of_motor,int velocity) {
	desired_velocity[num_of_motor]=velocity;
}

void Katana::set_freeze_status(bool status) {
	this->freeze=status;
}

void Katana::set_motor_state(int num_of_motor, bool state) {
	motorOn[num_of_motor]=state;
}

int Katana::set_position(int num_of_motor, int position, bool wait_until_reached)
{
	int join_ok;

	//  printf("set position in (%d)\n",position);

	/* unfreeze motor if moving to position */
	this->freeze=false;

	/* lorsque l'on commande en position, on reactive automatiquement le moteur */
	motorOn[num_of_motor]=true;

	/*security: passif mode disabled is the motor that is checked for passive mode is controlled*/
	if(num_of_motor==PASSIVECHECK_MOTOR) {
		//    printf("katana.cpp : set position : passif desactive\n");
		passif = false;
	}

	arguments->motor = num_of_motor;
	arguments->pos  = position;
	arguments->boolean = wait_until_reached;

	if (pthread_create(&thread_katana, NULL, thread_set_position, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		return -1;
	}

	join_ok = pthread_join(thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}


	//  printf("set position out\n");
	return join_ok;/*== 0 if no error*/
}


void Katana::set_previous_velocity(int num_of_motor,int velocity) {
	previous_velocity[num_of_motor]=velocity;
}


void Katana::set_refreshed(int num_of_motor, bool val) {
	refreshed[num_of_motor] = val;
}

int Katana::set_velocity(int num_of_motor,int velocity)
{
	int join_ok;
	arguments->motor = num_of_motor;
	arguments->vel  = velocity;


	/* unfreeze motor if moving with speed */
	this->freeze=false;

	/*security: passif mode disabled if the motor that is checked for passive mode is controlled*/
	if(num_of_motor==PASSIVECHECK_MOTOR && velocity != 0)
    {
	  /** si on bouge (v!=0) l'articulation qui donne l'info du
	   * mode passif **/
	  /* En fait le vrai test est: est ce que la position cible
	   * est differente de la position actuelle */
	  // printf("katana.cpp : set velocity : passif desactive\n");
	  passif = false;
	}

	/* lorsque l'on commande en vitesse, on reactive automatiquement le moteur */
	motorOn[num_of_motor]=true;

	//printf("set velocity in [%d] = (%d) \n", num_of_motor, velocity);

	if (pthread_create(&thread_katana, NULL, thread_set_velocity, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		return -1;
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}

	//  printf("set velocity out\n");

	return join_ok;/*== 0 if no error*/
}


int Katana::switch_motor(int num_of_motor,bool activate)
{
	int join_ok;

	arguments->motor = num_of_motor;
	arguments->boolean  = activate;

	motorOn[num_of_motor]=activate;

	//std::cout<< "Debug switch_motor !" << std::endl;

	if (pthread_create(&thread_katana, NULL, thread_switch_motor, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}

	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	return join_ok;
}

int Katana::switch_robot(bool activate)
{
	int join_ok;
	arguments->boolean  = activate;

	for(int i=0; i< nb_motors; i++) {
		motorOn[i] = activate;
	}

	//std::cout<< "Debug switch_robot !" << std::endl;

	if (pthread_create(&thread_katana, NULL, thread_switch_robot, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}
	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	return join_ok;
}


int Katana::set_controller_parameters(int num_of_motor,int p, int d, int i)
{

	std::cout<< "Debug st_controller !" << std::endl;

	int join_ok;
	arguments->motor = num_of_motor;
	arguments->p = p;
	arguments->d = d;
	arguments->i = i ;

	/*security: passif mode disabled is the motor that is checked for passive mode is controlled*/
	if(num_of_motor==PASSIVECHECK_MOTOR) {
		passif = false;
	}

	/* il faudrait preciser les valeurs des moteurs (actif ou non) lors de l'utilisation de cette fonction*/

	if (pthread_create(&thread_katana, NULL, thread_set_controller_parameters, (void *)arguments)!= 0)
	{
		std::cerr << "Thread_katana not created, program stopped\n"<<std::endl;
		exit(1);
	}
	join_ok = pthread_join( thread_katana, NULL);
	if (join_ok != 0){
		std::cerr << "Thread_katana not joined!\n"<<std::endl;
		exit(1);
	}
	return join_ok;
}
/** protected **/
/*gestionnaire de signaux : masque blocant dans les threads*/
void Katana::gestion_mask_signaux()
{
	sigset_t masque;
	sigemptyset(&masque);
	if (sigaddset(&masque, SIGUSR1) == -1)
	{
		fprintf(stderr, "impossible de bloquer le signal SIGUSR1...\n");
		exit(1);
	}
	if (sigaddset(&masque, SIGCHLD) == -1)
	{
		fprintf(stderr, "impossible de bloquer le signal SIGCHLD...\n");
		exit(1);
	}
	if (sigaddset(&masque, SIGINT) == -1)
	{
		fprintf(stderr, "impossible de bloquer le signal SIGINT...\n");
		exit(1);
	}

	if (pthread_sigmask(SIG_BLOCK, &masque, NULL) != 0)
	{
		fprintf(stderr,
				"impossible d'imposer le mask des signaux au thread...\n");
		exit(1);
	}
}


void *Katana::thread_set_controller_parameters(void *arg)
{
	Arguments *data = (Arguments *)arg;
	int p = data->p;
	int d = data->d;
	int i = data->i;
	gestion_mask_signaux();
	data->katana->CLMBase::GetBase()->GetMOT()->arr[data->motor].setControllerParameters(p,d,i);
}




void *Katana::thread_calibrate(void* arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	data->katana->calibrate();
}

void *Katana::thread_freeze_motor(void* arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	data->katana->freezeMotor(data->motor);
}

void *Katana::thread_get_all_position(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	encoders = data->katana->getRobotEncoders();
}

void *Katana::thread_get_encoder_max_pos(void* arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	max = data->katana->GetBase()->GetMOT()->arr[data->motor].GetEncoderMinPos();
}

void *Katana::thread_get_encoder_min_pos(void* arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	min = data->katana->GetBase()->GetMOT()->arr[data->motor].GetEncoderMinPos();
}

void *Katana::thread_get_position(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	encoders = data->katana->getRobotEncoders();
}

void *Katana::thread_get_pwm(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();
	const TMotPVP *MonPVP;

	data->katana->CLMBase::GetBase()->GetMOT()->arr[data->motor].recvPVP();
	MonPVP = data->katana->CLMBase::GetBase()->GetMOT()->arr[data->motor].GetPVP();    /*lire le PVP*/
	unsigned char uns_ch_pwm = MonPVP->pwm;
	if (uns_ch_pwm>127)
	{
		pwm = (int)(uns_ch_pwm) - 256;
	}
	else
	{
		pwm = (int)(uns_ch_pwm);
	}
}



void *Katana::thread_get_sensors(void *arg)
{
	Arguments *data = (Arguments *)arg;
	CSctBase *sensctrl;
	const TSctDAT *data_sensor;
	gestion_mask_signaux();

	sensctrl = &data->katana->GetBase()->GetSCT()->arr[0];
	data_sensor = sensctrl->GetDAT();
	sensctrl->recvDAT();
	for (int i = 0; i < nb_sensors ; i ++){
		sensors[i] = data_sensor->arr[i];
	}
}

void *Katana::thread_get_velocity(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	speed = data->katana->getMotorVelocityLimit(data->motor);
}

void *Katana::thread_read_master_firmware(void* arg)
{
	const TKatMFW *mfw;
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	arguments->katana->GetBase()->recvMFW();
	mfw = data->katana->GetBase()->GetMFW();


	data->version = mfw->ver;
	data->revision = mfw->rev;
}

void *Katana::thread_set_position(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	//  printf(" thread set_position in\n");

	data->katana->moveMotorToEnc(data->motor, data->pos, data->boolean);


	//  printf(" thread set_position out\n");
}

void *Katana::thread_set_velocity(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	data->katana->setMotorVelocityLimit(data->motor, data->vel);
}


void *Katana::thread_switch_motor(void *arg)
{

	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();


	if(data->boolean == false) {
		data->katana->switchMotorOff(data->motor);
		//    std::cout<<"moteur "<< data->motor << " off !"<< std::endl;
	}
	else {
		data->katana->switchMotorOn(data->motor);
		//std::cout<<"moteur "<< data->motor << " on !"<< std::endl;
	}
}

void *Katana::thread_switch_robot(void *arg)
{
	Arguments *data = (Arguments *)arg;
	gestion_mask_signaux();

	if(data->boolean == 0) {
		data->katana->switchRobotOff();
	}
	else {
		data->katana->switchRobotOn();
	}
}


