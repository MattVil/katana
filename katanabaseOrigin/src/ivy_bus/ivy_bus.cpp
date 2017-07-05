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
#include "ivy_bus.h"
#include <stdio.h>
#include <getopt.h>
#include <ivy.h>
#include <ivyloop.h>
#include <string.h>
#include <time.h>
#include "cinematique.h"
#include "katana.h"
#include "main.h"



/* callback associated to "Help" messages */
void help_Callback (IvyClientPtr app, void *data, int argc, char **argv)
{
 
  printf("callback pour help active \n");
  
  IvySendMsg("'Hello' : test simplement la connection");
  IvySendMsg("'Help'  : affiche l aide");
  IvySendMsg("'Status' : affiche le status du bras");
  IvySendMsg("'Ready' : stop la connection Ivy et lance le serveur pour promethe");
  IvySendMsg("'Version' : version du firmare");
  IvySendMsg("'Calibrated' : affiche si la calibration a ete fait");
  IvySendMsg("'Gocalibration' : faire la calibration");
  IvySendMsg("'Proprio' : donne la proprio du bras");
  IvySendMsg("'Test' : lance le test en cours");
  IvySendMsg("'Security' : permet de verifier le plan de securite");
  IvySendMsg("'AddSecurity' : permet de rajouter des obstacles cylindriques dans la fonction de securite");
  IvySendMsg("'SaveSecurity' : permet de sauvegarder la configuration actuelle des cylindres apres en avoir rajoute (-->secu.conf)");
  IvySendMsg("'3Dpos' : affiche les coordonnees 3D des differentes articulation");
  IvySendMsg("'Passif' : Le bras peut passer en mode inactif. Apres la premiere utilisation, si on le laisse actif pendant plus de quelques secondes alors on sort de la fonction 'Passif'. En outre, la securite affiche si le point extremite de la pince est actuellement dans la zone d'un cylindre ou pas. (Utile pour verifier que la zone de securite a ete correctement delimite par secu.conf");
}


/* callback associated to "Hello" messages */
void hello_Callback (IvyClientPtr app, void *data, int argc, char **argv)
{
  const char* arg = (argc < 1) ? "" : argv[0];
  IvySendMsg ("Bonjour%s\n", arg);
  printf("callback pour hello active %s\n",(char *)data);
}


/* callback associated to "Ready" messages */
void ready_Callback (IvyClientPtr app, void *data, int argc, char **argv)
{
  int b;
  b = is_calibrated();
  if(b == 0)
    {
      IvySendMsg ("---->CALIBRATION PAS OK\n");
      IvySendMsg("Calibration du bras en cours ...");
      gocalibrate();
      IvySendMsg("... Fin de la calibration du bras");
    }
  else
    {  
      IvySendMsg ("---->CALIBRATION OK\n");
     
    }
  
  printf("callback pour Ready\n");
  IvyStop ();
}


/* callback associated to "Calibrated" messages */
/* utilisateur sera capable de savoir si le bras a ete calibrer*/
void isCalibrate_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  int b;
  /* la valeur de b est 0 si la calibration ne semble pas faite */
  /* sinon b vaut 1 si la calibration est faite*/
  b = is_calibrated();
 
  if(b == 0)
    IvySendMsg ("---->CALIBRATION PAS OK\n");
  else
    IvySendMsg ("---->CALIBRATION OK\n");
}


/* callback associated to "Version" messages */
/* renvoie le numero de version */
void firmware_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  short version;
  version= readmasterfirmware();
  printf("callback pour Version\n");
  IvySendMsg ("La version du firmware ----> %i\n",version);
}


