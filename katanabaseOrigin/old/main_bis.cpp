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
#include "kniBase.h"
#include "keyboard.h"
#include "main.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>

#include <sys/time.h>
#include <signal.h>

#include <getopt.h>
#include <ivy.h>
#include <ivyloop.h>
#include "ivy_bus.h"

#define	PORT	5566
#define	ADDR	"192.168.168.232"
#define MAXBUF 1024
#define PORT1 1115
int pos_min[6]={-12000,-20000,-26000,7000,-16600,12000};      /*position min que peuvent atteindre les butees*/
int pos_max[6]={30000,-10000,1000,19000,30000,30000};         /*position max que peuvent atteindre les butees*/
int current_target[6] = {0,0,0,0,0,0};
struct sigaction act;                                         /*gestion des signaux*/
CLMBase *katana;                                              /*il faudra le transformer en structure*/
using namespace std;


/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/***********************                             Fonction de parametrage du Bras                                 **************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/***********************                                                                                             **************************************/
/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/
/**********************************************************************************************************************************************************/





const TMotSCP	                *mygetscp(/*CLMBase *katana, */int idx)
{
  const TMotSCP			*myscp = NULL;
  
  katana->GetBase()->GetMOT()->arr[idx].recvSCP();
  myscp = katana->GetBase()->GetMOT()->arr[idx].GetSCP();
  
  return myscp;
}




/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******       fonction qui affiche certains parametres       *******/
/*******                    position                          *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void				readpid_pos(/*CLMBase *katana*/)
{
  int				idx = 0;
  const TMotSCP			*myscp = NULL;

  for (idx = 0; idx < katana->getNumberOfMotors(); idx++)
    {
      myscp = mygetscp(/*katana ,*/ idx);
      cout << "[moteur " << idx << "] P " << (int)myscp->kP << " - I = " << (int)myscp->kI << " - D = " << (int)myscp->kD 
	   << " -voltage" << (int)myscp->maxppwm <<" -pourcentage" << (int)myscp->maxppwm_nmp<< "\n";
      
    }
}


/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******       fonction qui affiche certains parametres       *******/
/*******                     vitesse                          *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/



void				readpid_spd(/*CLMBase *katana*/)
{
  int				idx = 0;
  const TMotSCP			*myscp = NULL;

  for (idx = 0; idx < katana->getNumberOfMotors(); idx++)
    {
      myscp = mygetscp(/*katana,*/ idx);
      cout << "[moteur " << idx << "] P " << (int)myscp->kP_speed << " - I = " << (int)myscp->kI_speed << " - D = " << (int)myscp->kD_speed << "\n";
    }
}



/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******       fonction qui recupere certains parametres      *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/



const TMotPVP			*mygetpvp(/*CLMBase *katana,*/ int idx)
{
  const TMotPVP			*mypvp = NULL;

  katana->GetBase()->GetMOT()->arr[idx].recvPVP();
  mypvp = katana->GetBase()->GetMOT()->arr[idx].GetPVP();

  return mypvp;
}



/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******       fonction qui affiche certains parametres       *******/
/*******                  position et vitesse                 *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void				readpvp(/*CLMBase *katana*/)
{
  int				idx = 0;
  const TMotPVP			*mypvp = NULL;

  for (idx = 0; idx < katana->getNumberOfMotors(); idx++)
    {
      mypvp = mygetpvp(/*katana,*/ idx);
      cout << "[moteur " << idx << "] position = " << mypvp->pos << " - vitesse = " << mypvp->vel << " - pwm cycle = " << (int)mypvp->pwm << "\n";
    }
}




/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******            retourne a la position initiale           *******/
/*******         je n ai jamais tester cette fonction         *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void				goinitialposition(/*CLMBase *katana*/)
{
  int				idx = 0;

  for (idx = 0; idx < katana->getNumberOfMotors(); idx++)
    {
      cout << "return to initial position " << katana->GetBase()->GetMOT()->arr[idx].GetCLB()->encoderPositionAfter << "\n";
      katana->moveMotorToEnc(idx, katana->GetBase()->GetMOT()->arr[idx].GetCLB()->encoderPositionAfter, true);
    }
}






/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******            fonction qui nous enseigne sur            *******/
/*******          la valeur Min et max des encodeurs          *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/



void positionMinMaxEncodeur(/*CLMBase *katana*/)
{

  int				min = 0;
  int				max = 0;
  int                           idx=0;

  for(idx=0 ; idx< katana->getNumberOfMotors() ; idx++)
    {
      min = pos_min[idx]; //katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos();
      max = pos_max[idx]; //katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos();

      cout << "moteur[" << idx <<"]" "encoder min = " << min << "\tencoder max = " << max << "\n";
    }
}







/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******                   fonction jamais tester             *******/
/*******           doit surement faire un aller retour        *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void				pingpong(/*CLMBase *katana,*/ int idx, int sens)
{
  int				min = 0;
  int				max = 0;
  int				prev_sens = 0;
  const TMotPVP			*mypvp = NULL;
  int				sign_vel = 0;
  int				pos_target = 0;

  min = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos() + 1000;
  max = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos() - 1000;

  cout << "encoder min = " << min << "\tencoder max = " << max << "\n";

  pos_target = min;
  prev_sens = max;
  sign_vel = 1;
  cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
  katana->moveMotorToEnc(idx, pos_target, false);
  
  while (42)
    {
      int	input;

      input = _getch();
      switch(input)
	{
	case 'q' :
	  {
	    return ;
	  }
	  break;
	default :
	  break;
	}

      mypvp = mygetpvp(/*katana,*/ idx);

      if (((mypvp->vel > 0) && (sign_vel < 0)) || ((mypvp->vel < 0) && (sign_vel > 0)) || (mypvp->vel == 0))
	{
	  if (prev_sens == min)
	    {
	      pos_target = max;
	      prev_sens = max;
	      sign_vel = -1;
	    }
	  else if (prev_sens == max)
	    {
	      pos_target = min;
	      prev_sens = min;
	      sign_vel = 1;
	    }

	  if (pos_target < min)
	    pos_target = min;
	  else if (pos_target > max)
	    pos_target = max;

	  cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
	  katana->moveMotorToEnc(idx, pos_target, false);
	  usleep(100000);
	}
      
    }  
}





