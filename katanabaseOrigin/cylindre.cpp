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
#include "cylindre.h"


/*******************************************************************************
 * ****************************************************************************/
Cylindre::Cylindre()
{
    activated=false;
    id=-1;
}


/*******************************************************************************
 * ****************************************************************************/
Cylindre::~Cylindre() {
}


/*******************************************************************************
 * Verifie si la position donnee en parametre (x,y, z) est dans la zone 
 * determinee par le cylindre. Si mute est vrai alors on affiche pas toutes les 
 * infos.
 * Le parametre bottom donne le plan inferieur (selon y) tandis que hauteur 
 * donne le plan superieur.
 * return    true si vrai
 *           false sinon
 * ****************************************************************************/
bool Cylindre::estDansCylindre(float x, float y, float z)
{
  bool testY=false;
  float distance=-1;
#ifdef DEBUG
  std::cout << "les parametres sont : x:" << x << ", y:" << y << ", z:" << z << ", centre=" << centre[2] << ", hauteur=" << hauteur << std::endl;
#endif
    
  if(z < centre[2] || z > hauteur+centre[2])
  {
#ifdef DEBUG
    std::cout<<"Cylindre '" << name << "': articulation trop haute ou trop basse pour etre dedans ("<<z<<"/"<<hauteur<<")"<<std::endl;
#endif
    return false; /* test de Y dit que de toute facon, ce n'est pas dans le cylindre*/
  }
    
    /* verification de la distance par rapport a l'axe du cylindre */
    
  distance=sqrt((x-centre[0])*(x-centre[0]) + (y-centre[1])*(y-centre[1]));
  
  if(distance>rayon)
  {
#ifdef DEBUG
    std::cout<<"Cylindre '" << name << "': articulation hors du rayon du cylindre ("<<distance<<"/"<<rayon<<")"<<std::endl;
#endif
    return false; /* la localisation n'est pas dans le cylindre */
  }
  std::cout << "x:" << x << ", y:" << y << ", z:" << z << "is in Cylindre '" << name << "' (" << centre[2] << "/" << rayon << ") d=" << distance << std::endl;
  
  return true; /* la localisation est dans le cylindre.*/
}


/*******************************************************************************
 * Verifie si la position donnee en parametre (x,y, z) est dans la zone 
 * determinee par le cylindre. Si mute est vrai alors on affiche pas toutes les 
 * infos.
 * Le parametre bottom donne le plan inferieur (selon y) tandis que hauteur 
 * donne le plan superieur.
 * return    true si vrai
 *           false sinon
/******************************************************************************/
bool Cylindre::estDansCylindreDebug(float x, float y, float z)
{
  bool testY=false;
  float distance=-1;
#ifdef DEBUG
  std::cout << "les parametres sont : x:" << x << ", y:" << y << ", z:" << z << ", centre=" << centre[2] << ", hauteur=" << hauteur << std::endl;
#endif
    
  if(z < centre[2] || z > hauteur+centre[2])
  {
    std::cout<<"Cylindre '" << name << "': articulation trop haute ou trop basse pour etre dedans ("<<z<<"/"<<hauteur<<")"<<std::endl;
    return false; /* test de Y dit que de toute facon, ce n'est pas dans le cylindre*/
  }
    
    /* verification de la distance par rapport a l'axe du cylindre */
    
  distance=sqrt((x-centre[0])*(x-centre[0]) + (y-centre[1])*(y-centre[1]));
  
  if(distance>rayon)
  {
    std::cout<<"Cylindre '" << name << "': articulation hors du rayon du cylindre ("<<distance<<"/"<<rayon<<")"<<std::endl;
    return false; /* la localisation n'est pas dans le cylindre */
  }
  std::cout << "x:" << x << ", y:" << y << ", z:" << z << "is in Cylindre '" << name << "' (" << centre[2] << "/" << rayon << ") d=" << distance << std::endl;
  
  return true; /* la localisation est dans le cylindre.*/
}


/*******************************************************************************
 * ****************************************************************************/
bool Cylindre::is_activated() {
    return activated;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::set_params(float x, float y, float z, float r, float h)
{
  centre[0] = x;
  centre[1] = y;
  centre[2] = z;
  rayon = r;
  hauteur = h;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::set_center(float x, float y, float z)
{
  centre[0] = x;
  centre[1] = y;
  centre[2] = z;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::set_rayon(float r)
{
  rayon = r;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::set_hauteur(float h)
{
  hauteur = h;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::set_name(char *newname)
{
  strncpy(name, newname, 32*sizeof(char));
}


/*******************************************************************************
 * ****************************************************************************/
char *Cylindre::get_name()
{
  return name;
}


/*******************************************************************************
 * ****************************************************************************/
void Cylindre::display()
{
  std::cout << name << " : (" << centre[0] << "," << centre[1] << "," << centre[2] << ") hight = " << hauteur << " and radius = " << rayon << std::endl;
}
