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


/*bool freeze;Is true if the robot was frozen*/


/*******************************************************************************
Function used to ensure that the
aim is attend
 * ****************************************************************************/
//a : reference, b : valeur a verifier
bool idem(int *a,std::vector<int>b)
{
	int tolerance = 10;
	bool test = true;
	for (int i = 0 ; i < 6 ; i++)
	{
		if (test == false)
		{return test;}
		else
		{
			test = ((a[i] - tolerance < b[i])&&(a[i] + tolerance >b[i]));
		}
	}
	return test;
}


/*******************************************************************************
Security function
 * ****************************************************************************/
bool security_check(std::vector<int> &encoders_)
{
	/*
  long Secondes;
  long MicroSecondes,mean;
  struct timeval Input;
  struct timeval Output;
  gettimeofday(&Input,NULL);
	 */
	bool no_verif=false;
	static bool passif_mode;
	passif_mode = katana->get_mode_katana(); /* recuperation du mode du bras katana */

	/**
	 * ajout AdR - si les moteurs sont en passif, on ne gere plus la securite
	 * Les tests ne sont faits que sur les 4 premiers moteurs qui sont geres par le mode passif.
	 */
	bool motorOn = true;
	for(int i=0; i<4 && motorOn; i++)
	{
		motorOn = katana->get_motor_state(i);
	}
	if(motorOn==false)
	{
		std::cout << "Mode passif en cours, pas de securite activee"<<std::endl;
		return true;
	}

	//std::cout<<"security check"<<std::endl;

	if (!katana->get_freeze_status())
	{
		Arm * arm = katana->get_cinematique();
		bool not_in_restricted_area = false,
				aim_reached = false;

		/*encoders_ = katana->get_all_position();*/


#ifdef B_TEXT
		for (int i = 0; i < 6 ; i ++)
			std::cout << "encoder "<< i << " : " <<  encoders_[i] << std::endl;
#endif

		aim_reached = idem(arm->goal_encoders,encoders_);
		if (aim_reached)
			no_verif=true;
		not_in_restricted_area = arm->verification(encoders_,no_verif);


		if (!not_in_restricted_area)
		{
			/*stop the robot*/
			for (int i  = 0 ; i < 6 ;i++)
			{
				katana->set_position(i,encoders_[i], false);
        katana->set_previous_velocity(i,0);
        current_target[i]=encoders_[i];
			}
			katana->set_freeze_status(true);
#ifdef B_TEXT
			std::cout <<"robot is stopped"<< std::endl;
#endif

			/* cas particulier : on remet le mode passif dans son etat d'avant la securite apres avoir stoppe le bras*/
			katana->set_passif(passif_mode);
		}
#ifdef B_TEXT
		else
			printf("Security check finished without problem\n");
#endif
		/*
    gettimeofday(&Output,NULL);
    Secondes = Output.tv_sec - Input.tv_sec;
    MicroSecondes = 1000000*Secondes + Output.tv_usec - Input.tv_usec;
    std::cout << "Securite " << MicroSecondes << std::endl;
		 */
		return not_in_restricted_area;
	}
	return true;
}


/*******************************************************************************
passif/actif mode function
 * ****************************************************************************/
/*
 * Return :  true si le bras est desactive
 *                   false sinon
 */
bool passif_function(std::vector<int> encod)
{
	static int I_m = 0;
	static int bonus = 0;
	static bool passif_manip = false;
	static int previous_encod[6];


	if (katana->get_mode_katana()==true)
	{
#ifdef B_TEXT
    std :: cout << "and passive mode is enable ! " << std::endl ;
#endif
    int I_actu;
    unsigned char I_actu_unch;
    int seuil_P = 30; /* experimentalement : Im ~ pwm ~ 13 mais pas �� la mise sous tension.*/
    int seuil_N = -5;
      
    /* surveillance temps 1*
       struct timeval timeIn = { -1, -1 };
       struct timeval timeOut = { -1, -1 };
       gettimeofday(&timeIn, NULL );
       /* surveillance temps 1*/				
      
    I_actu = katana->get_pwm(4); /* old value : 3*/
      
    /* surveillance temps 2*
       gettimeofday(&timeOut, NULL );
       printf("Time is : %ld s, %ld usec\n",timeOut.tv_sec -timeIn.tv_sec, timeOut.tv_usec-timeIn.tv_usec);				
       /* surveillance temps 2*/
      
    I_m = (I_m + I_actu)/2;
      
#ifdef B_TEXT
		std::cout << "and the pwm is " << I_actu << std::endl;
		std::cout << "and Im is " << I_m << std::endl;
#endif

		if ((I_m  > seuil_P)||(I_m < seuil_N))
		{
			for(int k=0; k<4; k++) {
				if(katana->get_motor_state(k))
				{
#ifdef B_TEXT
					std::cout<< "Le moteur "<<k<<" va etre desactive, attention !"<<std::endl;
#endif  
					katana->switch_motor(k,false);
				}
			}

			for(int i=0; i<katana->get_nb_motors(); i++)
      {
				katana->set_previous_velocity(i,0);
        katana->set_desired_velocity(i,0);
			}
			passif_manip = true;
			katana->set_freeze_status(false);
		}
		else
		{
			bool stop = idem(previous_encod,encod);
			if (stop)
			{
				for(int k=0; k<4; k++)
				{
					if(katana->get_motor_state(k)==false)
					{
#ifdef B_TEXT
						std::cout << "passif desactive, moteur "<<k<<" est maintenant ON!" << std::endl;
#endif
						katana->switch_motor(k,true);
						current_target[k] = katana->get_position(k);
					}
				}
				passif_manip = false;
			}
		}
	}
	else
	{
#ifdef B_TEXT
		std::cout << "... but passive mode is OFF..."<< std::endl;
		std::cout<< "Ne peux pas passer en mode passif !!"<< std::endl;
#endif
	}

	for(int i=0;i<6;i++) {
		previous_encod[i] = encod[i];
	}

	return passif_manip;
}


/*******************************************************************************
 * fonction qui affiche certains parametres       
 *            position et vitesse                 
 * ****************************************************************************/

/* fonction incomplete - interface a completer */

void readpvp()
{
	int idx = 0;
	int pos;
	int vit;

	for (idx = 0; idx < katana->get_nb_motors(); idx++)
	{
		pos = katana->get_position(idx);
		vit = katana->get_velocity(idx);
		std::cout << "[moteur " << idx << "] position = " << pos << " - vitesse = " << vit /*<< " - pwm cycle = " << (int)mypvp->pwm*/ << "\n";
	}
}


/*******************************************************************************
 *      fonction qui nous enseigne sur            
 *    la valeur Min et max des encodeurs          
 * ****************************************************************************/
/* fonction incomplete - interface a completer */
void positionMinMaxEncodeur()
{

	int min = 0;
	int max = 0;

	for(int idx=0 ; idx< katana->get_nb_motors() ; idx++)
	{
		min = pos_min[idx]; //katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos();
		max = pos_max[idx]; //katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos();

		std::cout << "moteur[" << idx <<"]" "encoder min = " << min << "\tencoder max = " << max << "\n";
	}
}


/*******************************************************************************
 *  fonction qui active/desactive le robot        
 * ****************************************************************************/
void switchrobot(int activate)
{
#ifdef B_TEXT
	std::cout << "entree dans la fonction switchrobot \n";
#endif
	katana->switch_robot(activate);

	if(activate==false) {
		for(int i=0; i<katana->get_nb_motors(); i++) {
			katana->set_previous_velocity(i,0);
      katana->set_desired_velocity(i,0);
		}
	}
#ifdef B_TEXT
	std::cout << "sortie de la fonction switchrobot \n";
#endif
}


/*******************************************************************************
 *   fonction qui active/desactive un moteur      
 * ****************************************************************************/
void switchmotor(int idx, int activate)
{
#ifdef B_TEXT
	std::cout << "entree dans la fonction switchmotor \n";
#endif
	katana->switch_motor(idx, activate);
	if(activate==false) {
		katana->set_previous_velocity(idx,0);
    katana->set_desired_velocity(idx,0);
	}
#ifdef B_TEXT
	std::cout << "sortie de la fonction switchmotor \n";
#endif
}


/*******************************************************************************
 *        fonction qui lit la vitesse             
 *      a laquelle doit aller les moteurs         
 * ****************************************************************************/
void read_vitesse()
{

	int velocity;
	std::cout << "entree dans la fonction controle_moteur_vitesse \n";
	for(int motorNumber = 0; motorNumber < katana->get_nb_motors(); ++motorNumber) {
		velocity=katana->get_velocity(motorNumber);
		std::cout << "[moteur " << motorNumber << "]" << " - vitesse = " << velocity <<"\n";
	}
	std::cout << "sortie de la fonction controle_moteur_vitesse \n";
}


