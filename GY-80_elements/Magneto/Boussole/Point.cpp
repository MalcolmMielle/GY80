#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SerialStream.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Koelis.h"

Point3d Pos_point;
Point3d posCam;
DATA Data;
float teta,phi,r,phi_objet,teta_objet;
Point3d_l* Carte=NULL;
int alerte=0;
int List_Object=1;
int flag_total;
int flag_option=0;

	
Magnetometre mag;
//Serial serial;

int main(int argc, char *argv[])
{
	//Initialisaion des points de bases
	Data.nb_mesure=0;
	teta = 0;
	phi = 0;
    	r = 20;
    	phi_objet=0;
    	teta_objet=0;

	posCam.x = r*cos(teta)*cos(phi);
    	posCam.y = r*sin(teta)*cos(phi) ;
    	posCam.z = r*sin(phi);
    	
    	printf("Voulez-vous enregistrer tous les points ? Entrez 0 si non, n'importe quel autre chiffre pour oui.\n");
    	scanf("%d",&flag_total);

	//Initialisation Du fichier de sauvegarde.
	FILE* f;
	f=fopen("Carte.txt","w+");
	printf("Reinitai\n");
	fclose(f);
	
	
	//Initialisation !
	glutInit(&argc, argv); //Init de la fenêtre
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Double Buffer et Couleur et buffer de profondeur
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Positionne tes points !"); //Nom de la fenêtre
	
	//Activation de la profondeur.
	glMatrixMode(GL_PROJECTION); //Définit le type de la pile de matrice
	glLoadIdentity(); //Fixe la matrice dans la pile de matrice
	gluPerspective(45,1,0.5,100);//Angle de vueen y, ratio longueur largeur en x, jusqu'ou un objet proche est visible, idem loin
	glEnable(GL_DEPTH_TEST); //Activation de la profondeur
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//Init des tampons d'affichage et de profondeur
	
	//Activation de l'arduino

	
	
	
	CreateList();
	
	
	glutIdleFunc(Dessin);
	glutKeyboardFunc(keyboard);//Fonction principale clavier
	glutDisplayFunc(Dessin); //Fonction principale de dessin
	glutMainLoop(); //Boucle de traitement

	
}
	