/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******              fonction qui fait bouger un             *******/
/*******                       moteur                         *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void				gomovemotor(/*CLMBase *katana,*/ int idx, int step, int sens)
{
  int				i = 0;
  int				pos_target = 0;
  char				m = '\0';
  int				min = 0;
  int				max = 0;
  const TKatMOT			*motor;
  ofstream			pwmfile;
  ofstream			posfile;

  min = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos() + 1000;
  max = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos() - 1000;

  /********** probleme avec le le moteur 0 ************/
  /**********  il ne vas pas jusqu a la buter min  ****/

  if(idx == 0)
    min=-14000;

  pwmfile.open("pwm.txt");
  posfile.open("pos.txt");

  while (42)
    {
      m = '\0';
      cout << "\n"
	"4 - aller a gauche\n"
	"6 - aller a droite\n"
	"+ - augmenter le step de 50\n"
	"- - diminuer le step de 50\n"
	"p - afficher les position min et max\n"
	"q - revenir au menu principal\n";
      cin >> m;
      switch (m)
	{
	case '-' :
	  {
	    step -= 50;
	    if (step < 100)
	      step = 100;
	    cout << "le step est de " << step << "\n";
	  }
	  break;
	case '+' :
	  {
	    step += 50;
	    if (step > 3000)
	      step = 3000;
	    cout << "le step est de " << step << "\n";
	  }
	  break;
	case '4' : 
	  {
	    int i;

	    pos_target = katana->getMotorEncoders(idx, true) + (step * sens);
	    cout <<"position initial="<< katana->getMotorEncoders(idx, true) << " pos_target=" << pos_target  <<"\n";
	    if (pos_target < pos_min[idx])
	      pos_target = pos_min[idx];
	    else if (pos_target > pos_max[idx])
	      pos_target = pos_max[idx];
	    cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
	    katana->moveMotorToEnc(idx, pos_target, false);
	    prise_objet(/*katana*/);
	    /*for (i = 0; i < 30; i++)
	      {
	      const TMotPVP			*mypvp = NULL;
	      
	      mypvp = mygetpvp(katana, idx);
	      cout << "[moteur " << idx << "] position = " << mypvp->pos << " - vitesse = " << mypvp->vel << " - pwm cycle = " << (int)mypvp->pwm << "\n";
	      }*/
	  }
	  break;
	case '6' :
	  {
	    int i;

	    pos_target = katana->getMotorEncoders(idx, true) - (step * sens);
	    if (pos_target < pos_min[idx])
	      pos_target = pos_min[idx];
	    else if (pos_target > pos_max[idx])
	      pos_target = pos_max[idx];
	    cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
	    katana->moveMotorToEnc(idx, pos_target, false);
	    prise_objet(/*katana*/);
	    /*for (i = 0; i < 30; i++)
	      {
	      const TMotPVP			*mypvp = NULL;
	      
	      mypvp = mygetpvp(katana, idx);
	      cout << "[moteur " << idx << "] position = " << mypvp->pos << " - vitesse = " << mypvp->vel << " - pwm cycle = " << (int)mypvp->pwm << "\n";
	      }*/
	  }
	  break;
	case 'p' :
	  {
	    cout << "Position min = " << min << " - Position max = " << max << "\n";
	  }
	  break;
	case 'q' :
	  {
	    pwmfile.close();
	    posfile.close();
	    return;
	  }
	  break;
	default :
	  {
	    cerr << "commande inconnue\n";
	  }
	  break;
	}
    }
}





/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******              fonction qui lit la vitesse             *******/
/*******            a laquelle doit aller les moteurs         *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void read_vitesse(/*CLMBase *katana*/)
{

  short velocity;
  int motorNumber;
  cout << "entree dans la fonction controle_moteur4_vitesse \n";
  for(short motorNumber = 0; motorNumber < katana->getNumberOfMotors(); ++motorNumber) {
    velocity=katana->getMotorVelocityLimit(motorNumber);
    cout << "[moteur " << motorNumber << "]" << " - vitesse = " << velocity <<"\n";
  }
  cout << "sortie de la fonction controle_moteur4_vitesse \n";
}


/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******             fonction qui lit les encodeurs           *******/
/*******            a laquelle doit aller les moteurs         *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/


void read_encodeur(/*CLMBase *katana*/)
{

  short encodeur;
  int motorNumber;
  cout << "entree dans la fonction read_encodeur \n";
  for(short motorNumber = 0; motorNumber < katana->getNumberOfMotors(); ++motorNumber) {
    encodeur= katana->getMotorEncoders(motorNumber, true);
    cout << "[moteur " << motorNumber << "]" << " - position = " << encodeur <<"\n";
  }
  cout << "sortie de la fonction read_encodeur \n";
}


/********************************************************************/
/********************************************************************/
/*******                                                      *******/
/*******                                                      *******/
/*******              fonction qui ecrit la vitesse           *******/
/*******            a laquelle doit aller les moteurs         *******/
/*******          rajout d une securite on ne peut pas        *******/
/*******               aller a une vitesse > 100              *******/
/*******                                                      *******/
/********************************************************************/
/********************************************************************/

void write_vitesse_all_encoder(/*CLMBase *katana,*/ int velocity)
{
  
  int idx=0;  
  if(velocity > 100)
    {
      /*si la vitesse > seuil pourra etre dangereux*/
      /*ici arbitrairement on a mis 100*/
    }
  else
    {
      for(idx=0 ; idx < katana->getNumberOfMotors() ; idx++)
	katana->setMotorVelocityLimit(idx, velocity);
    }
  
}