/*******************************************************************************
 *       fonction qui lit les encodeurs           
 *      a laquelle doit aller les moteurs??       
 * ****************************************************************************/
void read_encodeur(/*CLMBase *katana*/)
{
	int motorNumber = 6;
	std::vector<int> encod;
	encod = katana->get_all_position();
	for (int i = 0; i< katana->get_nb_motors() ; i ++)
		std::cout << encod[i] << std::endl;
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


/*******************************************************************************
 * same function than previous one, but with security model
 * ****************************************************************************/
void controle_moteur_vitesse( int idx, int velocity,int *encoder)
{
	int             i = 0;
	char                m = '\0';
	const TKatMOT           *motor;
	bool change = true;
	std::vector<int> encod;

	long Secondes;
	long MicroSecondes,mean;
	struct timeval Input;
	struct timeval Output;


#ifdef B_TEXT
	printf("speed control on motor %d : parameter = %d \n",idx,velocity);
#endif


	/* si le moteur est desactive, on inhibe la commande en vitesse pour ne pas reactiver le moteur */
	/* on reinitialise la commande memoire pour que lorsque le bras est reactive, on puisse avoir une commande vitesse qui soit envoyee*/
	if(katana->get_motor_state(idx)==false) {
		return;
	}

	//    printf("indice : %d, velocity %d current_target %d previous velocity %d \n", idx, velocity,current_target[idx], katana->get_previous_velocity(idx));

	if (katana->get_previous_velocity(idx) == velocity)
	{
		//            std::cout<<"same previous velocity "<<idx<<" ("<<velocity<<")"<<std::endl;
		//            return; /* on envoie toujours la vitesse !!! */
	}
	else
	{
		if(velocity > 0)
		{
			if (current_target[idx] == pos_max[idx])
				change = false; /*si on est deja en direction du motor alors...*/
			else
			{
				current_target[idx] = pos_max[idx];
				encoder[idx] = pos_max[idx];
				katana->set_position(idx, current_target[idx], false);
			}
			if (idx == 0)
			{
				if (velocity > 100)
					velocity = 100;
			}
			katana->set_velocity(idx, velocity);
		}
		else if (velocity < 0)
		{
			if (current_target[idx] == pos_min[idx])
				change = false;
			else
			{
				current_target[idx] = pos_min[idx];
				encoder[idx] = pos_min[idx];
				katana->set_position(idx, current_target[idx], false);
			}
			if (idx == 0)
			{
				if (velocity < -100)
					velocity = -100;
			}
			katana->set_velocity(idx, -velocity);
		}
		gettimeofday(&Input,NULL);
		if(velocity == 0)
		{
			encoder[idx] = katana->get_position(idx);
			current_target[idx] = encoder[idx];
			katana->freeze_motor(idx);
		}
		gettimeofday(&Output,NULL);
		Secondes = Output.tv_sec - Input.tv_sec;
		MicroSecondes = 1000000*Secondes + Output.tv_usec - Input.tv_usec;
		//      std::cout << "Vitesse " << MicroSecondes << std::endl;
	}

	katana->set_previous_velocity(idx,velocity);
	// printf("previous velocity est %d - current target est %d\n",katana->get_previous_velocity(idx),current_target[idx]);
}

/*******************************************************************************
 * ****************************************************************************/
void controle_moteur_vitesse( int idx, int velocity)
{
	int               i = 0;
	char              m = '\0';
	bool change = true;
	/*parametre pour le calcul de temps*/
	long Secondes;
	long MicroSecondes;
	struct timeval Input;
	struct timeval Output;

#ifdef B_TEXT
	printf("speed control on motor %d : parameter = %d \n",idx,velocity);
#endif


	/*on met la vitesse de ce moteur a velocity*/
	/*on ne peut pas mettre des vitesses negatives*/
	/*lorsqu'on rentre un nombre negatif la vitesse du moteur est tres rapide*/

	/*position d arrivee*/
	/*on reste entre la position min et max*/
	if(velocity > 0)
	{
		if (current_target[idx] == pos_max[idx]) change = false;
		else {
			current_target[idx] = pos_max[idx];
			change = true ;
		}
		if (idx == 0) {if (velocity > 100) velocity = 100;}
		katana->set_velocity(idx, velocity);
	}
	else if (velocity < 0)
	{
		if (current_target[idx] == pos_min[idx]) change = false;
		else {
			current_target[idx] = pos_min[idx];
			change = true ;
		}
		if (idx == 0) {if (velocity < -100) velocity = -100;}
		katana->set_velocity(idx, -velocity);
	}

	if(velocity == 0)
	{
		current_target[idx] = 0;
		katana->freeze_motor(idx);
	}
	else
	{
		if (change)
			katana->set_position(idx, current_target[idx], false);
	}
}


/* PRIVATE FUNCTION */
/*******************************************************************************
 * ****************************************************************************/
float position_to_angle(int position, int idx){
	if( idx == 1 && position >= -31000 && position <= 5100 )
		return (124.25 - (((float)position + 31000.)*140./36100.));
	printf("\t\t\t\t\t\t\t\t\t\tposition = %d\n", position);
	return (124.25 - (((float)position + 31000.)*140./36100.));

	//return 360.;
}

/* PRIVATE FUNCTION */
/*******************************************************************************
 * ****************************************************************************/
int angle_to_encoders(float angle, int idx){
	if( idx == 1 && angle >= 0 && angle <= 140 )
		return ((124.25 - angle)*36100.)/140. - 31000.;
	printf("\t\t\t\t\t\t\t\t\t\tangle = %f\n", angle);
	return ((124.25 - angle)*36100.)/140. - 31000.;
}

/* PRIVATE FUNCTION */
/*******************************************************************************
 * ****************************************************************************/
float distAngle_to_encoders(float distAngle, int idx){
	if( idx == 1 && distAngle >= -140 && distAngle <= 140 )
		return (distAngle*36100.)/140.;
	return 0;
}


/* PRIVATE FUNCTION
 * angle in radians with the 2nd articulation and the vertical
 * */
/*******************************************************************************
 * ****************************************************************************/
float compute_acceleration(float angleArtic2, float a1, float a2, int bDisp){
	float acc, l, angleExt, angleDesired2, k, g = 9.81, m = 0.1;			// INIT MASSE !!!!
	float coord3DExt[3], coord3DMid[3];
	int angleD;
	int iSign = 0;
	Arm * bras = katana->get_cinematique();
	int idx = 1;

	bras->get_3Dpos_of_joint(NB_JOINTS - 1, coord3DExt); // Get coord extremity of the arm
	bras->get_3Dpos_of_joint(idx+1, coord3DMid); // Get coord of the second artic of the arm
	l = sqrt( coord3DExt[0]*coord3DExt[0] + coord3DExt[1]*coord3DExt[1] + coord3DExt[2]*coord3DExt[2]);
	//	angleArtic = position_to_angle(katana->get_position(idx), idx);
	k = sqrt(a1*a1 + a2*a2);
	if( a1 + a2 < 0.0001 )
		angleD = 0;
	else
		angleD = (int)((a1*(float)pos_min[idx] + a2*(float)pos_max[idx]) / (a1 + a2));
	angleDesired2 = (position_to_angle(angleD, 1) + 90)*PI/180.;
	angleExt = atan2 (coord3DExt[2], sqrt(coord3DExt[0]*coord3DExt[0] + coord3DExt[1]*coord3DExt[1]) ) + PI/2.; // Angle in radians between the extremity and the vertical

	float angleMid = atan2 (coord3DMid[2], sqrt(coord3DMid[0]*coord3DMid[0] + coord3DMid[1]*coord3DMid[1]) ) + PI/2.; // Angle in radians between the 2nd articulation and the vertical

//	printf("angleMid = %f     angleArtic2 = %f", angleMid*180./PI, angleArtic2*180./PI);

	/* The effect of the weight may be on the opposite direction */
	if( angleArtic2 > PI &&  bDisp == 1){
		iSign++;
		printf("\t\t\t\t !!!!!!!  ARTIC 2 A PLUS DE 90�� : angleArtic2 = %f  !!!!!!!!!!!!!\n", angleArtic2*180./PI);
	}
	if( (coord3DExt[0] * coord3DMid[0] < 0.) && (coord3DExt[1] * coord3DMid[1] < 0.) &&  bDisp == 1 ){
		iSign++;
		printf("\t\t\t\t\t\t\t !!!!!!!  ARTIC DANS DIR OPPOSE   !!!!!!!!!!!!!\n");
	}

	float factMult = 1;
	// Compute the acceleration
	acc = -(iSign == 1 ? -1 : 1)*(g/l)*sin(angleExt) + (k*factMult/(m*(l*l)))*((angleDesired2 - angleArtic2));

//	if( bDisp == 1 )
//		printf("Compute acc : ACC = %f     angleExt = %f,  angleDesired2 = %f    angleArtic2 = %f      l = %f    k = %f      iSign = %d      (iSign == 1 ? -1 : 1) = %d       (g/l) = %f        sin(angleExt) = %f     -(bSign ? -1 : 1)*(g/l)*sin(angleExt)  = %f      (k/(m*(l*l)))*((angleDesired2 - angleArtic2)) = %f \n",
//								acc, 	angleExt*180./PI, angleDesired2*180./PI, angleArtic2*180./PI,	 l,			 k,			iSign, 		(iSign == 1 ? -1 : 1),				(g/l), 			sin(angleExt), 			-(iSign ? -1 : 1)*(g/l)*sin(angleExt), 			(k/(m*(l*l)))*((angleDesired2 - angleArtic2)));

//	printf("Compute acc : ACC = %f     angleExt = %f,  angleDesired2 = %f    angleArtic2 = %f      l = %f    k = %f      iSign = %d      (iSign == 1 ? -1 : 1) = %d       (g/l) = %f        sin(angleExt) = %f     -(bSign ? -1 : 1)*(g/l)*sin(angleExt)  = %f      (k/(m*(l*l)))*((angleDesired2 - angleArtic2)) = %f \n",
//							acc, 	angleExt*180./PI, angleDesired2*180./PI, angleArtic2*180./PI,	 l,			 k,			iSign, 		(iSign == 1 ? -1 : 1),				(g/l), 			sin(angleExt), 			-(iSign ? -1 : 1)*(g/l)*sin(angleExt), 			(k/(m*(l*l)))*((angleDesired2 - angleArtic2)));


	return acc;
}

//acc = -(g/l)*sin(phi(=angle vers masse) - (k/(m*l^2))*(targetPosition(trad en angle!) - theta(=pos courante));

/*******************************************************************************
 * Control the motor through the co-activation of antagonist muscles *
 * ****************************************************************************/
void controle_moteur_activation(int idx, float a1, float a2, int *encoder)
{
	int i = 0;
	char m = '\0';
	int targetPosition, velocity;
	float x1, v1, acc1, x2, v2, acc2, x3, v3, acc3, x4, v4, acc4, xf, vf, dt;
	//	const TKatMOT *motor;
	bool change = true;
	std::vector<int> encod;

	long Secondes;
	long MicroSecondes,mean;
	struct timeval Input;
	struct timeval Output;
	struct timeval dt_promethe_control_2;


#ifdef B_TEXT
	printf("Muscle activation control on motor %d, parameter : a1 = %d, a2 = %d \n",idx,a1,a2);
#endif


	/* si le moteur est desactive, on inhibe la commande en vitesse pour ne pas reactiver le moteur */
	/* on reinitialise la commande memoire pour que lorsque le bras est reactive, on puisse avoir une commande vitesse qui soit envoyee*/
	if(katana->get_motor_state(idx)==false) {
		return;
	}

	//    printf("indice : %d, velocity %d current_target %d previous velocity %d \n", idx, velocity,current_target[idx], katana->get_previous_velocity(idx));


	/* Compute the desired position x*/

	float vitesse_simulation = 1./1.;

	if( idx != 1 ){
		if( a1 + a2 < 0.0001 )
			targetPosition = 0;
		else
			targetPosition = (int)((a1*(float)pos_min[idx] + a2*(float)pos_max[idx]) / (a1 + a2));


		velocity = vitesse_simulation*(((targetPosition - katana->get_position(idx))*300/(pos_max[idx] - pos_min[idx]))*sqrt((a1*a1 + a2*a2)));  // TODO: AJOUTER VIT MAX EN PARAM DE LA FCT (=60)
		//velocity = (targetPosition - katana->get_position(idx))*60/(pos_max[idx] - pos_min[idx]);
	}
	else{




		// Pesanteur



		// PESANTEUR

		/* RUNGE KUTTA
        x1 = x
        v1 = v
        a1 = a(x1, v1, 0)

        x2 = x + 0.5*v1*dt
        v2 = v + 0.5*a1*dt
        a2 = a(x2, v2, dt/2.0)

        x3 = x + 0.5*v2*dt
        v3 = v + 0.5*a2*dt
        a3 = a(x3, v3, dt/2.0)

        x4 = x + v3*dt
        v4 = v + a3*dt
        a4 = a(x4, v4, dt)

        xf = x + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4)
        vf = v + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4)
		 */

		Arm * bras = katana->get_cinematique();
		//float coord3DExt[3];
		float coord3DMid[3];
		//bras->get_3Dpos_of_joint(NB_JOINTS - 1, coord3DExt); // Get coord extremity of the arm
		bras->get_3Dpos_of_joint(idx, coord3DMid); // Get coord of the second artic of the arm
		int posKatanaIdx = katana->get_position(idx);



		gettimeofday(&dt_promethe_control_2,NULL);
		Secondes = dt_promethe_control_2.tv_sec - dt_promethe_control.tv_sec;
		MicroSecondes = 1000000*Secondes + dt_promethe_control_2.tv_usec - dt_promethe_control.tv_usec;
		if( MicroSecondes > 1000000 ){
			/* 1st iteration -> initialization */
			MicroSecondes = 100000; /* == 1/10s */
			dt_moy = 0.1;
			previous_position[idx] = pos_min[idx];
		}
		dt = (float)MicroSecondes/1000000.; /* Time in secondes */
//		printf(" \t\t\t last dt = %f \n", dt);
		dt_moy = 0.9*dt_moy + 0.1*dt;
		dt = dt_moy * vitesse_simulation; /* Simulation temps ralenti */


//printf("position_to_angle(posKatanaIdx, idx)  =  %f\n", position_to_angle(posKatanaIdx, idx));
		x1 = (position_to_angle(posKatanaIdx, idx) + 90) * PI/180.; // Angle in radians between 2nd articulation and vertical
		v1 = ( ((position_to_angle(previous_position[idx],idx)) + 90)*PI/180. - x1 ) / ((float)(MicroSecondes/1000000.)*vitesse_simulation); /* Radians/secondes . Pb :previous_position non initialis�� (->1ere val mauvaise) */
		//x1 = atan2 (coord3DMid[2], sqrt(coord3DMid[0]*coord3DMid[0] + coord3DMid[1]*coord3DMid[1]) ) + PI/2.; // Angle in radians between the 2nd articulation and the vertical
		acc1 = compute_acceleration(x1, a1, a2, 1);
		// acc = -(g/l)*sin(phi(=angle vers masse) - (k/(m*l^2))*(targetPosition(trad en angle!) - theta(=pos courante));

		x2 = x1 + 0.5*v1*dt;
		v2 = v1 + 0.5*acc1*dt;
		acc2 = compute_acceleration(x2, a1, a2, 0);

		x3 = x1 + 0.5*v2*dt;
		v3 = v1 + 0.5*acc2*dt;
		acc3 = compute_acceleration(x3, a1, a2, 0);

		x4 = x1 + v3*dt;
		v4 = v1 + acc3*dt;
		acc4 = compute_acceleration(x4, a1, a2, 0);

		xf = x1 + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4);
		vf = v1 + (dt/6.0)*(acc1 + 2*acc2 + 2*acc3 + acc4);

//		printf("RUNGE KUTA xf = %f\n", xf*180./PI);
		//xf = x1 + dt*(v1 + dt*acc1);
//		printf("SIMPLE xf = %f\n", (x1 + dt*(v1 + dt*acc1))*180./PI);


		float fVelo = - distAngle_to_encoders( xf*180./PI - x1*180./PI, idx)*0.01/dt_moy; /* negatif because when angle increase, encoders decrease */
		velocity = (int)(fVelo+.5);


//		if(abs(fVelo) < 1)
//			velocity = fVelo > 0 ? 1 : -1;
//		printf("VELOCITY = %d\n", velocity);



		//velocity = (angle_to_encoders(xf,idx) - posKatanaIdx)*0.01/dt_moy;

//		printf(" \tVelocity Motor 1 : %d   pos_cur = %d enc      pos_dest = %d enc       dt = %f s     x1 = %f deg       xf = %f deg\n  v1 = %f rad/s     acc1 = %f  rad/s^2         acc2 = %f  rad/s^2           acc3 = %f  rad/s^2            acc4 = %f rad/s^2\n\n", velocity, katana->get_position(idx), angle_to_encoders(xf,idx), dt, x1*180./PI, xf*180./PI, v1*180./PI, acc1, acc2, acc3, acc4);

//		printf(" \tVelocity Motor 1 : %d   pos_cur = %d enc      pos_dest = %d enc       dt = %f s     x1 = %f deg       xf = %f deg\n  v1 = %f rad/s     acc1 = %f  rad/s^2         acc2 = %f  rad/s^2           acc3 = %f  rad/s^2            acc4 = %f rad/s^2\n\n", velocity, katana->get_position(idx), angle_to_encoders(xf,idx), dt, x1*180./PI, xf*180./PI, v1*180./PI, acc1, acc2, acc3, acc4);


		/*
		// PESANTEUR   ANCIENNE VERSION
		Arm * bras = katana->get_cinematique();
		float coord3DExt[3], coord3DMid[3];
		bras->get_3Dpos_of_joint(NB_JOINTS - 1, coord3DExt); // recuperation des coordonnees extr��mit�� du bras
		float weight = sqrt(coord3DExt[0]*coord3DExt[0] + coord3DExt[1]*coord3DExt[1])/bras->get_arm_length();
		int gravity = (int)(60*weight); 										//===================================> 60 ?????????????????????
		bras->get_3Dpos_of_joint(1, coord3DMid); // recuperation des coordonnees 2nde articulation/

		int bChge = 0;
		if( katana->get_position(idx) < -22233 ){ // Motor 2 at 90��
			gravity = -gravity;
			bChge++;
		}

		if( (coord3DExt[0] * coord3DMid[0] < 0.) && (coord3DExt[1] * coord3DMid[1] < 0.) ){
			gravity = -gravity;
			bChge++;
		}
		velocity += gravity;
//*/



		gettimeofday(&dt_promethe_control,NULL);
		previous_position[idx] = posKatanaIdx;


		//		printf("Les coordonnees de l'extr��mit�� sont : %f, %f, %f\n",coord3DExt[0],coord3DExt[1],coord3DExt[2]);
		//		printf(	"Les coordonnees de la 2eme arti sont : %f, %f, %f\n",coord3DMid[0],coord3DMid[1],coord3DMid[2]);
		//		printf(	"POSITION 2eme ARTIC : \t%d \tChange : %d\n", katana->get_position(idx), bChge );
		//		printf(	"POIDS �� %f soit \t%d \n", weight*100, gravity);
	}





	if( velocity > 60 ) {
		velocity = 60;
	}
	if( velocity < -60 ) {
		velocity = -60;
	}


	//	printf("Muscle activation control on motor %d, parameter : a1 = %f, a2 = %f, TARGET = %d, VELOCITY = %d\n",idx,a1,a2, targetPosition, velocity);


	//	if( idx == 1 && katana->get_position(2) == -14515 && katana->get_position(3) == 14650 ){
	//		printf("Muscles 2 et 3 align��s \n");
	//		katana->set_position(idx, current_target[idx], false);
	//
	//	}


	if (katana->get_previous_velocity(idx) == velocity)
	{
		//            std::cout<<"same previous velocity "<<idx<<" ("<<velocity<<")"<<std::endl;
		//            return; /* on envoie toujours la vitesse !!! */
	}
	else
	{
		if(velocity > 0)
		{
			if (current_target[idx] == pos_max[idx])
				change = false; /*si on est deja en direction du motor alors...*/
			else
			{
				current_target[idx] = pos_max[idx];
				encoder[idx] = pos_max[idx];
				katana->set_position(idx, current_target[idx], false);
			}
			if (idx == 0)
			{
				if (velocity > 100)
					velocity = 100;
			}
			katana->set_velocity(idx, velocity);
		}
		else if (velocity < 0)
		{
			if (current_target[idx] == pos_min[idx])
				change = false;
			else
			{
				current_target[idx] = pos_min[idx];
				encoder[idx] = pos_min[idx];
				katana->set_position(idx, current_target[idx], false);
			}
			if (idx == 0)
			{
				if (velocity < -100)
					velocity = -100;
			}
			katana->set_velocity(idx, -velocity);
		}
		gettimeofday(&Input,NULL);
		if(velocity == 0)
		{
			encoder[idx] = katana->get_position(idx);
			current_target[idx] = encoder[idx];
			katana->freeze_motor(idx);
		}
		gettimeofday(&Output,NULL);
		Secondes = Output.tv_sec - Input.tv_sec;
		MicroSecondes = 1000000*Secondes + Output.tv_usec - Input.tv_usec;
		//      std::cout << "Vitesse " << MicroSecondes << std::endl;
	}

	katana->set_previous_velocity(idx,velocity);
	// printf("previous velocity est %d - current target est %d\n",katana->get_previous_velocity(idx),current_target[idx]);
}


