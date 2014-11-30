#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Magnetometre.hpp"
#include <SerialStream.h>
//#include "serial.hpp"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef DEF_KOELIS
#define DEF_KOELIS

/*******STRUCTURES*******/

typedef struct POINT3D
{
 float x,y,z;
}Point3d;

struct DATA
{
 int nb_mesure;
};
typedef struct DATA DATA;

struct Point3d_l
{
 float x,y,z;
 struct Point3d_l *next;
};

typedef struct Point3d_l Point3d_l; 

/*******VARIABLE GLOBALES*******/
extern Point3d Pos_point;
extern Point3d posCam;
extern Point3d_l* Carte;
extern float teta,phi,r,phi_objet,teta_objet;
extern int alerte;
extern DATA Data;
extern int List_Object;
extern int flag_total, flag_option;
extern Magnetometre mag;
//extern Serial serial;
extern LibSerial::SerialStream ardu;


/*******FONCTIONS*******/
void CreateList();
void Dessin();
void Enreg();
void keyboard(unsigned char key, int x, int y);
Point3d_l* ajoutPoint3d_l(Point3d_l* in,FILE* f);
void affichestruct(Point3d_l* Point1);
void Affiche();
void freelist(Point3d_l* Point1);
void Capteur();
void Option();
Point3d DefinePoint(Point3d Point, float r, float ajout_phi, float ajout_teta);


#endif
