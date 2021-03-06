#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Koelis.h"

void CreateList()
{
	glNewList(List_Object, GL_COMPILE); //Crée une liste qu'on peut directement appeller
		glBegin(GL_LINES);
			glColor3ub(0,255,0); //Parce qu'on utilise la bibliothèque Glu
		  	glVertex3f(0,0,0);
		  	glVertex3f(0,0,3);
		  	glColor3ub(255,0,0); 
		  	glVertex3f(0,0,0);
		  	glVertex3f(0,3,0);
		  	glColor3ub(255,0,0); 
		  	glVertex3f(0,0,0);
		  	glVertex3f(3,0,0);
		
		glEnd();
	glEndList();

}

void Capteur()
{

float headWidth = 1;
  float headLength = 1;
  
  glPushMatrix();
  
  // Draw base
  /*glTranslatef(0, 0, -100);
  box(100, 100, 200);*/
  
  // Draw pointer
  glRotatef(mag.heading, 1, 0, 0);
  glTranslatef(-headWidth/2, -2, -4);
  glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0 ,0);
    glVertex3f(0, 1, 0);
    glVertex3f(headWidth, 0 ,0);
    glVertex3f(headWidth, 1, 0);
    glVertex3f(headWidth/2, 0, -headLength);
    glVertex3f(headWidth/2, 1, -headLength);
    glVertex3f(0, 0 ,0);
    glVertex3f(0, 1, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(headWidth, 0, 0);
    glVertex3f(headWidth/2, 0, -headLength);
    glVertex3f(0, 1, 0);
    glVertex3f(headWidth, 1, 0);
    glVertex3f(headWidth/2, 1, -headLength);
  glEnd();
  
  glPopMatrix();
}

Point3d DefinePoint(Point3d Point, float r, float ajout_phi, float ajout_teta)
{
	//Point.x = r*cos(teta_objet+ajout_teta)*cos(phi_objet+ajout_phi);
	//Point.y = r*sin(teta_objet+ajout_teta)*cos(phi_objet+ajout_phi);
	//Point.z = r*sin(phi_objet+ajout_phi);
	
	Point.x=r*cos(90+mag.heading+ajout_phi);
	Point.y=r*sin(90+mag.heading+ajout_phi);
	Point.z=0;
	
	return Point;
		
}



void Dessin()
{
	printf("Fonction de dessin\n");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Init des tampons d'affichage et de profondeur
	glMatrixMode(GL_MODELVIEW); //
	glLoadIdentity(); //Nouvelle matrice sur la pile.
	
	/******************************************Position de la caméra****************************************/
	if(phi>3.14159)
	{
		phi=phi-3.14159;
	}
	
	posCam.x = r*cos(teta)*cos(phi);
	posCam.y = r*sin(teta)*cos(phi);
	posCam.z = r*sin(phi);
	//printf("On a %f %f %f et phi %f teta %f\n",posCam.x,posCam.y,posCam.z, phi, teta);
	
	gluLookAt(posCam.x+0.5,posCam.y+0.5,posCam.z+0.5,0,0,0,0,0,1);//Point de vue : eyes : x,y,z, cente image : x,y,z direction de 'z' (vecteur up) x,y,z)
	
	/****************************************Position du point************************************************/
	//Dessine des lignes
	if(flag_option!=1)
	{
		printf("getin\n");
  		Pos_point.x=2*(cos(phi_objet)*cos(teta_objet));
  		Pos_point.y=2*(cos(phi_objet)*sin(teta_objet));
  		Pos_point.z=2*(sin(phi_objet));	
  	}
  	else
  	{
  		flag_option=0;
  		/**Rajouter une résolution inverse afin de redémarrer la scène à ce point**/
  	}
  	
  	/****************************************Dessin du capteur*****************************************************/
	Capteur();
	std::cout << "Debut..." <<std::endl;
	mag.readHeadAll();
	//std::string str;
	//serial.recv(str, 1000, 1000);
	std::cout << "End..." <<std::endl;
	/****************************************Dessin du repère******************************************************/
	glCallList(List_Object);
	
	/****************************************Partie option et flags************************************************/
	if(alerte==1)
	{
		Affiche();
	}	
	
	if (flag_total!=0)
	{
		Enreg();
	}
	
	
	glFlush();
	//Fin du dessin
	glPopMatrix();
	glutSwapBuffers() ;

}