/*******************************************************************************
 * ****************************************************************************/
void gocalibrate(/*CLMBase *katana*/)
{
	std::cout << "calibration en cours ... NE PAS STOPPER LE PROGRAMME MEME AVEC UN CTRL+C\n";
	katana->calibrate();
	std::cout << "calibration terminee\n";
}


/*******************************************************************************
 *           lis les capteurs de la pince 
 * ****************************************************************************/
void readsensorvalue()
{
	int capteur_init[16]={};
	int *sensors;
	std::cout << "\nCurrent Sensor values:" << std::endl;
	sensors = katana->get_sensors();
	for (int i=0; i<katana->get_nb_sensors(); i++)
	{
		std::cout.width(5);
		std::cout << sensors[i] << " ";
	}
	std::cout << "\n";
}

/*******************************************************************************
 * fonction prise d un objet?
 * ****************************************************************************/
void valeur_capteur(int *capteur_init)
{
	int *capt_temp;
	if(capteur_init == NULL)
	{
		std::cout << "erreur de malloc\n";
		exit(1);
	}

	capt_temp = katana->get_sensors();

	for(int i=0; i<16; i++) {
		capteur_init[i] = capt_temp[i];
	}
}


/*******************************************************************************
 * lit la version du firmware
 * ****************************************************************************/