void controle_moteur_vitesse_buter_min(/*CLMBase *katana,*/ int idx,int velocity)
{

  int				i = 0;
  int				pos_target = 0;
  char				m = '\0';
  int				min = 0;
  int				max = 0;
  const TKatMOT			*motor;
  
  
  min = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos() + 1000;
  max = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos() - 1000;

  /*on met la vitesse de ce moteur a velocity*/
  katana->setMotorVelocityLimit(idx, velocity);
  
  if(idx == 0)
    min=-14000;

  /*position d arriver*/
  pos_target = min;
  //cout <<"position initial="<< katana->getMotorEncoders(idx, true) << " pos_target=" << pos_target  <<"\n";
  if (pos_target < min)
    pos_target = min;
  else if (pos_target > max)
    pos_target = max;
  //cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
  katana->moveMotorToEnc(idx, pos_target, false);

}

void controle_moteur_vitesse_buter_max(/*CLMBase *katana,*/ int idx, int velocity)
{
  int				i = 0;
  int				pos_target = 0;
  char				m = '\0';
  int				min = 0;
  int				max = 0;
  const TKatMOT			*motor;
  
  
  min = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos() + 1000;
  max = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos() - 1000;

  /*on met la vitesse de ce moteur a velocity*/
  katana->setMotorVelocityLimit(idx, velocity);
  
  if(idx == 0)
    min=-14000;
  
  /*position d arriver*/
  pos_target = max;
  //cout <<"position initial="<< katana->getMotorEncoders(idx, true) << " pos_target=" << pos_target  <<"\n";
  if (pos_target < min)
    pos_target = min;
  else if (pos_target > max)
    pos_target = max;
  //cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
  katana->moveMotorToEnc(idx, pos_target, false);

}

void controle_moteur_vitesse(/*CLMBase *katana,*/ int idx, int velocity)
{
  int				i = 0;
  char				m = '\0';
  const TKatMOT			*motor;
  bool change = true;

  /*parametre pour le calcul de temps*/
  long Secondes;
  long MicroSecondes;
  struct timeval Input;
  struct timeval Output;
  
  
  
  /*on met la vitesse de ce moteur a velocity*/
  /*on ne peut pas mettre des vitesses negatives*/
  /*lorsqu'on rentre un nombre negatif la vitesse du moteur est tres rapide*/
  
  /*position d arriver*/
  /*on reste entre la position min et max*/




  if(velocity > 0)
    {
      if (current_target[idx] == pos_max[idx]) change = false;
      else {
      current_target[idx] = pos_max[idx];
      change = true ;
      }
       if (idx == 0) {if (velocity > 100) velocity = 100;}
      katana->setMotorVelocityLimit(idx, velocity);
     
    }
  else if (velocity < 0)
    {  
      if (current_target[idx] == pos_min[idx]) change = false;
      else {
      current_target[idx] = pos_min[idx];
      change = true ;
      }
      if (idx == 0) {if (velocity < -100) velocity = -100;}
      katana->setMotorVelocityLimit(idx, -velocity);
     
    }

 /*mesure du temps*/
  gettimeofday(&Input,NULL);
  
  if(velocity == 0)
    {current_target[idx] = 0; 
      katana->freezeMotor(idx);
    }
  else
    {
      if (change)      katana->moveMotorToEnc(idx, current_target[idx], false);
    
    }

  /*fin de mesure du temps*/
  gettimeofday(&Output,NULL);
  Secondes = Output.tv_sec - Input.tv_sec;
  MicroSecondes = 1000000*Secondes + Output.tv_usec - Input.tv_usec;
  //printf("microsecondes=%ld\n",MicroSecondes);
 
}

void controle_moteur_vitesse(/*CLMBase *katana,*/ int idx)
{
  int				i = 0;
  int				pos_target = 0;
  char				m = '\0';
  int				min = 0;
  int				max = 0;
  const TKatMOT			*motor;
  ofstream			pwmfile;
  ofstream			posfile;
  int                           z;
  min = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMinPos() + 1000;
  max = katana->GetBase()->GetMOT()->arr[idx].GetEncoderMaxPos() - 1000;

  if(idx == 0)
    min=-14000;
  

  pwmfile.open("pwm.txt");
  posfile.open("pos.txt");

  while (42)
    {
      m = '\0';
      cout << "\n"
	"4 - aller vers buter Min\n"
	"6 - aller vers buter Max\n"
	"p - afficher les position min et max\n"
	"q - revenir au menu principal\n";
      cin >> m;
      switch (m)
	{
  
	case '4' : 
	  {
	    int i;

	    pos_target = min;
	    cout <<"position initial="<< katana->getMotorEncoders(idx, true) << " pos_target=" << pos_target  <<"\n";
	    if (pos_target < min)
	      pos_target = min;
	    else if (pos_target > max)
	      pos_target = max;
	    cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
	    katana->moveMotorToEnc(idx, pos_target, false);
	    /*cout<< "tappez sur une touche pour stopper le moteur\n";
	      cin>>z;
	      cout<< "on affiche la touche " << z <<"\n";
	      katana->freezeMotor(idx);
	      for (i = 0; i < 30; i++)
	      {
	      const TMotPVP			*mypvp = NULL;
	      
	      mypvp = mygetpvp(katana, idx);
	      cout << "[moteur " << idx << "] position = " << mypvp->pos << " - vitesse = " << mypvp->vel << " - pwm cycle = " << (int)mypvp->pwm << "\n";
	      }*/
	    cout<< "\n-->tapez une valeur pour controler la vitesse de tous les moteurs\n";
	    cout<<"-->";
	    cin>>z;
	    cout<< "on affiche la touche " << z <<"\n";
	    write_vitesse_all_encoder(/*katana,*/z);
	  }
	  break;
	case '6' :
	  {
	    int i;
	    pos_target = max;
	    if (pos_target < min)
	      pos_target = min;
	    else if (pos_target > max)
	      pos_target = max;
	    cout << "deplacement du moteur " << idx << " a la position " << pos_target << "\n";
	    katana->moveMotorToEnc(idx, pos_target, false);
	    /*cout<< "\n-->tapez sur une touche pour stopper le moteur\n";
	      cout<<"-->";
	      cin>>z;
	      cout<< "on affiche la touche " << z <<"\n";
	      katana->freezeMotor(idx);
	      for (i = 0; i < 30; i++)
	      {
	      const TMotPVP			*mypvp = NULL;
	      
	      mypvp = mygetpvp(katana, idx);
	      cout << "[moteur " << idx << "] position = " << mypvp->pos << " - vitesse = " << mypvp->vel << " - pwm cycle = " << (int)mypvp->pwm << "\n";
	      }*/
	    cout<< "\n-->tapez une valeur pour controler la vitesse de tous les moteurs\n";
	    cout<<"-->";
	    cin>>z;
	    cout<< "on affiche la touche " << z <<"\n";
	    write_vitesse_all_encoder(/*katana,*/z);

	  }
	  break;
	case 'p' :
	  {
	    cout << "Position min = " << min << " - Position max = " << max << "\n";
	  }
	  break;
	case 'q' :
	  {
	    pwmfile.close();
	    posfile.close();
	    return;
	  }
	  break;
	default :
	  {
	    cerr << "commande inconnue\n";
	  }
	  break;
	}
    }
}