/* callback associated to "Gocalibration" messages*/
/* fait la calibration du bras */
void gocalibration_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  int b;
  char ans[2];
  b = is_calibrated();
  if(b == 0)
  {
    IvySendMsg ("---->CALIBRATION PAS OK\n");
    IvySendMsg("Calibration du bras en cours ...");
    gocalibrate();
    IvySendMsg("... Fin de la calibration du bras");
  }
  else
  {  
    IvySendMsg ("---->CALIBRATION OK\n");      
    //~ IvySendMsg ("Katanabase is waiting answer\n");
    printf("---->calibration ok\n");
    IvySendMsg ("---->NO NEED FOR CALIBRATION\n"); 
    printf("---->No need for calibration\n");
    //~ printf("Do you still want to calibrate ? (y/n) > ");
    //~ scanf("%c",ans);
    //~ ans[1]='\0';
    //~ if(strcmp(ans,"y")==0) {
      //~ IvySendMsg("Calibration du bras en cours ...");
      //~ gocalibrate();
      //~ IvySendMsg("... Fin de la calibration du bras");
    //~ }
    //~ else {
      //~ IvySendMsg("No calibration performed\n");
      //~ printf("No calibration performed\n");
    //~ }
    IvySendMsg ("Katanabase is waiting answer\n");
    printf("Do you want to move arm to neutral position ? (y/n) > ");
    scanf("%s",ans);
    ans[1]='\0';
    if(strcmp(ans,"y")==0) {      
      printf("Move to neutral position from init \n");
      Arm *katana_arm = katana->get_cinematique();
      go_to_neutral_position_from_init(katana_arm);
      IvySendMsg ("MOvement finished\n");
    }
    else {
      printf("Don't move\n");
      IvySendMsg ("Don't move\n");
    }
  }
}


/* callback associated to "Status" messages*/
/* recupere le numero de version */
/* emettre un avis sur la calibration */
void status_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  short version;  /*numero de version*/
  int b;          /*retour de la valeur de calibration*/
  
  
  /*envoie du numero de version*/
  version= readmasterfirmware();
  IvySendMsg ("La version du firmware ----> %i\n",version);
  
  
  
  /*retour de la calibration*/
  /* la valeur de b est 0 si la calibration ne semble pas faite */
  /* sinon b vaut 1 si la calibration est faite*/
  b = is_calibrated();
  if(b == 0)
    IvySendMsg ("---->CALIBRATION PAS OK\n");
  else
    IvySendMsg ("---->CALIBRATION OK\n");
  /*on propose la calibration*/
  IvySendMsg("Si vous voulez faire la calibration, tapez ------> Gocalibration");
  
}


/* callback associated to "SwitchOff" messages */
/* desactive les moteurs */
void switchOff_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  char answ[10];
  printf("callback pour SwitchOff\n");

  printf("Witch Off Motor (attention a la securite du bras !!) ? (y/n) : ");
  scanf("%s",answ);

  if(strcmp(answ,"y")==0) {
    switchrobot(0);
    IvySendMsg ("SwitchOff----------->done\n");
  }
  else {
    IvySendMsg ("SwitchOff----------->nothing done\n");
  }

}


/* callback associated to "SwithOn" messages */
/* active les moteurs */
void switchOn_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  char answ[10];
  printf("callback pour SwitchOn\n");

  /* fonction a rajouter */
  printf("Witch On Motor ? (y/n) : ");
  scanf("%s",answ);

  if(strcmp(answ,"y")==0) {
    switchrobot(1);
    IvySendMsg ("SwitchOn----------->done\n");
  }
  else {
    IvySendMsg ("SwitchOn----------->nothing done\n");
  }

}

/* callback associated to "Proprio" messages */
/* donne la proprio des moteurs */
void proprio_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  int i;
  int pos;

  printf("callback pour Proprio\n");

  read_encodeur();

  IvySendMsg("proprio has been read\n");
}


/* callback associated to "3Dpos" messages */
/* donne la position 3D de chaque articulation du bras */
void position3D_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  std::vector<int> encod;
  Arm * bras = katana->get_cinematique();
  float coord3D[3];

  printf("callback pour 3Dposition\n");

  encod = katana->get_all_position();

  for(int i=0; i<6; i++) {
    printf("encod[%d]=%d\n",i,encod[i]);
  }
  bras->compute_3Dcoordinates(encod);
  
  for(int i=0; i<NB_JOINTS; i++) {
    bras->get_3Dpos_of_joint(i, coord3D); /* recuperation des coordonnees*/
    printf("Les coordonnees du joint %d sont : %f, %f, %f\n",i,coord3D[0],coord3D[1],coord3D[2]);
  }

  IvySendMsg("3Dposition has been read\n");
}