short readmasterfirmware()
{
	short             version;
	short             revision;

	katana->read_master_firmware(&version,&revision);

	std::cout << "version : " << version << " revision : " << revision << std::endl;

	return  version;
}


void go_to_sleep_position(Arm *katana_arm)
{
	bool test_security;
	bool position_not_reached;
	int curr_pos;

	int encoder[6] = {30000,-26700,-30800,30800,30800,30700};
	std::vector<int> encod;

	for(int i=0; i<6; i++){
		encod.push_back(encoder[i]);
	}

	int precision = 10; /* precision sur les encodeurs pour dire que deux positions sont identiques */

	printf("Go to sleep position \n");

	/* demarrage des moteurs */

	for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
	{
		katana->set_velocity(idx, 0); /* freeze motors */
		//      printf("ok ici \n encodeur[%d] %d \n",idx,encoder[idx]);
		katana->set_position(idx,encoder[idx] , false);
		current_target[idx] = encoder[idx];

	}

	/* on assure la securite pendant le mouvement */
	katana->set_freeze_status(false);
	test_security = security_check(encod);

	for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
	{
		katana->set_velocity(idx, 60);/* need to be fast enough*/
	}


	position_not_reached = true;
	while(test_security && position_not_reached) {
		test_security = security_check(encod);
		position_not_reached = false;
		for(int i = 0; i< 6; i++) {
			curr_pos=katana->get_position(i);
			position_not_reached = position_not_reached || !(encoder[i]-precision < curr_pos && curr_pos < encoder[i]+precision);
			//        printf("[%d] current pos %d, dest_position %d, security %d\n",i,curr_pos,encoder[i],test_security);
		}
	}

	if(test_security==false)  {
		for (int i=0;i<katana->get_nb_motors();i++) {
			katana->set_velocity(i, 0); /* freeze motors */
			int pos = katana->get_position(i);
			current_target[i] = pos;
			katana->set_position(i, pos, false); /* move to current position */
			/* moteur bloques */
		}
		std::cout<<"Security stopped arm ! \nCheck position to avoid collision in case of low battery\n";
		exit(1);
	}

	//  printf("position intermediaire pour le repos atteinte !\n");

	/* final movement */
	encoder[0] = 30800;
	encod[0] = 30800;
	encoder[1] = -30800;
	encod[1] = -30800;

	/* demarrage des moteurs */

	for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
	{
		katana->set_position(idx,encoder[idx] , false);
		current_target[idx] = encoder[idx];
	}

	/* on assure la securite pendant le mouvement */
	katana->set_freeze_status(false);
	test_security = security_check(encod);

	position_not_reached = true;
	while(test_security && position_not_reached) {
		test_security = security_check(encod);
		position_not_reached = false;
		for(int i = 0; i< 6; i++) {
			curr_pos=katana->get_position(i);
			position_not_reached = position_not_reached || !(encoder[i]-precision < curr_pos && curr_pos < encoder[i]+precision);
			//        printf("[%d] current pos %d, dest_position %d, security %d\n",i,curr_pos,encoder[i],test_security);
		}
	}

	if(test_security==false)
	{
		for (int i=0;i<katana->get_nb_motors();i++) {
			katana->set_velocity(i, 0); /* freeze motors */
			int pos = katana->get_position(i);
			current_target[i] = pos;
			katana->set_position(i, pos, false); /* move to current position */
			/* moteur bloques */
		}
		std::cout<<"Security stopped arm ! \nCheck initial position of the arm before running calibration!\n Check position to avoid collision in case of low battery\n";
		exit(1);
	}

}