/**********************************************************************************************************************/


void gochoosemotor_controle_vitesse(/*CLMBase *katana*/)
{
  int		idx = -1;

  cout << "\n"
    "       |   |   ouvert : left\n"
    "       \\ 5 /   ferme : right\n"
    "        \\_/\n"
    "        | |\n"
    "       _|_|_\n"
    "       |   |\n"
    "  left | 4 | right\n"
    "       |___|\n"
    "        | |\n"
    "       _|_|_\n"
    "right |     |\n"
    "      |  3  |\n"
    " left |_____|\n"
    "        | |\n"
    "        | |\n"
    "       _|_|_\n"
    "right |     |\n"
    "      |  2  |\n"
    " left |_____|\n"
    "        | |\n"
    "        | |\n"
    "        | |\n"
    "       _|_|_\n"
    " left |     |\n"
    "      |  1  |\n"
    "right |_____|\n"
    "        | |\n"
    "        | |\n"
    "        | |\n"
    "       _| |_\n"
    "      /     \\\n"
    "right |  0  | left\n"
    "      |_____|\n"
    "\n";
  cout << "Choisissez le moteur a deplacer :\n";
  cin >> idx;
  cout << "Vous avez choisi le moteur " << idx << "\n";
  if ((idx < 0) || (idx >= katana->getNumberOfMotors()))
    {
      cout << "mais ce moteur n existe pas !! Retour au menu principal.\n";
      return ;
    }
  
  controle_moteur_vitesse(/*katana,*/ idx);
}


/**********************************************************************************************************************/



void				gochoosemotor(/*CLMBase *katana*/)
{
  int		idx = -1;
  int		step = 100;
  int		sens_tab[6] = { -1, -1, -1, -1, -1 ,1 };

  cout << "\n"
    "       |   |   ouvert : left\n"
    "       \\ 5 /   ferme : right\n"
    "        \\_/\n"
    "        | |\n"
    "       _|_|_\n"
    "       |   |\n"
    "  left | 4 | right\n"
    "       |___|\n"
    "        | |\n"
    "       _|_|_\n"
    "right |     |\n"
    "      |  3  |\n"
    " left |_____|\n"
    "        | |\n"
    "        | |\n"
    "       _|_|_\n"
    "right |     |\n"
    "      |  2  |\n"
    " left |_____|\n"
    "        | |\n"
    "        | |\n"
    "        | |\n"
    "       _|_|_\n"
    " left |     |\n"
    "      |  1  |\n"
    "right |_____|\n"
    "        | |\n"
    "        | |\n"
    "        | |\n"
    "       _| |_\n"
    "      /     \\\n"
    "right |  0  | left\n"
    "      |_____|\n"
    "\n";
  cout << "Choisissez le moteur a deplacer :\n";
  cin >> idx;
  cout << "Vous avez choisi le moteur " << idx << "\n";
  if ((idx < 0) || (idx >= katana->getNumberOfMotors()))
    {
      cout << "mais ce moteur n existe pas !! Retour au menu principal.\n";
      return ;
    }
  cout << "Choisissez le pas d avancement entre 100 et 3000 : \n";
  cin >> step;
  cout << "Vous avez choisi un pas d avancement de " << step << "\n";
  if ((step < 100) ||(step > 3000))
    {
      cout << "mais il n est pas compris entre 100 et 3000!! Retour au menu principal.\n";
      return ;
    }
  gomovemotor(/*katana,*/ idx, step, sens_tab[idx]);
}



/*************************************************************/
/*************************************************************/
/************                                       **********/
/************                                       **********/
/************       Allez a la position min         **********/
/************    pour eviter que les encodeurs      **********/
/************             ne cassent                **********/
/************                                       **********/
/************                                       **********/
/*************************************************************/
/*************************************************************/

void aller_pos_max(/*CLMBase *katana*/)
{
  int idx=0;
  for(idx=0 ; idx < katana->getNumberOfMotors() ; idx++)
    katana->moveMotorToEnc(idx, pos_max[idx], false);
}

void aller_pos_min(/*CLMBase *katana*/)
{
  int idx=0;
  for(idx=0 ; idx < katana->getNumberOfMotors() ; idx++)
    katana->moveMotorToEnc(idx, pos_min[idx], false);
}


/*************************************************************/
/*************************************************************/
/************                                       **********/
/************                                       **********/
/************    Allez a la position calibration    **********/
/************       pour par exemple fin de         **********/
/************                  manip                **********/
/************                                       **********/
/************                                       **********/
/*************************************************************/
/*************************************************************/


void aller_pos_calibration(/*CLMBase *katana*/)
{
  int idx=0;
  int pos_calibration[6]={30500,-30500,-30500,30500,30500,30500};
  for(idx=0 ; idx < katana->getNumberOfMotors() ; idx++)
    katana->moveMotorToEnc(idx, pos_calibration[idx], false);

}


/*************************************************************/
/*************************************************************/
/************                                       **********/
/************                                       **********/
/************          Calibration Manuelle         **********/
/************             Jamais tester             **********/
/************                                       **********/
/************                                       **********/
/*************************************************************/
/*************************************************************/


