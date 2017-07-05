/*
Copyright  ETIS ¿ ENSEA, Université de Cergy-Pontoise, CNRS (1991-2014)
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

#ifndef CINEMATIQUE_H
#define CINEMATIQUE_H

#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include "cylindre.h"
//#include <mxml.h>

/*Angle value for offsetting back*/
#define ANGULAR_OFFSET -0.36 /*1/pi radians*/


/*Prediction encoder*/
#define ENCODER_PREDICT 50. /* min encoder to determine security sampling*/
#define FREQ_SECURITY 0.040 /* frequency of security check */


/*Arm values*/
#define NB_JOINTS 5
#define NB_OFFSETS 4
#define NB_OPERATING_RANGES 5
#define NB_SEGMENTS 4

/********************************************************/
/*   DEFINITION OF CINEMATICS ACCORDING TO TYPE OF ARM  */
/********************************************************/



/*modification des valeurs pour webots

/**range of motors**/
#define OR0 360
#define OR1 -139.48
#define OR2 253.95  // webots vs reel : 148.14 vs 253.95
#define OR3 230.48
#define OR4 332.2 //operating range of rotation of wrist gripper,
		  //useless here
/**Offset of the angles, in degrees**/
#define OFFSET0 -0.36 /* correction offset*/
#define OFFSET1 124.23 /* correction offset*/
#define OFFSET2 -122.88  /* correction offset*/
#define OFFSET3 -121.02
#define OFFSET4   8.5

/*fin modif*/

/**size of the robot arm**/
#define SEG0 .317           /* longueur en m entre le socle et le moteur 1*/
#define SEG1 .190           /* entre le moteur 1 et le moteur 2 : UA dans la doc Katana*/
#define SEG2 .139           /* entre le moteur 2 et le moteur 3 : FA*/
#define SEG3 .315       /* entre le moteur 3 et le moteur 4  + entre le moteur 4 et l'extremite de la pince : WR + GR*/

/**Max and min encoders for different motors **/
#define ENMAX0 31000
#define ENMAX1 5800
#define ENMAX2 2500
#define ENMAX3 31000
#define ENMAX4 30000
#define ENMAX5 30000

#define ENMIN0 -15000
#define ENMIN1 -31000
#define ENMIN2 -31000
#define ENMIN3 -1780
#define ENMIN4 -18000
#define ENMIN5 9000

/*
#define ENMAX0 30000 
#define ENMAX1 5100 
#define ENMAX2 1970 
#define ENMAX3 31000 
#define ENMAX4 31000 
#define ENMAX5 30770 


/* Configuration pour la securite */
#define hauteur_dos		1.1
#define avant_robulab 		-0.13
#define arriere_robulab 	1.0 /*0.11; cylindre mieux (cf secu.conf)*/
#define largeur_robulab 	0.0 /* 0.24; cylindre mieux (cf secu.conf)*/ 
#define hauteur_robulab 	0.  /*0. si utilisation avec table
				     *0.3 si utilisation robulab */
#define marge			0.06
#define marge_socle  		0.15  
#define hauteur_socle 		0.405


#define PI 3.14159265358979323846

#define SECURITE_FILE   "secu.conf"
#define NB_CYL          10


typedef struct Joint{
	int numero;
	float val;  /*valeur de la rotation appartenant à [0.0,1.0]*/
	float speed;
	float x;
	float y;
	float z;
} Joint;


void init_joint (Joint *j, int nb, float v, float x, float y, float z);

class Arm
{
public :
	int *goal_encoders;

	Arm();
	//Arm(mxml_node_t *tree);
	~Arm();
	void add_cylinder(float x, float y, float z, float r, float h);
	void close_files();
	void compute_3Dcoordinates(std::vector<int> curr_encoders);
	void get_3Dpos_of_joint(int idx_of_joint, float pos3D[3]);
	float get_arm_length();
	bool get_tactile_sensor();
	bool verif_cylinders_debug(int idx_of_joint);
	bool verification(std::vector<int>, bool no_verif);
	bool verif_w_robulab();
	void save_security();


private :
	std::vector<Cylindre> tab_cylindres;
	std::vector<Cylindre> cylindres_soft_security;
	Joint joint[NB_JOINTS];
	float offsets[NB_JOINTS];
	int encoder_max[6];
	int encoder_min[6];
	float segments[NB_SEGMENTS];
	float op_ranges[NB_OPERATING_RANGES];
	float angles[NB_JOINTS];
	float new_consigne[NB_JOINTS];
	float Vmax[6];
	FILE *jointPos;
	FILE *cartesianPos;
	FILE *time_f;
	struct timeval time;

    void calculVmax();
    float myEncToCursor(int,int, int );
    bool verif();
    void set_arm_position(float , float , float , float);
    void calc_pos_joint(Joint *,Joint *);
    void print_to_files(std::vector<int>);
};

#endif