/** to move to a given position with security checked */
void secured_move_to_position(Arm *katana_arm, int encoder[6], int speed) {
  bool test_security;
  bool position_not_reached;
  int curr_pos;
  std::vector<int> encod;

  int precision = 50; /* precision sur les encodeurs pour dire que deux positions sont identiques */

  /** init encod */
  for(int i=0; i<6; i++){
    encod.push_back(encoder[i]);
  }

  /* demarrage des moteurs */

  for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
  {
    katana->set_velocity(idx, 0); /* freeze motors */
    katana->set_position(idx,encoder[idx] , false);
    current_target[idx] = encoder[idx];

  }

  /* on assure la securite pendant le mouvement */
  katana->set_freeze_status(false);
  test_security = security_check(encod);

  for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
  {
    katana->set_velocity(idx, speed);/* need to be fast enough*/
  }

  position_not_reached = true;
  while(test_security && position_not_reached) {
    test_security = security_check(encod);
    position_not_reached = false;
    for(int i = 0; i< 6; i++) {
      curr_pos=katana->get_position(i);
      position_not_reached = position_not_reached || !(encoder[i]-precision < curr_pos && curr_pos < encoder[i]+precision);
      //printf("[%d] current pos %d, dest_position %d, security %d\n",i,curr_pos,encoder[i],test_security);
    }
  }

  if(test_security==false)  {
    /** redondant a priori */
    for (int i=0;i<katana->get_nb_motors();i++) {
      katana->set_velocity(i, 0); /* freeze motors */
      int pos = katana->get_position(i);
      current_target[i] = pos;
      katana->set_position(i, pos, false); /* move to current position */
      /* moteur bloques */
    }
    std::cout<<"Security stopped arm ! \nCheck position to avoid collision in case of low battery\n";
    exit(1);
  }

}


// int pos_min[6]={-14640,-31000,-31000,-1700,-16600,12000};
// int pos_max[6]={31000,5100,1970,31000,31000,30770};   


/** to be used with ARM2 on the robulab 
 *  init position is : {31000,-31000,-31000,31000,31000,30700}
 **/
void go_to_neutral_position_from_init(Arm *katana_arm)
{
  /** to be implemented */
  int encoder[6] = {31000,-31000,-31000,31000,31000,12500};
  int init[6] = {31000,-31000,-31000,31000,31000,30700};
  std::vector<int> encod;

  printf("Go to neutral position from init position \n");

  /** check current position if it is too different from init
   * position dont do anything */
  
  /* initialisation des goal_encoders */
  encod = katana->get_all_position();
  for(int i=0; i<katana->get_nb_motors()-1; i++) { /** dont consider gripper opening */
    if(abs(encod[i] - init[i]) > 500) {
      printf("Current position is not init position [%d](%d / %d). Dont move ! STOP NOW !\n",i,encod[i],init[i]);
      printf("Move arm to init position (end of calibration before performing go_to_neutral_position_from_init\n");
      exit(-1);
    }
  }

  secured_move_to_position(katana_arm, encoder, 50); /** no danger */

  encoder[4] = -5500;
  secured_move_to_position(katana_arm, encoder, 80); /** no danger */

  encoder[0] = 28000;
  secured_move_to_position(katana_arm, encoder, 50); 

  encoder[3] = 25000;
  secured_move_to_position(katana_arm, encoder, 20); /** low speed, critical part */

  encoder[3] = 8000;
  encoder[2] = -17900;
  encoder[1] = -17000;
  secured_move_to_position(katana_arm, encoder, 40); 

  encoder[5] = 24000;
  encoder[4] = 6000;
  encoder[0] = 16000;
  secured_move_to_position(katana_arm, encoder, 40); 
}

/** to be used with ARM2 on the robulab 
 *  neutral position is {16000,-17000,-17900,8000,6000,24000} // {16000,-15000,-25000,2000,6000,12500}
 **/
//~ void go_to_sleep_position_from_neutral(Arm *katana_arm)
//~ {
  //~ int encoder[6] = {16000,-17000,-17900,8000,6000,28000};
//~ 
  //~ printf("Go to sleep position \n");
//~ 
  //~ /** do not forget to open widely the gripper to be sure that any
   //~ * hold object would be released. */
  //~ secured_move_to_position(katana_arm, encoder, 40); /** low speed, for the moment */
//~ 
  //~ encoder[5] = 12500;
  //~ encoder[4] = -5500;
  //~ encoder[0] = 28000; 
  //~ secured_move_to_position(katana_arm, encoder, 40); 
//~ 
  //~ encoder[3] = 25000;
  //~ encoder[2] = -29000;  
  //~ encoder[1] = -23000;
  //~ secured_move_to_position(katana_arm, encoder, 50); 
  //~ 
  //~ encoder[2] = -31000; 
  //~ encoder[1] = -31000;
  //~ secured_move_to_position(katana_arm, encoder, 50); 
//~ 
  //~ encoder[3] = 31000;
  //~ secured_move_to_position(katana_arm, encoder, 20); /** low speed, for the moment */
//~ 
  //~ encoder[0] = 31000;
  //~ secured_move_to_position(katana_arm, encoder, 50); /** low speed, for the moment */
//~ 
  //~ encoder[4] = 31000;
  //~ secured_move_to_position(katana_arm, encoder, 80); /** low speed, for the moment */
//~ 
  //~ encoder[5] = 15000; /** is it that much important ? */
  //~ secured_move_to_position(katana_arm, encoder, 50); /** low speed, for the moment */
//~ }

/** to be used with ARM2 on the robulab */
void go_neutral_position(Arm *katana_arm)
{
  bool test_security;
  bool position_not_reached;
  int curr_pos;

  /* add here a #define to select the neutral position according to
   * the arm that is used*/
  int encoder[6] = {16000,-17000,-17900,8000,7000,24000};

  std::vector<int> encod;

  for(int i=0; i<6; i++){
    encod.push_back(encoder[i]);
  }

  int precision = 10; /* precision sur les encodeurs pour dire que deux positions sont identiques */



  /* demarrage des moteurs */

  for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
  {
    katana->set_velocity(idx, 0); /* freeze motors */
    //      printf("ok ici \n encodeur[%d] %d \n",idx,encoder[idx]);
    katana->set_position(idx,encoder[idx] , false);
    current_target[idx] = encoder[idx];
  }
  
  /* on assure la securite pendant le mouvement */
  katana->set_freeze_status(false);
  test_security = security_check(encod);
  
  for(int idx=0 ; idx < katana->get_nb_motors() ; idx++)
  {
    katana->set_velocity(idx, 40); /* let motor go smoothly if security is ok */
  }
  
  
  position_not_reached = true;
  while(test_security && position_not_reached) {
    test_security = security_check(encod);
    position_not_reached = false;
    for(int i = 0; i< 6; i++) {
      curr_pos=katana->get_position(i);
      position_not_reached = position_not_reached || !(encoder[i]-precision < curr_pos && curr_pos < encoder[i]+precision);
//	      printf("[%d] current pos %d, dest_position %d, security %d\n",i,curr_pos,encoder[i],test_security);
    }
  }
  
  if(test_security==false)  {
    for (int i=0;i<katana->get_nb_motors();i++) {
      katana->set_velocity(i, 0); /* freeze motors */
      int pos = katana->get_position(i);
      current_target[i] = pos;
      katana->set_position(i, pos, false); /* move to current position */
      /* moteur bloques */
    }
    std::cout<<"Security stopped arm ! \nCheck initial position of the arm before running calibration!\n Check position to avoid collision in case of low battery\n";
    exit(1);
  }
  
}