void				manualcalibrate(/*CLMBase *katana,*/ int idx)
{
  TMotCLB clb = *katana->GetBase()->GetMOT()->arr[idx].GetCLB();
  TMotAPS aps;

  if (!clb.enable)
    return;
  // On desactive le moteur
  aps.actpos = 0;
  aps.mcfAPS = MCF_ON;
  katana->GetBase()->GetMOT()->arr[idx].sendAPS(&aps);

  katana->GetBase()->GetMOT()->arr[idx].setCalibrated(false);

  cout << "offset du moteur" << idx << " = " << katana->GetBase()->GetMOT()->arr[idx].GetInitialParameters()->encoderOffset << "\n";

  {
    TMotAPS aps = { 
      clb.mcf, 
      //encoderOffset du fichier de conf
      katana->GetBase()->GetMOT()->arr[idx].GetInitialParameters()->encoderOffset
    };

    katana->GetBase()->GetMOT()->arr[idx].sendAPS(&aps);
	
    katana->mov(idx, 
		//encoderPositionAfter du fichier de configuration
		clb.encoderPositionAfter,
		true);
  }

  //calibrate( j, *base->GetMOT()->arr[j].GetCLB(), *base->GetMOT()->arr[j].GetSCP(), *base->GetMOT()->arr[j].GetDYL() );
  katana->GetBase()->GetMOT()->arr[idx].setCalibrated(true);
  cout << "Moteur " << idx << " calibre\n";
}



/**********************************************************************************************************************/



