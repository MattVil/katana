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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cinematique.h"

/*#define DEBUG*/

/*******************************************************************************
 * fonction d'initialisation d'une structure joint
 * ****************************************************************************/
void init_joint (Joint *j, int i, float v, float x, float y, float z){
  j->numero = i;
  j->val = v;
  j->x= x;
  j->y= y;
  j->z= z;
}


/*******************************************************************************
 * fonction de convenience pour le calcul du signe
 * ****************************************************************************/
inline int sign(int x)
{
  return ((x < 0) ? -1 : ((x > 0) ? 1 : 0) );
}


/*******************************************************************************
 * Constructeur de la classe Arm
 * ****************************************************************************/
Arm::Arm()
{
}


/*******************************************************************************
 * Constructeur de la classe Arm
 * ****************************************************************************/
Arm::Arm(mxml_node_t *tree)
{
  float val_segments[NB_SEGMENTS] = {SEG0,SEG1,SEG2,SEG3};
  float val_operating_ranges[NB_OPERATING_RANGES] = {OR0,OR1,OR2,OR3,OR4};
  float val_offsets[NB_JOINTS]={OFFSET0,OFFSET1,OFFSET2,OFFSET3,OFFSET4};
  int encoder_max_temp[NB_JOINTS] = {ENMAX0,ENMAX1,ENMAX2,ENMAX3,ENMAX4};
  int encoder_min_temp[NB_JOINTS] = {ENMIN0,ENMIN1,ENMIN2,ENMIN3,ENMIN4};
  int i =0;
  mxml_node_t *node=NULL;
  char *p=NULL;
  Cylindre cylindre;
  float x, y, z, r, h;
  std::vector<Cylindre>::iterator it;
  
  
  for (i=0; i< NB_JOINTS;i++)
  {
    init_joint(&(joint[i]), i, 0.0, 0.0, 0.0, 0.0);
    offsets[i] = val_offsets[i];
    encoder_max[i]= encoder_max_temp[i];
    encoder_min[i]= encoder_min_temp[i];
  }

  for (i=0; i< NB_SEGMENTS;i++)
  {
    segments[i] = val_segments[i];
  }

  for (i=0; i< NB_OPERATING_RANGES;i++)
    op_ranges[i] = (val_operating_ranges[i]*PI)/180.0;


  goal_encoders = new int[6];

  for (i = 0; i < 6 ; i++)
  {
    goal_encoders[i]=encoder_max[i]-encoder_min[i];
  }

  calculVmax();

/* ouverture des fichiers pour l'enregistrement des coordonnees */
  jointPos = fopen("jointPos.SAVE", "w");
  if (jointPos == NULL)
  {
    fprintf(stderr, "ERROR : Impossible to create file jointPos.SAVE\n");
    exit(1);
  }
  cartesianPos = fopen("cartesianPos.SAVE", "w");
  if (cartesianPos == NULL)
  {
    fprintf(stderr, "ERROR : Impossible to create file cartesianPos.SAVE\n");
    exit(1);
  }
  /* enregistrement du temps */
  time_f = fopen("time.SAVE", "w");
  if (time_f == NULL)
  {
    fprintf(stderr, "ERROR : Impossible to create file time.SAVE\n");
    exit(1);
  }
  
  /** Loading of the joints properties */
  for(i=0, node = mxmlFindElement(tree, tree, "joint", NULL, NULL, MXML_DESCEND); i<NB_JOINTS && node != NULL; i++, node = mxmlFindElement(node, tree, "joint", NULL, NULL, MXML_NO_DESCEND))
  {
    p=(char*)mxmlElementGetAttr(node, "enc_min");
    if(p == NULL)
    {
      std::cout << "error, unable to find enc_min attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%i", &(encoder_min[i])) != 1)
    {
      std::cout << "error, unable to read enc_min attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    p=(char*)mxmlElementGetAttr(node, "enc_max");
    if(p == NULL)
    {
      std::cout << "error, unable to find enc_max attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%i", &(encoder_max[i])) != 1)
    {
      std::cout << "error, unable to read enc_max attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    p=(char*)mxmlElementGetAttr(node, "angle_offset");
    if(p == NULL)
    {
      std::cout << "error, unable to find angle_offset attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%f", &(offsets[i])) != 1)
    {
      std::cout << "error, unable to read angle_offset attribute of joint" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::cout << "new joint created: enc_min=" << encoder_min[i] << ", enc_max=" << encoder_max[i] << ", offset=" << offsets[i] << std::endl;
  }
  /** Loading of the segments properties */
  for(i=0, node = mxmlFindElement(tree, tree, "segment", NULL, NULL, MXML_DESCEND); i < NB_SEGMENTS && node != NULL; i++, node = mxmlFindElement(node, tree, "segment", NULL, NULL, MXML_NO_DESCEND))
  {
    p=(char*)mxmlElementGetAttr(node, "length");
    if(p == NULL)
    {
      std::cout << "error, unable to find length attribute of segment" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%f", &(segments[i])) != 1)
    {
      std::cout << "error, unable to read length attribute of segment" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::cout << "new segment created: length=" << segments[i] << std::endl;
  }
  /** Loading of the hard security cylindres properties */
  for(node = mxmlFindElement(tree, tree, "cylindre", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, tree, "cylindre", NULL, NULL, MXML_NO_DESCEND))
  {
    p=(char*)mxmlElementGetAttr(node, "name");
    if(p == NULL)
    {
      std::cout << "error, unable to find name attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    cylindre.set_name(p);
    p=(char*)mxmlElementGetAttr(node, "bottom_center");
    if(p == NULL)
    {
      std::cout << "error, unable to find bottom_center attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "(%f,%f,%f)", &x, &y, &z) != 3)
    {
      std::cout << "error, unable to read bottom_center attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    p=(char*)mxmlElementGetAttr(node, "hight");
    if(p == NULL)
    {
      std::cout << "error, unable to find hight attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%f", &h) != 1)
    {
      std::cout << "error, unable to read hight attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    p=(char*)mxmlElementGetAttr(node, "radius");
    if(p == NULL)
    {
      std::cout << "error, unable to find radius attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(sscanf(p, "%f", &r) != 1)
    {
      std::cout << "error, unable to read radius attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    p=(char*)mxmlElementGetAttr(node, "type");
    if(p == NULL)
    {
      std::cout << "error, unable to find type attribute of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }
    cylindre.set_params(x, y, z, r, h);
    if(strncmp(p, "hard", 4*sizeof(char)) == 0)
    {
      tab_cylindres.push_back (cylindre);
    }
    else if(strncmp(p, "soft", 4*sizeof(char)) == 0)
    {
      cylindres_soft_security.push_back (cylindre);
    }
    else
    {
      std::cout << "error, unknown type '" << p << "' of cylindre" << std::endl;
      exit(EXIT_FAILURE);
    }    
  }
  for (it=tab_cylindres.begin(); it < tab_cylindres.end(); it++ )
  {
    std::cout << "new hard cylindre created ";
    it->display();
  }
  for (it=cylindres_soft_security.begin(); it < cylindres_soft_security.end(); it++ )
  {
    std::cout << "new soft cylindre created ";
    it->display();
  }
}


/*******************************************************************************
 * fonction de conversion Encoder Position 0 et 1
 * ****************************************************************************/
inline float Arm::myEncToCursor(int encoder,int encoder_min, int encoder_max)
{
  float cursor = (float)(encoder-encoder_min)/(float)(encoder_max-encoder_min);
  return cursor;
}


/*******************************************************************************
 * ****************************************************************************/
void Arm::add_cylinder(float x, float y, float z, float r, float h)
{
  Cylindre cylindre;
  cylindre.set_params(x, y, z, r, h);
  tab_cylindres.push_back (cylindre);
}


/*******************************************************************************
 * destructeur
 * ****************************************************************************/
Arm::~Arm()
{
  printf("bug hunting ~Arm dans cinematique.cpp\n");
  close_files();
  delete[] goal_encoders;
}



/*******************************************************************************
 * *****************************************************************************
 * Methodes publiques
 * *****************************************************************************
 * ****************************************************************************/


/*******************************************************************************
 * Ecriture valeurs dans fichiers pour debug
 * ****************************************************************************/
void Arm::print_to_files(std::vector<int> curr_encoders) {

  if (jointPos != NULL)
  {
    for (int idx_of_joint = 0 ; idx_of_joint< 4 ; idx_of_joint++) {
      fprintf(jointPos,"%d ",curr_encoders[idx_of_joint]);
    }
    fprintf(jointPos,"\n");
  }
   
   if (cartesianPos != NULL)
   {
     fprintf(cartesianPos,"%f ",joint[3].x);
     fprintf(cartesianPos,"%f ",joint[3].y);
     fprintf(cartesianPos,"%f ",joint[3].z);
     fprintf(cartesianPos,"%f ",joint[4].x);
     fprintf(cartesianPos,"%f ",joint[4].y);
     fprintf(cartesianPos,"%f ",joint[4].z);
     fprintf(cartesianPos,"\n");
   }
   if (time_f != NULL)
   {
     gettimeofday(&time,NULL);
     fprintf(time_f,"%f\n",(double)(time.tv_sec) + ((double)(time.tv_usec))/1000000);
   }
   
}


/*******************************************************************************
 * Fermeture des fichiers pour la sauvegarde des donnees
 * ****************************************************************************/
void Arm::close_files() {
  if (jointPos != NULL)
  {
    fclose(jointPos);
    jointPos = NULL;
  }
  printf("bug hunting close_files dans cinematique.cpp\n");
  if (cartesianPos != NULL)
  {
    fclose(cartesianPos);
    cartesianPos = NULL;
  }
  if (time_f != NULL)
  {
    fclose(time_f);
    time_f = NULL;
  }
}


/*******************************************************************************
 * Mise a jour des coordonnees des articulations de Arm a partir de curr_encoders (ARGS)
 * ****************************************************************************/
void Arm::compute_3Dcoordinates(std::vector<int> curr_encoders) {
  float new_consigne[4];
  //~ std::cout<<"Les nouvelles consignes sont : ";
  for (int idx_of_joint = 0 ; idx_of_joint< 4 ; idx_of_joint++) {
    new_consigne[idx_of_joint] = myEncToCursor(curr_encoders[idx_of_joint], encoder_min[idx_of_joint], encoder_max[idx_of_joint]);
    //~ std::cout<<new_consigne[idx_of_joint]<<" ";
  }
  //~ std::cout<<std::endl;
  set_arm_position(new_consigne[0], new_consigne[1], new_consigne[2], new_consigne[3]);
}


/*******************************************************************************
 * Recuperation des coordonnees cartesiennes de joint <idx_of_joint> (ARGS)
 * Les valeurs sont donnees dans l'ARG pos3D.
 * ****************************************************************************/
void Arm::get_3Dpos_of_joint(int idx_of_joint, float pos3D[3]) {
  if(idx_of_joint<NB_JOINTS) {
    pos3D[0]=joint[idx_of_joint].x;
    pos3D[1]=joint[idx_of_joint].y;
    pos3D[2]=joint[idx_of_joint].z;
  }
  else
    std::cerr<<"Idx of joint est superieur au nombre de joints dans get_3Dpos"<<std::endl;
}


/*
* Recuperation des coordonnees cartesiennes de joint <idx_of_joint> (ARGS)
* Les valeurs sont donnees dans l'ARG pos3D.
*/
float Arm::get_arm_length()
{
	float length = 0.;
	for (int i=0; i< NB_SEGMENTS;i++)
	{
		length += segments[i];
	}
  return length;
}



bool Arm::get_tactile_sensor()
{
  bool pain=false;
  float joint_x_mid, joint_y_mid, joint_z_mid;
  std::vector<Cylindre>::iterator cylindre;
  int i, j;

  for (int i = 1;i<NB_JOINTS; i++)
  {
    //~ std::cout << " (" << joint[i].x << "," << joint[i].y << "," << joint[i].z << ")" << std::endl;
    joint_x_mid = (joint[i-1].x + joint[i].x)/2;
    joint_y_mid = (joint[i-1].y + joint[i].y)/2;
    joint_z_mid = (joint[i-1].z + joint[i].z)/2;
    /* verification de la position par rapport aux cylindres appris */
    for (j=0, cylindre=cylindres_soft_security.begin(); cylindre < cylindres_soft_security.end(); j++, cylindre++)
    {
      if(cylindre->estDansCylindre(joint[i].x, joint[i].y, joint[i].z))
      {
        std::cout << "joint " << i << " (" << joint[i].x << "," << joint[i].y << "," << joint[i].z << ") is inside cylinder " << cylindre->get_name() <<std::endl;
        pain=true;
      }
      if(i != 1 && cylindre->estDansCylindre(joint_x_mid, joint_y_mid, joint_z_mid))
      {
        std::cout << "middle of " << i-1 << "-" << i << " (" << joint_x_mid << "," << joint_y_mid << "," << joint_z_mid << ") is inside cylinder " << cylindre->get_name() <<std::endl;
        pain=true;
      }
    }
  }
  
  return pain;
}


/*******************************************************************************
 * *****************************************************************************
 * Methodes privees
 * *****************************************************************************
 * ****************************************************************************/


/*******************************************************************************
 * modele direct : les coordonées (x,y,z)  de chaque joint (pointé par curr)
 * sont calculées en fonction des coordonées du joint precedent
 * (pointé par prev), de la somme des angles des degrés de libertés  précédents
 * (sum) et de la longueur du segment entre prev et curr (stoqué dans
 * a->segments[prev->numero]
 * ****************************************************************************/
void Arm::calc_pos_joint(Joint *curr,Joint *prev){

  float sum = 0.0;

  /* on somme les valeurs des angles en RADIANS*/
  for (int i=1;i<curr->numero;i++)
    sum += angles[i];

  if (curr->numero != 1)
  {
    curr->x = prev->x + segments[prev->numero] * cos((double)sum )*cos((double)(-angles[0]));
    curr->y = prev->y + segments[prev->numero] * cos((double)sum )*sin((double)(-angles[0]));
    curr->z = prev->z + segments[prev->numero] * sin((double)sum);
  }
  else
  {
    curr->x = prev->x;
    curr->y = prev->y;
    curr->z = prev->z+segments[0];
  }
}


/*******************************************************************************
 *calcule  la position des 4 articulations du bras pos0,1,2,3 sont des valeurs 
 * comprises entre [0,1]
 * ****************************************************************************/
void Arm::set_arm_position(float pos0, float pos1, float pos2, float pos3)
{
  joint[0].val = pos0;
  joint[1].val = pos1;
  joint[2].val = pos2;
  joint[3].val = pos3;

/* les angles sont exprimes en radians pour op_ranges MAIS en degres pour offsets...*/
  for(int i=0;i<NB_JOINTS;i++)
  {
    angles[i]  = joint[i].val * op_ranges[i] ;/* mise en correspondance de la consigne (val) et d l'angle de chaque articulation correspondant*/
    angles[i] = angles[i]+((offsets[i]*PI/180.0));   /* on rajoute l'offset en radiants*/
//        std::cout<<"angle["<<i<<"] est "<<angles[i]<<std::endl;
  }
  for (int i=1; i< NB_JOINTS;i++){
    calc_pos_joint(&(joint[i]),&(joint[i-1]));
    //~ std::cout << "(" << joint[i].x << "," << joint[i].y << "," << joint[i].z << ")" << std::endl;
  }
}


/*******************************************************************************
 * fonction de calcul de la vitesse a prendre en compte pour la prediction
 * ****************************************************************************/
void Arm::calculVmax()
{
  for (int i = 0; i<6 ; i++)
  {
    Vmax[i]=10000.;
  }
}


/*******************************************************************************
 * verif_cylinders : test securite lie aux cylindres definis dans secu.conf
 * param :   int idx_of_joint  : index de l'articulation a tester
 * return :  true si le test est valide
 *            false si l'articulation est dans l'un des cylindres
 * ****************************************************************************/
bool Arm::verif_cylinders_debug(int idx_of_joint)
{  
  std::vector<Cylindre>::iterator cylindre;
  int i;
  
  std::cout << "x:" << joint[idx_of_joint].x << ", y:" << joint[idx_of_joint].y << ", z:" << joint[idx_of_joint].z << std::endl;
  for (i=0, cylindre=tab_cylindres.begin(); cylindre < tab_cylindres.end(); i++, cylindre++)
  {
    if(cylindre->estDansCylindreDebug(joint[idx_of_joint].x, joint[idx_of_joint].y, joint[idx_of_joint].z))
    {
      std::cout << "Stopped because joint " << idx_of_joint << " is inside cylinder " << cylindre->get_name() <<std::endl;
      return false;
    }
  }
    
  return true;
}


/*******************************************************************************
 * fonction effectuant les differents tests voulus 
 * ****************************************************************************/
bool Arm::verif()
{
  float joint_x_mid, joint_y_mid, joint_z_mid;
  std::vector<Cylindre>::iterator cylindre;
  int i, j;

  for (int i = 1;i<NB_JOINTS; i++)
  {
    //~ std::cout << " (" << joint[i].x << "," << joint[i].y << "," << joint[i].z << ")" << std::endl;
    joint_x_mid = (joint[i-1].x + joint[i].x)/2;
    joint_y_mid = (joint[i-1].y + joint[i].y)/2;
    joint_z_mid = (joint[i-1].z + joint[i].z)/2;
    /* verification de la position par rapport aux cylindres appris */
    for (j=0, cylindre=tab_cylindres.begin(); cylindre < tab_cylindres.end(); j++, cylindre++)
    {
      if(cylindre->estDansCylindre(joint[i].x, joint[i].y, joint[i].z))
      {
        std::cout << "Stopped because joint " << i << " (" << joint[i].x << "," << joint[i].y << "," << joint[i].z << ") is inside cylinder " << cylindre->get_name() <<std::endl;
        return false;
      }
      if(cylindre->estDansCylindre(joint_x_mid, joint_y_mid, joint_z_mid))
      {
        std::cout << "Stopped because middle of " << i-1 << "-" << i << " (" << joint_x_mid << "," << joint_y_mid << "," << joint_z_mid << ") is inside cylinder " << cylindre->get_name() <<std::endl;
        return false;
      }
    }
  }
  
  return true;
}


/*******************************************************************************
 * La fonction de verification
 * ****************************************************************************/
bool Arm::verification(std::vector<int> curr_encoders, bool no_verif)
{
  float tau_predictif;
  float new_consigne[4];
  float tau_max = FREQ_SECURITY;
  float V_max=-1.;

  for(int i=0; i<4; i++) {
    //      printf("Vmax [%d] : %f \n",i, Vmax[i]);
    if(Vmax[i]>V_max)
      V_max = Vmax[i];
  }
  float signe;
  int tolerance = 10;
    
  float tau_predictif_incr = ENCODER_PREDICT / V_max; /* pas d'echantillonage en encodeur constant */
  int new_pos = 0;
  bool test =true;
    
#ifdef DEBUG
  printf("DEBUG : Arm::verification : V_max = %f, tau_predict_incr %f (/%f), nb_ech %d\n",V_max, tau_predictif_incr, tau_max, (int)(tau_max/tau_predictif_incr)); 
#endif


  /*** update cinematics ***/

  for (int idx_of_joint = 0 ; idx_of_joint< 4 ; idx_of_joint++) {
    new_consigne[idx_of_joint] = myEncToCursor(curr_encoders[idx_of_joint], encoder_min[idx_of_joint], encoder_max[idx_of_joint]);
  }
  set_arm_position(new_consigne[0], new_consigne[1], new_consigne[2], new_consigne[3]);

  /* enregistrement des valeurs */
  print_to_files(curr_encoders);

  if(!no_verif) { /* check security */
      
    for(tau_predictif=tau_predictif_incr; tau_predictif<tau_max; tau_predictif = tau_predictif + tau_predictif_incr) 
    {
      for (int idx_of_joint = 0 ; idx_of_joint< 4 ; idx_of_joint++)
      {
	      
	//printf("goal actuel sur %d : %d\n",idx_of_joint,(int)this->goal_encoders[idx_of_joint]);	    
	//printf("curr encod sur %d : %d\n",idx_of_joint,(int)curr_encoders[idx_of_joint]);
	      
	/* test pour ne pas prendre le bruit pour du mouvement */
	if(abs(this->goal_encoders[idx_of_joint]-curr_encoders[idx_of_joint]) < tolerance)
	{
	  signe=0.;
	}
	else 
	{
	  if(this->goal_encoders[idx_of_joint]>curr_encoders[idx_of_joint]) 
	  {
	    signe = 1.;
	  }
	  else
	    signe = -1.;
	}
	//	      signe = sign(this->goal_encoders[idx_of_joint]-curr_encoders[idx_of_joint]);
	      
	//printf("Vmax : %f , tau predictif %f, difference : %d, signe %f \n",Vmax[idx_of_joint],tau_predictif,(this->goal_encoders[idx_of_joint]-curr_encoders[idx_of_joint]), signe);
	      
	      
	new_pos = curr_encoders[idx_of_joint]+(int)(Vmax[idx_of_joint]*tau_predictif*signe);
	      
	//	    printf("nouvelle position %d ancienne position %d\n",new_pos,curr_encoders[idx_of_joint]);
	      
	new_consigne[idx_of_joint] = myEncToCursor(new_pos, encoder_min[idx_of_joint], encoder_max[idx_of_joint]);
	      
	//printf("nouvelle consigne %d \n",new_consigne[idx_of_joint]);
	      
      }
      set_arm_position(new_consigne[0], new_consigne[1], new_consigne[2], new_consigne[3]);
	  
      test = verif() && test;
    }
  }    
  return test;
}