void capture_signal(int signo, siginfo_t *info, void *context)
{
	int err;
	static int count =0;

	fprintf(stdout, "sig = %i (%i) - code = %i\n", signo, info->si_signo, info->si_code);
	printf("count = %d\n", count);
	count++;
	if(count>5) {
		perror("to many error while trying to reach safe position\nHard stop now !!!");
		exit(1);
	}

	int pos=0;

	if(signo==SIGUSR1) {
		printf("Low battery !!\n");
	}

	printf("Stop broker\n");
	/*
	 ** ici inclure le code pour traiter le signal capturer
	 ** - blocage des moteurs
	 ** - ... etc ...
	 */
	if(katana!=NULL) {
		if(katana->is_calibrated()) {

			katana->set_passif(false);
			Arm *katana_arm = katana->get_cinematique(); /* pour gerer la securite pendant les mouvements */
			printf("bug hunting 1 - main.cpp\n");
			katana_arm->close_files();

			printf("bug hunting 2 - main.cpp\n");

			for (int i=0;i<katana->get_nb_motors();i++) {
				katana->set_velocity(i, 0); /* freeze motors */
				pos = katana->get_position(i);
				current_target[i] = pos;
				katana->set_position(i, pos, false); /* move to current position */
				/* moteur bloques */
			}

			/* go to neutral position */
			go_neutral_position(katana_arm);

			/* go to safe position */
			go_to_sleep_position(katana_arm);

			std::cout<<"Arm reached safe position"<<std::endl;
			/*katana->~Katana();*/
		}
		else {
			std::cout<<"Katana not calibrated !!\n";
		}
	}
	else
		std::cout<<"Katana not calibrated (Katana==NULL)\n"<<std::endl;

	exit(1);
	return;
}


/*******************************************************************************
 * Test si le bras a ete calibre
 * ****************************************************************************/
/*
 * a priori lorqu on eteint le robot et que l on demandes les
 *valeurs des encodeurs les valeurs sont toujours les memes
 *dans toutes les positions des encodeurs
 *ca peut etre un bon moyen de savoir si l on a fait
 *la calibration ou non
 */
int is_calibrated(/*CLMBase *katana*/)
{
	int avant_calib[6]={28920,31000,-29536,23920,-31000,-31000};
	int erreur=0;
	int erreur_acc=0;
	short encodeur;
	int motorNumber;

	std::cout << "entree dans la fonction is_calibrated"<<std::endl;;

	for(short motorNumber = 0; motorNumber < katana->get_nb_motors(); ++motorNumber) {
		encodeur= katana->get_position(motorNumber);
		erreur=encodeur-avant_calib[motorNumber];

		if(erreur<0)
			erreur=-erreur;

		std::cout << "position= " << encodeur << "erreur= " << erreur  <<"\n";

		erreur_acc = erreur_acc + erreur;
	}

	std::cout << "sortie de la fonction is calibrated \n";


	if(erreur > 10)
	{
		katana->set_calibrated(true);
		return 1;
	}
	else
	{
		katana->set_calibrated(false);
		return 0;
	}

}


/*******************************************************************************
 * Test pouvant etre lance depuis ivy          ***
 * ****************************************************************************/
void test()
{
	/* you can put the code you want here and call this function from ivy */
}


/*******************************************************************************
 * *****************************************************************************
 * Broker Methodes
 * *****************************************************************************
 * ****************************************************************************/

/*******************************************************************************
 * Constructor
 * ****************************************************************************/
Broker::Broker(const char *filename)
{
  
  mxml_node_t *tree=NULL;
	mxml_node_t *node=NULL;
	FILE *f=NULL;
	char *p=NULL;
  
  
  strncpy(addr, "127.0.0.1", sizeof("127.0.0.1"));
  robulab = false;
  ivy = true;
  
  f=fopen(filename, "r");
	if(f==NULL)
	{
		printf("unable to open %s", filename);
		exit(EXIT_FAILURE);
	}
	tree = mxmlLoadFile(NULL, f, MXML_TEXT_CALLBACK);
	fclose(f);
	node = mxmlFindElement(tree, tree, "broker", NULL, NULL, MXML_DESCEND);
  /*is the katana installed on a robulab*/
	p=(char*)mxmlElementGetAttr(node, "robulab");
	if(p == NULL)
	{
		std::cout << "warning, no robulab found in" << filename << std::endl;
	}
  else
  {
    if(strncmp(p, "yes", sizeof("yes")) == 0)
    robulab = true;
  }
  
  p=(char*)mxmlElementGetAttr(node, "ivy");
	if(p == NULL)
	{
		std::cout << "warning, no ivy found in" << filename << std::endl;
	}
  else
  {
    if(strncmp(p, "no", sizeof("no")) == 0)
    ivy = false;
  }
  
	p=(char*)mxmlElementGetAttr(node, "port");
	if(p == NULL)
	{
		std::cout << "warning, no port specified in" << filename << " -> using 1115" << std::endl;
    port = 1115;
	}
  else
    port = atoi(p);
    
	p=(char*)mxmlElementGetAttr(node, "ip");
	if(p == NULL)
	{
		std::cout << "warning, no ip specified in" << filename << " -> using 127.0.0.1" << std::endl;
	}
  else
   strncpy(addr, p, 15*sizeof(char));
  
}


/*******************************************************************************
 * Destructor
 * ****************************************************************************/
Broker::~Broker()
{
}


/*******************************************************************************
 * Init
 * ****************************************************************************/
void Broker::init_robulab()
{
  int pid;
  
  
  if(robulab)
  {
    pid = getpid();

    if (pthread_create(Robulab::get_pthread(), NULL, Robulab::pthread_check_battery, (void *)&pid)!= 0)
    {
      std::cerr<< "Thread_robulab not created, program stopped\n"<<std::endl;
      exit(1);
    }
  }
}


/*******************************************************************************
 * is the robulab defined
 * ****************************************************************************/
bool Broker::is_robulab_defined()
{
  return robulab;
}


/*******************************************************************************
 * is ivy needed
 * ****************************************************************************/
bool Broker::is_ivy_needed()
{
  return ivy;
}


/*******************************************************************************
 * Main
 * ****************************************************************************/