void				goreadencodersvalues(/*CLMBase *katana*/)
{
  std::vector<int> encoders(katana->getNumberOfMotors(), 0);

  std::cout << "\nEncoder values: " << std::endl;
  katana->getRobotEncoders(encoders.begin(), encoders.end(), true);
  for (std::vector<int>::iterator i= encoders.begin(); i != encoders.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}



/**********************************************************************************************************************/



void				gocalibrate(/*CLMBase *katana*/)
{
  cout << "calibration en cours ... NE PAS STOPPER LE PROGRAMME MEME AVEC UN CTRL+C\n";
  katana->calibrate();
  cout << "calibration terminee\n";
}





/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/***********                                                ***********/
/***********                                                ***********/
/***********          lis les capteurs de la pince          ***********/
/***********                                                ***********/
/***********                                                ***********/
/**********************************************************************/
/**********************************************************************/

void				readsensorvalue(/*CLMBase *katana*/)
{
  CSctBase			*sensctrl;
  const TSctDAT			*data;
  int capteur_init[16]={};
  std::cout << "\nCurrent Sensor values:" << std::endl;
  sensctrl = &katana->GetBase()->GetSCT()->arr[0];
  data = sensctrl->GetDAT();
  sensctrl->recvDAT();
  for (int i=0; i<data->cnt; i++)
    {
      std::cout.width(5);
      std::cout << data->arr[i] << " ";
    }
  std::cout << "\n";
}




/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/***********                                                ***********/
/***********                                                ***********/
/***********            fonction prise d un objet?          ***********/
/***********                                                ***********/
/***********                                                ***********/
/**********************************************************************/
/**********************************************************************/
int* valeur_capteur()
{
  CSctBase			*sensctrl;
  const TSctDAT			*data;
  int *capteur_init; 

  capteur_init = (int *)malloc(16*sizeof(int));

  if(capteur_init == NULL)
    {
      cout << "erreur de malloc\n";
      exit(1);
    }

  sensctrl = &katana->GetBase()->GetSCT()->arr[0];
  data = sensctrl->GetDAT();
  sensctrl->recvDAT();

  for (int i=0; i<data->cnt; i++)
    {
      //cout << "sensor " << i << "=" << data->arr[i] << "\n";
      capteur_init[i] = data->arr[i];      
    }

  return capteur_init;
} 



int prise_objet(/*CLMBase *katana*/)
{
  CSctBase			*sensctrl;
  const TSctDAT			*data;
  //int capteur_init[16]={230, 172, 254, 201, 12, 88, 85, 94, 220, 160, 255, 218, 83, 138, 99, 103}; premier valeur
  //int capteur_init[16]={230, 172, 254, 201, 12, 88, 85, 94, 197, 139, 255, 218, 83, 138, 99, 103}; deuxiemme valeur
  int capteur_init[16]={230, 143, 254, 201, 12, 60, 85, 94, 143, 76, 255, 174, 83, 105, 99, 103};

  int accu=0;
  int difference=0;
  sensctrl = &katana->GetBase()->GetSCT()->arr[0];
  data = sensctrl->GetDAT();
  sensctrl->recvDAT();

  for (int i=0; i<data->cnt; i++)
    {
      cout << "sensor " << i << "=" << data->arr[i] << "\n";
      difference=data->arr[i] - capteur_init[i];
      if(difference<0)
	difference = -difference;
      
      accu=accu+difference;
      
    }
  

  /*for (int i=0; i<data->cnt; i++)
   *{
   *  cout << "sensor " << i << "=" << data->arr[i] << "\n";
   *  accu = accu + data->arr[i];
   *
   *}
   *
   *return accu;
   */

  if(accu < 200)
    { 
      cout << "------>rien dans la pince \n";
      cout << "------> Accu=" << accu <<"\n";
      return 0;
    }
  else 
    {
   
      cout << "------>object dans la pince \n";
      cout << "------> Accu=" << accu <<"\n";
   
      return 1;
    }
  

}


void fermer_pince()
{

  int boolean;
  boolean = prise_objet();
  cout << "boolean= " << boolean << "\n"; 
  
  if(boolean == 1)
    {
      
      controle_moteur_vitesse(5,-50);
      cout << "Je ferme la pince \n";
  
    }

  
  else
    {
      if(boolean == 2)
	{
	  cout << "je freeze les moteurs\n";
	  katana->freezeMotor(5);
	}
      else
	{
	  cout << "Pas d objet dans la pince\n";
	}
    }
}


void readidentificationstring(/*CLMBase *katana*/)
{
  const TKatIDS			*ids;

  katana->GetBase()->recvIDS();
  ids = katana->GetBase()->GetIDS();
  cout << "Identification string : " << ids->strID << "\n";
}



/*************************************************************************/
/*************************************************************************/
/***********                                                    **********/
/***********                                                    **********/
/***********            lit la vesion du firmware               **********/
/***********                                                    **********/
/***********                                                    **********/
/*************************************************************************/
/*************************************************************************/

short readmasterfirmware(/*CLMBase *katana*/)
{
  const TKatMFW			*mfw;
  short				version;
  short				revision;

  katana->GetBase()->recvMFW();
  mfw = katana->GetBase()->GetMFW();
  version = mfw->ver;
  revision = mfw->rev;
  cout << "version : " << version << " revision : " << revision << "\n";
  
  return  version;
}



/*************************************************************************/
/*************************************************************************/
/***********                                                    **********/
/***********                                                    **********/
/***********         Alarme lorsqu il y a un controle C         **********/
/***********                                                    **********/
/***********                                                    **********/
/*************************************************************************/
/*************************************************************************/




void alarm(int sig)
{
  
  printf("il y a eu un controle C\n");
  /* faire le traitement qu il faut*/
  aller_pos_calibration();
}

void capture_signal(int signo, siginfo_t *info, void *context)
{
  fprintf(stdout, "sig = %i (%i) - code = %i\n", signo, info->si_signo, info->si_code);
  
  /*
  ** ici inclure le code pour traiter le signal capturer
  ** - blocage des moteurs
  ** - ... etc ...
  */
  aller_pos_max();
  exit(1);
}

/*************************************************************************/
/*************************************************************************/
/***********                                                    **********/
/***********                                                    **********/
/***********            Test si le bras a ete calibre           **********/
/***********                                                    **********/
/***********                                                    **********/
/*************************************************************************/
/*************************************************************************/


/*
* apriorie lorqu on eteint le robot et que l on demandes les 
*valeurs des encodeurs les valeurs sont toujours les memes
*dans toutes les positions des encodeurs
*ca peut etre un bon moyen de savoir si l on a fait
*la calibration ou non
*/
int is_calibrated(/*CLMBase *katana*/)
{
  int avant_calib[6]={28920,31000,-29536,23920,-31000,-31000};
  int erreur=0;;
  int erreur_acc=0;
  short encodeur;
  int motorNumber;

  cout << "entree dans la fonction read_encodeur \n";

  for(short motorNumber = 0; motorNumber < katana->getNumberOfMotors(); ++motorNumber) {
    encodeur= katana->getMotorEncoders(motorNumber, true);
    erreur=encodeur-avant_calib[motorNumber];

    if(erreur<0)
      erreur=-erreur;

    cout << "position= " << encodeur << "erreur= " << erreur  <<"\n"; 

    erreur_acc = erreur_acc + erreur;
  }

  cout << "sortie de la fonction read_encodeur \n";


  if(erreur > 10)
    {
      return 1;
    }
  else 
    {
      return 0;
    }
  
}



/*************************************************************************/
/*************************************************************************/
/***********                                                    **********/
/***********                                                    **********/
/***********                       Main                         **********/
/***********                                                    **********/
/***********                                                    **********/
/*************************************************************************/
/*************************************************************************/

int main(int argc, char **argv)
{
  char				go = '\0';
  int				i = 0;
  //CLMBase			*katana = new CLMBase();
  katana = new CLMBase();
  const TMotPVP *mypvp = NULL; /*structure qui va recevoir la proprioception*/
  std::auto_ptr<CCdlSocket>	device;
  std::auto_ptr<CCplSerialCRC>	protocol;
  int velocity=10;
  struct sockaddr_in server,client;
  struct hostent *hp;
  char buf[MAXBUF];
  
  int buf_len, sk,n_sent,n_read;
  socklen_t client_ln;
  int vit_ou_pos=0;
  
  
  char speed[256];
  char position[256];
  int pince; /*nous dit si il y a un object dans la pince*/


  char numero[256];
  char commande[256];
  char separateur[256];
  char param[256];        /*parametre qui controle la vitesse ou la position*/

  int b;
  




  /*gestion des signaux (controle C)*/
  /*act.sa_handler = alarm;
   *sigaction(SIGINT,&act,0);
   */


  memset(&act, 0, sizeof(struct sigaction));

  /*
  ** Pendant la capture d'un signal, on ne pourra pas recevoir d'autre signaux
  **
  ** Pour autoriser les signaux pendant une capture, utiliser sigemptyset(...)
  */
  sigfillset(&act.sa_mask);

  /*
  ** On precise qu'on veut des informations sur le signal capture
  */
  act.sa_flags = SA_SIGINFO;

  /*
  ** On definit la fonction qui sera appelee lors de la reception d'un signal
  **
  ** on utilise sa_sigaction a la place de sa_handler, 
  ** car on a le flag SA_SIGINFO
  */
  act.sa_sigaction = capture_signal;

  
  /*
   ** Prepare la capture de TOUS les signaux.
   ** _NSIG est defini dans bit/signum.h et correspond au numero du signal 
   ** max + 1. Il tient compte des signaux temps reel
   */
  for (i = 1; i < _NSIG; i++)
    sigaction(i, &act, NULL);


 
  
  cout << "Initialisation en cours de ...\n";
  try
    {
      device.reset(new CCdlSocket((char*)ADDR,PORT));
      //device.reset(new CCdlSocket("192.168.168.232",5566));

      protocol.reset(new CCplSerialCRC());
      protocol->init(device.get());
      
      //  katana.reset(new CLMBase());
      katana->create("katana6M180.cfg", protocol.get());
    }
  catch (Exception &e)
    {
      std::cout << "ERROR: " << e.message() << std::endl;
      return -1;
    }

  cout << "... Fin initialisation en cours de\n";  
   /******************************************************************/
  /******************************************************************/
  /**********                                               *********/
  /**********                                               *********/
  /**********          on realise la calibration            *********/
  /**********                                               *********/
  /**********                                               *********/
  /******************************************************************/
  /******************************************************************/
  
 
  //cout << "Calibration automatique en cours ...\n";
  //gocalibrate(/*katana*/);
  //aller_pos_max(/*katana*/);
  //cout << "... Calibration automatique terminee\n";
  //cout << "... Initialisation terminee\n";



 /**********        parametre pour ivy       *************/
  const char* bus = 0;


   /* handling of environment variable */
  if (!bus)
    bus = getenv ("IVYBUS");
  
  /* initializations */
  IvyInit ("mon_hello", "Hello le monde", 0, 0, 0, 0);
  IvyStart (bus);

  /* binding of HelloCallback to messages starting with 'Hello' */
  IvyBindMsg (hello_Callback, 0, "^Hello(.*)");

  /* binding of ByeCallback to 'Bye' */
  IvyBindMsg (bye_Callback, 0, "^Bye$");

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


  /* main loop */
  IvyMainLoop();





  
 
  
 

 
  /******************************************************************/
  /******************************************************************/
  /**********                                               *********/
  /**********                                               *********/
  /**********            fin de la calibration              *********/
  /**********                                               *********/
  /**********                                               *********/
  /******************************************************************/
  /******************************************************************/
  cout << "bras va au butees Max soft ...\n";
  aller_pos_max();
  
  
  printf("###### DEBUT SERVEUR #####\n");
  if (argc != 1) {
    printf("Usage: %s \n",argv[0]);
    exit(0);
  }
  
  /* creation d'un socket
   * IP protocol family(PF_INET)
   * UDP (SOCK_DGRAM)
   */
  
  if( (sk=socket(PF_INET,SOCK_DGRAM,0)) < 0 ) {
    printf("Erreur de creation de socket !!!\n");
    exit(1);
  }
  
  
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  /* etabli le numero du port du serveur */
  server.sin_port = htons(PORT1);
  
  
  /* attribution de l'adresse du serveur au socket */
  if ( (i = bind(sk,(struct sockaddr *)&server, sizeof(server))) < 0 ) {
    printf("Erreur dans le bind mon commentaire\n");
    perror ("Erreur de bind sur le socket");
    exit(3);
  }
  
  /* boucle principale */
  while(1)
    {
     
      for (i=0;i<MAXBUF;i++)
	buf[i] = '\0';
      
      /* on attend une demande du client */
      client_ln = sizeof(client);
      n_read = recvfrom(sk,buf,MAXBUF-1,0,(struct sockaddr *)&client,&client_ln);
      if(n_read < 0) {
	perror("Probleme de reception: n_read<0");
	exit(4);
      }
     
      /*********************************************************************/
      /*********************************************************************/
      /********************                                *****************/
      /******************** on envoie la commande au robot *****************/
      /********************                                *****************/
      /*********************************************************************/
      /*********************************************************************/

     

      sscanf(buf,"%s %s %s %s",numero,commande,separateur,param);
      
      if(strcmp(commande,"val_joint_vitessemotor1:motor1")==0)
	{
	  //printf("----->val_joint_vitessemotor1:motor1\n");
	  
	  vit_ou_pos=atoi(param);
	  controle_moteur_vitesse( 0 ,vit_ou_pos);
	  
	  //printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
	}
      else{
	if(strcmp(commande,"val_joint_vitessemotor2:motor2")==0)
	  {
	    //printf("----->val_joint_vitessemotor2:motor2\n");

	    vit_ou_pos=atoi(param);
	    controle_moteur_vitesse( 1 ,vit_ou_pos);

	    //printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
	  }
	else{
	  if(strcmp(commande,"val_joint_vitessemotor3:motor3")==0)
	    {
	      //printf("----->val_joint_vitessemotor3:motor3\n");
	    	     
	      vit_ou_pos=atoi(param);
	      controle_moteur_vitesse( 2 ,vit_ou_pos);

	      //printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
	      
	    }
	  else{
	    if(strcmp(commande,"val_joint_vitessemotor4:motor4")==0)
	      {
		//printf("----->val_joint_vitessemotor4:motor4\n");

		vit_ou_pos=atoi(param);
		controle_moteur_vitesse( 3 ,vit_ou_pos);

		//printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
		
	      }
	    else{
	      if(strcmp(commande,"val_joint_vitessemotor5:motor5")==0)
		{
		  //printf("----->val_joint_vitessemotor5:motor5\n");

		  vit_ou_pos=atoi(param);
		  controle_moteur_vitesse( 4 ,vit_ou_pos);

		  //printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
		  
		}
	      else{
		if(strcmp(commande,"val_joint_vitessemotor6:motor6")==0)
		  {
		    //printf("----->val_joint_vitessemotor6:motor6\n");

		    vit_ou_pos=atoi(param);
		    /*if(vit_ou_pos>0)
		      {
			katana->openGripper();
		      }
		    if(vit_ou_pos<0)
		      {
			katana->closeGripper();
		      }*/
		    controle_moteur_vitesse( 5 ,vit_ou_pos);
		    
		    //printf("---->commande=%s vitesse=%d \n",commande,vit_ou_pos);
		    
		  }
		else{
		  if(strcmp(commande,"val_joint_positionmotor1:motor1")==0)
		    {
		      //printf("----->val_joint_motor1\n");
		      vit_ou_pos=atoi(param);
		      katana->moveMotorToEnc(0, vit_ou_pos, false);
		      //printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
		    }
		  else{
		    if(strcmp(commande,"val_joint_positionmotor2:motor2")==0)
		      {
			//printf("----->val_joint_motor2\n");
			vit_ou_pos=atoi(param);
			katana->moveMotorToEnc(1, vit_ou_pos, false);
			//printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
		      }
		    else{
		      if(strcmp(commande,"val_joint_positionmotor3:motor3")==0)
			{
			  //printf("----->val_joint_motor3\n");
			  vit_ou_pos=atoi(param);
			  katana->moveMotorToEnc(2, vit_ou_pos, false);
			  //printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
			}
		      else{
			if(strcmp(commande,"val_joint_positionmotor4:motor4")==0)
			  {
			    //printf("----->val_joint_motor4\n");
			    vit_ou_pos=atoi(param);
			    katana->moveMotorToEnc(3, vit_ou_pos, false);
			    //printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
			  }
			else{
			  if(strcmp(commande,"val_joint_positionmotor5:motor5")==0)
			    {
			      //printf("----->val_joint_motor5\n");
			      vit_ou_pos=atoi(param);
			      katana->moveMotorToEnc(4, vit_ou_pos, false);
			      //printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
			    }
			  else{
			    if(strcmp(commande,"val_joint_positionmotor6:motor6")==0)
			      {
				//printf("----->val_joint_motor6\n");
				vit_ou_pos=atoi(param);
				katana->moveMotorToEnc(5, vit_ou_pos, false);
				//printf("---->commande=%s position=%d \n",commande,vit_ou_pos);
				
			      }
			    else{
			      if(strcmp(commande,"proprio_motor1:motor1,")==0)
				{
				  //printf("##############je recupere la proprio du motor1!!!!\n");
				  
				  mypvp=mygetpvp(0);
				  vit_ou_pos=mypvp->pos;
				  //printf("position=%d\n",vit_ou_pos);
				  
				  /*
				   *on remplie le champ buf
				   */
				  
				  //printf("buffer=%s\n",buf);
     
				  snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);

				  //printf("buffer=%s\n",buf);
				}
			      else{
				if(strcmp(commande,"proprio_motor2:motor2,")==0)
				  {
				    //printf("##############je recupere la proprio du motor2!!!!\n"); 
				    mypvp=mygetpvp(1);
				    vit_ou_pos=mypvp->pos;
				    //printf("position=%d\n",vit_ou_pos);
				    /*
				     *on remplie le champ buf
				     */
				    
				    //printf("buffer=%s\n",buf);
				    
				    snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
				    
				    //printf("buffer=%s\n",buf);

				  }
				else{
				  if(strcmp(commande,"proprio_motor3:motor3,")==0)
				    {
				      //printf("##############je recupere la proprio du motor3!!!!\n");
				      mypvp=mygetpvp(2);
				      vit_ou_pos=mypvp->pos;
				      //printf("position=%d\n",vit_ou_pos);
				      
				      /*
				       *on remplie le champ buf
				       */
				      
				      //printf("buffer=%s\n",buf);
				      
				      snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
				      
				      //printf("buffer=%s\n",buf);
				    }
				  
				  else{
				    if(strcmp(commande,"proprio_motor4:motor4,")==0)
				      {
					//printf("##############je recupere la proprio du motor4!!!!\n");
					mypvp=mygetpvp(3);
					vit_ou_pos=mypvp->pos;
					//printf("position=%d\n",vit_ou_pos);
				      
					/*
					 *on remplie le champ buf
					 */
					
					//printf("buffer=%s\n",buf);
					
					snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
					
					//printf("buffer=%s\n",buf);
					
				      }
				    else{
				      if(strcmp(commande,"proprio_motor5:motor5,")==0)
					{
					  //printf("##############je recupere la proprio du motor5!!!!\n"); 
					  mypvp=mygetpvp(4);
					  vit_ou_pos=mypvp->pos;
					  //printf("position=%d\n",vit_ou_pos);

					  /*
					   *on remplie le champ buf
					   */
					  
					  //printf("buffer=%s\n",buf);
					  
					  snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
					  
					  //printf("buffer=%s\n",buf);
					}
				      else{
					if(strcmp(commande,"proprio_motor6:motor6,")==0)
					  {
					    //printf("##############je recupere la proprio du motor6!!!!\n");
					    mypvp=mygetpvp(5);
					    vit_ou_pos=mypvp->pos;
					    //printf("position=%d\n",vit_ou_pos);

					    /*
					     *on remplie le champ buf
					     */
					    
					    //printf("buffer=%s\n",buf);
					    
					    snprintf(buf, sizeof(buf), "%s %d",numero, vit_ou_pos);
					    
					    //printf("buffer=%s\n",buf);
					  }
					else
					  {
					    if(strcmp(commande,"proprio_pince")==0)
					      {
						//printf("---------->je recupere la proprio de la pince!!!!\n");
						pince = prise_objet();
						//fermer_pince();
						//controle_moteur_vitesse(5,-50);
						snprintf(buf, sizeof(buf), "%s %d",numero, pince);
						//printf("buffer=%s\n",buf);
					      }
					    else
					  {
					    if(strcmp(commande,"init_params")==0)
					      {
						printf("---------->initialisation des parametres du bras\n");
						for (i=0;i<katana->getNumberOfMotors();i++)
						  current_target[i] = 0;
				
					      }
					    else
					      {
						if(strcmp(commande,"sensor")==0)
						  {
						    //printf("---------->je recupere la proprio de la pince!!!!\n");
						    int taille = 0;
						    int *tab = NULL;
						    char *buffer = NULL;
						    tab=(int *)malloc(16*sizeof(int));
						    buffer = buf;

						    if(tab == NULL)
						      {
							cout << "attention pb de malloc\n";
							exit(1);
						      }
						    
						    tab=valeur_capteur();
						    taille = snprintf(buffer, MAXBUF - (buffer-buf), "%s",numero);
						    buffer = buffer + taille ;
						    for(i=0 ; i<16 ; i++)
						      {
							taille=snprintf(buffer, MAXBUF - (buffer-buf), " %i",tab[i]);
							buffer = buffer + taille;
						      }

						    //readpvp();
						    /*printf("buffer=%s\n",buf);*/
						  }
					      }
					  }
				      }
				      
				    }
				  }
				}
			       }
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
      
      
      /**
      *
      *on envoie la commande au robot
      *      
      */
      
      
      
      /*******************************************************************/
      /*******************************************************************/
      /*                                                                 */
      /* maintenant, on envoie au client un paquet contenant le messsage */
      /*                      accuser de reception                       */
      /*                                                                 */
      /*******************************************************************/
      /*******************************************************************/
      
     
      printf("buff %s\n",buf);
      n_sent = sendto(sk,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client));

     
      //n_sent = sendto(sk,reponse,sizeof(reponse),0,(struct sockaddr *)&client,sizeof(client));
      if(n_sent < 0) {
	perror("Probleme d'envoie de donn�es");
	exit(5);
      }
     
    }  
  return 0;
}
