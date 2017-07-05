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
#include "main.h"

#define PASSIF_ACTIF 0

#define WAIT_PASSIF_FUNCTION 500000 /* 500 ms */
#define WAIT_SECURITY_FUNCTION 25000 /* 25 ms*/

//#define ROBULAB /* pour fonctionnement sur le robulab (test de la batterie) */
#ifdef ROBULAB
#include "robulab.h"
#warning "USING ROBULAB"
#endif

//#define B_TEXT            /* text message only, same as debug*/
#define B_KATANA            /* command are sent to the Katana (real or simulated on webbots)*/

/*******************************************************************************
 * *****************************************************************************
 *                                   
 *    Definition du robot utilise    
 *                                   
 * *****************************************************************************
 * ****************************************************************************/

//#define ROBOT_ARM1 /* celui du robulab en 2009*/

#define ROBOT_ARM2 /*<4034>*/

//#define WEBOTS /* simulation sous webots */



#ifdef WEBOTS
char katana_addr[]="127.0.0.1";
/*bras webots valeurs extremes*/
int pos_min[6]={-18350,-31000,-31000,-2100,-17950,12500};      /*position min que peuvent atteindre les butees*/ /*need security check !!!*/
int pos_max[6]={31000,6100, 25500,31000,31000,30770};            /*position max que peuvent atteindre les butees*/ /*need security check*/

#warning "WEBOTS ARM IS DEFINED"
char katana_config_file[]="webots_katana6M180.cfg";
#else
char katana_config_file[]="katana6M180.cfg";

#ifdef ROBOT_ARM1

char katana_addr[]="10.0.2.5";

/*bras 1 ex_wall_mount*/
//int pos_min[6]={-12000,-20000,-26000,7000,-16600,18500};      /*position min que peuvent atteindre les butees*/ /*safe*/
//int pos_max[6]={31000,-10000,1000,19000,30000,30000};         /*position max que peuvent atteindre les butees*/ /*safe*/

/*bras 1 ex_wall_mount valeurs extremes*/
int pos_min[6]={-14640,-31000,-31000,-1700,-16600,12500};      /*position min que peuvent atteindre les butees*/ /*need security check !!!*/
int pos_max[6]={31000,5100,1970,31000,31000,30770};            /*position max que peuvent atteindre les butees*/ /*need security check*/

#warning "ARM 1 IS DEFINED"
#else
#ifdef ROBOT_ARM2
char katana_addr[]=   "192.168.168.232";
/*bras 2 <4034>*/
//int pos_min[6]={-12000,-20000,-26000,7000,-16600,12000};      /*position min que peuvent atteindre les butees*/ /*safe*/
//int pos_max[6]={31000,-10000,1000,19000,30000,30000};         /*position max que peuvent atteindre les butees*/ /*safe*/

/*bras 1 ex_wall_mount valeurs extremes*/
int pos_min[6]={-14640,-31000,-31000,-1700,-16600,12000};		/*position min que peuvent atteindre les butees*/ /*need security check !!!*/
int pos_max[6]={31000,5100,1970,31000,31000,30770};				/*position max que peuvent atteindre les butees*/ /*need security check*/
int previous_position[6];										/* Positions of the articulations at the previous call of controle_moteur_activation() */
struct timeval dt_promethe_control;								/* Temps entre 2 appels de controle_moteur_activation() par Promethe */
float dt_moy;													/* Temps moyen entre 2 appels */

/*int pos_min[6]={-12000,-30000,-31000, 0,-16600,12000};          /*!need security check!*/ /*position min que peuvent atteindre les butees*/
/*int pos_max[6]={31000,  5800,  2500, 19000,30000,30000};         /*!need security check!*/ /*position max que peuvent atteindre les butees*/

#warning "ARM 2 <4034> IS DEFINED"
#else
#error "NO ARM DEFINED ---> NO COMPILATION"
#endif
#endif
#endif




/* valable pour les deux bras */
int katana_port=5566;
#define MAXBUF 1024
#define PORT1 1115


int current_target[6]; /*= {0,0,0,0,0,0}*/

struct sigaction act;  /*gestion des signaux*/
Katana *katana=NULL; /* classe d'interface avec le bras Katana*/

#define LEFT false
#define RIGHT true

pthread_mutex_t mutex;

struct TPoint {
	double X, Y, Z;
	double phi, theta, psi;
};

struct TCurrentMot {
	int idx;
	bool running;
	bool dir;
};

struct Tpos{
	static std::vector<int> x,y,z,u,v,w;
	static const int xArr[], yArr[], zArr[], uArr[], vArr[], wArr[];
};