int main(int argc, char **argv)
{
  Broker *broker = NULL;
	int i;
	char  go = '\0';
	int motor_number;  /*stocke le numero du moteur recu dans la commande*/
	int velocity=10;
	struct sockaddr_in server,client;
	struct hostent *hp;
	char buf[MAXBUF];
	int buf_len, sk,n_sent,n_read;
	socklen_t client_ln;
	int vit_ou_pos=0;
	int err;
	int stiffness;


	int * encoder_prec = new int[6];

	for (int indice = 0 ; indice < 6 ; indice ++)
	{encoder_prec[indice] = -100000;}

	std::vector<int> encod;
	std::vector<int> curr_encoders; /*containt proprioception of the arm*/

	bool mode = false;
  bool robulab = false;

	char speed[256];
	char position[256];
	int pince;                /*nous dit si il y a un object dans la pince*/ /*a transformer en booleen*/
	char numero[256];
	char commande[256];
	char separateur[256];
	char param[256];        /*parametre qui controle la vitesse ou la position*/


	memset(&act, 0, sizeof(struct sigaction));
	// Pendant la capture d'un signal, on ne pourra pas recevoir d'autre signaux
	// Pour autoriser les signaux pendant une capture, utiliser sigemptyset(...)
	sigfillset(&act.sa_mask);

	// On precise qu'on veut des informations sur le signal capture
	act.sa_flags = SA_SIGINFO;

	// On definit la fonction qui sera appelee lors de la reception d'un signal
	// on utilise sa_sigaction a la place de sa_handler,
	// car on a le flag SA_SIGINFO
	act.sa_sigaction = capture_signal;

	// Prepare la capture de TOUS les signaux.
	// _NSIG est defini dans bit/signum.h et correspond au numero du signal
	// max + 1. Il tient compte des signaux temps reel

	int indice_signal;

	for(indice_signal = 1; indice_signal < _NSIG; indice_signal++)
		sigaction(indice_signal, &act, NULL);

	if(argc < 2)
	{
		std::cout << "error, you must specify a config file as argument" << std::endl;
		exit(EXIT_FAILURE);
	}
  
  /* getting the information for the broker and launching it correctly */
  broker = new Broker(argv[1]);
  broker->init_robulab();
  

	/** Initialisation of the arm */
	katana = new Katana(argv[1]);    /*katana est une variable globale*/
	is_calibrated();
	Arm *katana_arm = katana->get_cinematique(); /* une fois que katana a ete instancie, on recupere la cinematique */
	/* initialisation des goal_encoders */
	encod = katana->get_all_position();
	for (i=0;i<katana->get_nb_motors();i++)
	{
		katana_arm->goal_encoders[i]=encod[i];
	}


	/**********        parametre pour ivy       ***********/
  if(broker->is_ivy_needed())
  {
    const char* bus = 0;


    /* handling of environment variable */
    if (!bus)
      bus = getenv("IVYBUS");

    /* initializations */
    IvyInit ("mon_hello", "Hello le monde", 0, 0, 0, 0);
    IvyStart (bus);

    /* binding of HelloCallback to messages starting with 'Hello' */
    IvyBindMsg (hello_Callback, 0, "^Hello(.*)");

    /* binding of ReadyCallback to 'Ready' */
    IvyBindMsg (ready_Callback, 0, "^Ready$");

    /* binding of help_callback to 'Help'*/
    IvyBindMsg (help_Callback, 0, "^Help$");

    /* binding of isCalibrate_callback to 'Calibrated'*/
    IvyBindMsg (isCalibrate_Callback, 0, "^Calibrated$");

    /* binding of firmware_callback to 'Version' */
    IvyBindMsg (firmware_Callback, 0, "^Version$");

    /* binding of Gocalibration_callback to 'Gocalibration' */
    IvyBindMsg (gocalibration_Callback, 0, "^Gocalibration$");

    /* binding of Status_callback to 'Status' */
    IvyBindMsg (status_Callback, 0, "^Status$");

    /* binding of SwitchOff_callback to 'SwitchOff' */
    IvyBindMsg (switchOff_Callback, 0, "^SwitchOff$");

    /* binding of SwitchOn_callback to 'SwitchOn' */
    IvyBindMsg (switchOn_Callback, 0, "^SwitchOn$");

    /* binding of Proprio_callback to 'Proprio' */
    IvyBindMsg (proprio_Callback, 0, "^Proprio$");

    /* binding of Test_callback to 'Test' */
    IvyBindMsg (Test_Callback, 0, "^Test$");

    /* binding of Security_check_callback to '3Dpos' */
    IvyBindMsg (position3D_Callback, 0, "^3Dpos$");

    /* binding of Security_check_callback to 'Passif' */
    IvyBindMsg (passif_Callback, 0, "^Passif$");

    std::cout << "Waiting for message 'Ready' from ivy ...\n";

    /* main loop */
    IvyMainLoop();



    std::cout << "End of Ivy main loop, moving the arm to default position ...\n";


  }
  else
  {
    if(is_calibrated() == 0)
    {
      std::cout << "---->CALIBRATION PAS OK\n" << std::endl;
      std::cout << "Calibration du bras en cours ..." << std::endl;
      gocalibrate();
      std::cout << "... Fin de la calibration du bras" << std::endl;
    }
    else
    {  
      std::cout << "---->CALIBRATION OK\n" << std::endl;
     
    }
  }
  /** go to initial position */
    go_to_neutral_position_from_init(katana_arm);
	printf("############## SERVER START ################\n");


	if (argc != 2) {
		printf("Usage: %s configfile \n",argv[0]);
		exit(0);
	}

	// creation d'un socket
	//IP protocol family(PF_INET)
	//UDP (SOCK_DGRAM)

	if( (sk=socket(PF_INET,SOCK_DGRAM,0)) < 0 ) {
		printf("Error Creating socket\n");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	/* etabli le numero du port du serveur */
	server.sin_port = htons(PORT1);

	/* attribution de l'adresse du serveur au socket */
	if ( ( indice_signal = bind(sk,(struct sockaddr *)&server, sizeof(server))) < 0 ) {
		perror ("bind error on  socket");
		exit(3);
	}

	long Secondes;
	long MicroSecondes,mean;
	struct timeval timeOut;
	int result_select;
	fd_set set;
	int fd;

	timeOut.tv_sec = 0;
	timeOut.tv_usec = 50000; /* 25ms 50 000*/
	struct timeval passifTimeOut;
	struct timeval currTime;
	passifTimeOut.tv_sec =0;
	passifTimeOut.tv_usec =0;
	long passifTimeCounter=WAIT_PASSIF_FUNCTION;
	struct timeval securityTimeOut;
	securityTimeOut.tv_sec =0;
	securityTimeOut.tv_usec =0;
	long securityTimeCounter=WAIT_SECURITY_FUNCTION;
	FD_ZERO(&set);
	FD_SET(sk, &set);
	fd=sk+1;

	/*****************************************
	 * boucle principale de reception des commandes
	 * ***************************************/

	while(42)
	{
		result_select=select(fd, &set, NULL, NULL, &timeOut);
		if (result_select>0)
		{
			for (i=0;i<MAXBUF;i++)
				buf[i] = '\0';
			// on attend une demande du client
			client_ln = sizeof(client);
			n_read = recvfrom(sk,buf,MAXBUF-1,0,(struct sockaddr *)&client,&client_ln);
			if(n_read < 0)
			{
				perror("Reception problem : n_read<0");
				exit(4);
			}
			sscanf(buf,"%s %s %s %s",numero,commande,separateur,param); //commande received cut
#ifdef B_TEXT
			printf("Buffer received (between #): #%s#\n",buf);
#endif
			/**All the commandes**/


      /**proprioception asked for one motor only**/
      if (strncmp(commande, "proprio_motor", 13) == 0)
			{
				if(commande[13]==commande[20])
				{
					motor_number=atoi(commande+13);
#ifdef B_TEXT
					printf("asking angular value of motor : %d \n",motor_number);
#endif

#ifdef B_KATANA
					vit_ou_pos = katana->get_position(motor_number-1);
					snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
#endif
				}
			}
			/** Uncommented function yet **/
			else if (strncmp(commande, "sensor", 6) == 0)
			{
#ifdef B_TEXT
				printf("commande sensor\n");
#endif

#ifdef B_KATANA
				int taille = 0;
				int tab[16];
				char *buffer = NULL;

				buffer = buf;

				//         tab=(int *)malloc(16*sizeof(int));
				//         if(tab == NULL){
				//             std::cout << "attention pb de malloc\n";
				//             exit(1);
				//         }

				valeur_capteur(tab);
				taille = snprintf(buffer, MAXBUF - (buffer-buf), "%s",numero);
				buffer = buffer + taille ;
				for(i=0 ; i<16 ; i++) {
					taille=snprintf(buffer, MAXBUF - (buffer-buf), " %i",tab[i]);
					buffer = buffer + taille;
				}
#endif
			}
			else if (strncmp(commande, "getSensor", 9) == 0)
			{
#ifdef B_TEXT
				printf("commande sensor_groupe\n");
#endif

#ifdef B_KATANA
				int taille = 0;
				int tab[16];
				char *buffer = NULL;

				buffer = buf;

				//         tab=(int *)malloc(16*sizeof(int));
				//         if(tab == NULL){
				//             std::cout << "attention pb de malloc\n";
				//             exit(1);
				//         }

				valeur_capteur(tab);
				taille = snprintf(buffer, MAXBUF - (buffer-buf), "%s ",numero);
				buffer = buffer + taille ;
				taille=snprintf(buffer, MAXBUF - (buffer-buf), "%i",tab[0]);
				buffer = buffer + taille;
				for(int i=1 ; i<16 ; i++)
				{
					taille=snprintf(buffer, MAXBUF - (buffer-buf), ":%i",tab[i]);
					buffer = buffer + taille;
				}
#endif

			}
			else if (strncmp(commande, "getTactileSensor", 13) == 0)
			{
#ifdef B_TEXT
				printf("commande get tactile sensor\n");
#endif

#ifdef B_KATANA
				int taille = 0;
				int tab[16];
				char *buffer = NULL;

				sscanf(buf,"%s", numero);

				snprintf(buf, sizeof(buf), "%s %i",numero, (int)(katana_arm->get_tactile_sensor()));
#endif
			}
			else if(strcmp(commande,"switchMotor")==0)
			{
				char idx_s[10];
				char activate_s[10];
				int activate, idx;
				// printf("les parametres recus sont : %s\n",param);
				sscanf(param,"motor%s",param);
				sscanf(param,"%d,%d",&idx,&activate);

#ifdef B_TEXT
				printf("switch motor : idx=%d, activate=%d\n",idx,activate);
#endif

#ifdef B_KATANA
				katana->switch_motor((idx-1),activate);
#endif
			}
			else if(strcmp(commande,"switchRobot")==0 ) /* inutilise par promethe */
			{
				int activate;
				activate = atoi(param);
#ifdef B_TEXT
				printf("switch robot : activate=%d\n",activate);
#endif

#ifdef B_KATANA
				printf("not yet implemented \n");
				// katana->switch_robot(activate); UNTESTED
#endif
			}
			/**NOUVELLE IMPLEMENTATION COMMENCE ICI**/
			else if(strcmp(commande,"pwm" )==0)
			{
				motor_number=atoi(commande+23);
				int pwm = katana->get_pwm(motor_number);
				snprintf(buf, sizeof(buf), "%s %d",numero, pwm);
			}
			else if(strcmp(commande,"stiffness" )==0)
			{
				stiffness =atoi(param);

				switch (stiffness)
				{
				case 1:
					katana->set_controller_parameters(3,1,2,1);
					katana->set_controller_parameters(2,1,2,1);
					katana->set_controller_parameters(1,1,2,1);

					std::cout << "Stiffness forte !"<< std::endl;

					//katana->switchMotorOn(0);
					break;
				case 0 :
					katana->set_controller_parameters(3,0,1,1);
					katana->set_controller_parameters(2,0,0,1);
					katana->set_controller_parameters(1,0,0,1);

					std::cout << "Stiffness faible !"<< std::endl;

					//katana->switchMotorOff(0);
					break;
				default :
					std::cout << "La stiffness doit etre 0 ou 1, 0 pour facile mais ATTENTION IL TOMBE, et 1 pour difficile"<< std::endl;
				}
			}
			else if(strcmp(commande,"get_passif_states" )==0)
			{
				snprintf(buf, sizeof(buf), "%s Passif > motor0: %d ;motor1: %d ;motor2: %d ;motor3: %d ;motor4: %d ;motor5: %d ",numero, katana->get_motor_state(0),katana->get_motor_state(1),katana->get_motor_state(2),katana->get_motor_state(3),katana->get_motor_state(4),katana->get_motor_state(5));
			}
			else if(strcmp(commande,"passif_switch" )==0)
			{
				int mode_val=-1;
				sscanf(buf,"%s passif_switch  #%d# ", numero,&mode_val);
				mode = katana->get_mode_katana();
				if(mode_val<0) {
					std::cout << "le mode etait : " << mode << std::endl;
					katana->set_passif(!mode);
				}
				else if(mode_val==0 && mode != false) {
					std::cout << "le mode passif est desactive" << std::endl;
					katana->set_passif(false);
				}
				else if(mode_val==1 && mode != true){
					std::cout << "le mode passif est active" << std::endl;
					katana->set_passif(true);
				}
			}
			else if(strcmp(commande,"Pos" )==0)
			{
				char val[6][10];
				int  numero_of_motor;
				sscanf(buf,"%s Pos motor%s  #%s# ", numero ,val[1],val[0]);

				/* On pourrait vouloir inhiber le controle en position quand le moteur est OFF */

				numero_of_motor = atoi(val[1]);
				//#ifdef B_TEXT
				std::cout<< "position control on " << numero_of_motor << " : param : " << val[0] << std::endl;
				//#endif
				katana->set_position(numero_of_motor,atoi(val[0]), false);

				snprintf(buf, sizeof(buf), "%s Pos",numero );
			}
			else if(strcmp(commande,"Vit" )==0)
			{
				int val[6] = {0,0,0,0,0,0};
				sscanf(buf,"%s Vit %d Vit %d Vit %d Vit %d Vit %d Vit %d", numero ,&(val[0]),&(val[1]),&(val[2]),&(val[3]),&(val[4]),&(val[5]) );


				for (int idx  = 0 ; idx < 6 ;idx++)
				{
#ifdef B_TEXT
					std::cout<< "controle moteur vitesse " << val[idx] << std::endl;
#endif
					controle_moteur_vitesse( idx ,val[idx],katana_arm->goal_encoders);
				}

				snprintf(buf, sizeof(buf), "%s Vit",numero );
			}
			else if(strcmp(commande,"Act" )==0)
			{
				float val[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
				sscanf(buf,"%s Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f", numero ,&(val[0]),&(val[1]),&(val[2]),&(val[3]),&(val[4]),&(val[5]),&(val[6]),&(val[7]),&(val[8]),&(val[9]),&(val[10]),&(val[11]) );

				//printf("Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f Act %f\n", (val[0]),(val[1]),(val[2]),(val[3]),(val[4]),(val[5]),(val[6]),(val[7]),(val[8]),(val[9]),(val[10]),(val[11]) );


				for (int idx  = 0 ; idx < 6 ;idx++)
				{
#ifdef B_TEXT
					std::cout<< "controle moteur " << idx << ", activation : a1 = " << val[2*idx] << ", a2 = " << val[2*idx+1] << std::endl;
#endif
					controle_moteur_activation( idx ,val[2*idx], val[2*idx+1], katana_arm->goal_encoders);
				}

				snprintf(buf, sizeof(buf), "%s Act",numero );
			}
			else if(strcmp(commande,"Proprio_groupe" )==0)
			{
				/* teste si les pos on ete rafraichies */
				bool all_refreshed = true;
				for(i=0; i<katana->get_nb_motors();i++)
				{
					all_refreshed = all_refreshed && katana->is_refreshed(i);
				}

				/* si pas rafraichies, on demande pos */
				if(! all_refreshed) {
					encod = katana->get_all_position();
				}
				snprintf(buf, sizeof(buf), "%s motor0: %d ;motor1: %d ;motor2: %d ;motor3: %d ;motor4: %d ;motor5: %d ",numero, encod[0],encod[1],encod[2],encod[3],encod[4],encod[5] );

				/* refreshed = false quand pos lue */
				for(i=0; i<katana->get_nb_motors();i++) {
					katana->set_refreshed(i,false);
				}
			}
			/*sending the command to the robot */
#ifdef B_TEXT
			std::cout<<"Send : #" << buf << "#" <<std::endl;
#endif
			n_sent = sendto(sk,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client));

			if(n_sent < 0)
			{
				perror("Probleme d'envoie de donnees");
				exit(5);
			}


			/* gestion de la securite*/
			gettimeofday(&currTime,NULL);
			securityTimeCounter = securityTimeCounter-1000000*(currTime.tv_sec-securityTimeOut.tv_sec)-(currTime.tv_usec-securityTimeOut.tv_usec);
			//      std::cout<<"1 securityTimeCounter = "<<securityTimeCounter<<std::endl;
			if(securityTimeCounter<1)
			{
				encod = katana->get_all_position();
				if(security_check(encod) == false)
				{
					for (int i=0; i<6; i++)
						katana->set_position(i, encoder_prec[i], true);
				}
				else
				{
					for (i = 0 ; i < 6 ; i++ )
						encoder_prec[i] = encod[i];
				}


				securityTimeCounter=WAIT_SECURITY_FUNCTION;
				gettimeofday(&securityTimeOut,NULL);
			}

			/* gestion du mode passif*/
			gettimeofday(&currTime,NULL);
			passifTimeCounter = passifTimeCounter-1000000*(currTime.tv_sec-passifTimeOut.tv_sec) -(currTime.tv_usec-passifTimeOut.tv_usec);
			//      std::cout<<"1 passifTimeCounter = "<<passifTimeCounter<<std::endl;
			if(passifTimeCounter<1) {
				passif_function( encod );
				passifTimeCounter=WAIT_PASSIF_FUNCTION;
				gettimeofday(&passifTimeOut,NULL);
			}

			timeOut.tv_sec = 0;
			timeOut.tv_usec = 50000; /* 25ms 50 000 ??*/
			FD_ZERO(&set);
			FD_SET(sk, &set);
			fd=sk+1;
		}
		else
		{
			/* 25ms sans commande, on est sur qu'il faut verifier la securite */
			encod = katana->get_all_position();
			if(security_check(encod) == false)
			{
				for(i=0; i<6; i++)
					katana->set_position(i, encoder_prec[i], true);
			}
			else
			{
				for (int i = 0 ; i < 6 ; i++ )
					encoder_prec[i] = encod[i];
			}

			securityTimeCounter=WAIT_SECURITY_FUNCTION; /* reset du temps a attendre pour remettre la securite a jour */
			gettimeofday(&securityTimeOut,NULL);

			/* gestion du mode passif*/
			gettimeofday(&currTime,NULL);
			passifTimeCounter = passifTimeCounter-1000000*(currTime.tv_sec-passifTimeOut.tv_sec)-(currTime.tv_usec-passifTimeOut.tv_usec);
			//      std::cout<<"2 passifTimeCounter = "<<passifTimeCounter<<std::endl;
			if(passifTimeCounter<1)
			{
				passif_function( encod );
				passifTimeCounter=WAIT_PASSIF_FUNCTION;
				gettimeofday(&passifTimeOut,NULL);
			}



			timeOut.tv_sec = 0;
			timeOut.tv_usec = 50000; /* 25ms 50 000 ??*/
			FD_ZERO(&set);
			FD_SET(sk, &set);
			fd=sk+1;
		}
	} /*fin de la boucle while*/


	return 0;
}