/* callback associated to "passif" messages */
/** 
* permet d'avoir le mode de fonctionnement passif : en attrapant le bras par le poignet (torsion) le bras devient inactif.
* Lorsque le bras est relache, il redevient actif et reste a la position ou on le laisse.
**/
void passif_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  int i=-1;
  std::vector<int> encod;
  Arm * bras = katana->get_cinematique();
  FILE *temps_f;
  struct timeval temps;
  struct timeval temps_ref;
  
  /* Creation d'un fichier temporaire pour mettre en correspondance le temps et les positions recuperees*/
  temps_f = fopen("temps.SAVE", "w");
  if (temps_f == NULL)
  {
    fprintf(stderr, "ERROR : Impossible to create file temps.SAVE\n");
    exit(1);
  }
  //gettimeofday(&temps,NULL);
  //  fprintf(temps_f,"%ld %ld",temps_ref.tv_sec-temps.tv_sec, temps_ref.tv_usec-temps.tv_sec);
  /* fin creation fichier new*/
  
  if(katana->is_calibrated())
  {
    // initialisation de la position de la pince (pour exp manip passive)
    katana->set_position(5,14000,false);

    katana->set_passif(true);
    IvySendMsg("Passif available\n");
    
    encod = katana->get_all_position();
    
    while(!passif_function(encod))
    {  /* tant que le bras n'est pas desactive */
      usleep(250);   
    }
    
    /* On peut deplacer le bras */
    gettimeofday(&temps_ref,NULL);
    
    while(passif_function(encod))
    {  /* tant que le bras est active */
      usleep(250);
      
      encod = katana->get_all_position();
      bras->verification(encod,false);
      gettimeofday(&temps,NULL);
      fprintf(temps_f,"%ld\n",(temps.tv_sec-temps_ref.tv_sec)*1000000 + temps.tv_usec-temps_ref.tv_usec);
    }
    
    
    /* verification de la securite pour l'articulation 4 */
    encod = katana->get_all_position();
    bras->compute_3Dcoordinates(encod);
    bras->verif_cylinders_debug(4);
    
    /* On laisse 5 secondes pour reenclencher le mode passif. */
    int count=0;
    int passif_activ=false;   
    do
    {
      count=0;
      passif_activ=false;
      while(count<200 && !passif_activ)
      {  /* tant que le bras n'est pas desactive OU 200 -> qqs secondes */
        if(passif_function(encod))
        passif_activ=true;
        usleep(250);
        count++;
      }
      
      if(passif_activ)
      {
        /* On peut deplacer le bras */  
        while(passif_function(encod))
        {  /* tant que le bras est active */
          usleep(250);  

          encod = katana->get_all_position();
          bras->verification(encod,false);
          gettimeofday(&temps,NULL);
          fprintf(temps_f,"%ld\n",(temps.tv_sec-temps_ref.tv_sec)*1000000 + temps.tv_usec-temps_ref.tv_usec);
        }
      }
      
      /* verification de la securite pour l'articulation 4 */
      encod = katana->get_all_position();
      bras->compute_3Dcoordinates(encod);
      bras->verif_cylinders_debug(4);
      
    } while(passif_activ);
    
    /* Le bras a fini d'etre deplace */
    
    /* verification de la securite pour l'articulation 4 */
    encod = katana->get_all_position();
    bras->compute_3Dcoordinates(encod);
    bras->verif_cylinders_debug(4);
    
    
    katana->set_passif(false);
    
    
    fclose(temps_f);
    temps_f = NULL;
    IvySendMsg("Passif disabled\n");
  }
  else
    IvySendMsg("Katana not calibrated, passif is not available\n");
}


/* callback associated to "Test" */
/* : un test... */
void Test_Callback(IvyClientPtr app, void *data, int argc, char **argv)
{
  test(); 
  IvySendMsg(" Test was done\n");
}