//Katana obj.
//std::auto_ptr<CLMBase> katana;
//std::vector<int> Foo::vec(array, array + sizeof(array)/sizeof(*array));
//positionen, hard-coded. Use values from file instead
const int Tpos::xArr[] = {30206, -23393, -3066, 14454, 30000, 30000};
const int Tpos::yArr[] = {24327, -7837, -16796, 5803, 30290, 31000};
const int Tpos::zArr[] = {24327, -7837, -16796, 5802, 30290, 10924};
const int Tpos::uArr[] = {5333, -13791, -9985, 11449, 30996, 12063};
const int Tpos::vArr[] = {-3799, -5703, -11676, 8210, 30995, 12063};
const int Tpos::wArr[] = {-3799, -5703, -11676, 8210, 30995, 30992};
std::vector<int> Tpos::x(xArr, xArr + sizeof(xArr)/sizeof(*xArr));
std::vector<int> Tpos::y(yArr, yArr + sizeof(yArr)/sizeof(*yArr));
std::vector<int> Tpos::z(zArr, zArr + sizeof(zArr)/sizeof(*zArr));
std::vector<int> Tpos::u(uArr, uArr + sizeof(uArr)/sizeof(*uArr));
std::vector<int> Tpos::v(vArr, vArr + sizeof(vArr)/sizeof(*vArr));
std::vector<int> Tpos::w(wArr, wArr + sizeof(wArr)/sizeof(*wArr));
std::vector<TPoint> points(0);
void StartPointlistMovement();
void StartProgram(int index);
pthread_t tid;
void* RunProgram(void*);
pid_t threadPid;
int retVal = 0;
bool progRunning = false;


/*******************************************************************************
 * Main
 * ****************************************************************************/
int main(int argc, char **argv)
{
	
	if (argc != 3) {
		std::cout << "---------------------------------\n";
		std::cout << "usage: control CONFIGFILE IP_ADDR\n";
		std::cout << "---------------------------------\n";
		return 0;
	}

	std::cout << "--------------------\n";
	std::cout << "CONTROL DEMO STARTED\n";
	std::cout << "--------------------\n";

	//----------------------------------------------------------------//
	//open device: a serial port is opened in this case
	//----------------------------------------------------------------//

		
	std::auto_ptr<CCdlSocket> device;
	std::auto_ptr<CCplSerialCRC> protocol;

	try {

		int port = 5566;
		device.reset(new CCdlSocket(argv[2], port));

		std::cout << "-------------------------------------------\n";
		std::cout << "success:  port " << port << " open\n";
		std::cout << "-------------------------------------------\n";

		//--------------------------------------------------------//
		//init protocol:
		//--------------------------------------------------------//

		protocol.reset(new CCplSerialCRC());
		std::cout << "-------------------------------------------\n";
		std::cout << "success: protocol class instantiated\n";
		std::cout << "-------------------------------------------\n";
		protocol->init(device.get()); //fails if no response from Katana
		std::cout << "-------------------------------------------\n";
		std::cout << "success: communication with Katana initialized\n";
		std::cout << "-------------------------------------------\n";


		katana = new Katana("katana6M90A_G.cfg");


	} catch(Exception &e) {
		std::cout << "ERROR: " << e.message() << std::endl;
		return -1;
	}
	std::cout << "-------------------------------------------\n";
	std::cout << "success: katana initialized\n";
	std::cout << "-------------------------------------------\n\n";

	std::vector<int> encoders(katana->get_nb_motors(), 0);

	TCurrentMot mot[6];
	for (int i = 0; i< 6; i++){
		mot[i].running = false;
		mot[i].idx = i;
		mot[i].dir = true;
		mot[i].dir = RIGHT;
	}

	write_vitesse_all_encoder(60);

	std::cout << "-------------------------------------------\n";
	katana->calibrate();
	std::cout << "-------------------------------------------\n\n";


	return 0;
}


/*******************************************************************************
 *        fonction qui ecrit la vitesse           
 *      a laquelle doit aller les moteurs         
 *    rajout d une securite on ne peut pas        
 *         aller a une vitesse > 100              
 * ****************************************************************************/
void write_vitesse_all_encoder(int velocity)
{

	int idx=0;
	if(velocity < 100)//si la vitesse > seuil pourra etre dangereux ici arbitrairement on a mis 100
	{
		for(idx=0 ; idx < katana->get_nb_motors() ; idx++)
			katana->set_velocity(idx, velocity);
	}

}