#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Draw.hpp"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



typedef struct POINT3D
{
 float x,y,z;
}Point3d; 

/*******Fonction prototype*******/
void keyboard(unsigned char key, int x, int y); /* Gestion du clavier */
void MyDisplayFunction();  
void dessin();
/********************************/
/*****Variable*****/
Point3d pCam;
Point3d pos;

float teta,phi,r,h,l,k;
double deg1, deg2;
float lx=0, ly=3.14159/4, lz;
float l1, l2;

Draw drawing;

/******************/






/***********Fonction principale**************/
int main(int argc, char *argv[])
{
	r=2.0;
	l=1.0;
	k=5.0;
	teta=0;
	h=3;
	phi=3.14159/4.;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

   
	// Diverses initialisations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	  
	// Creation de la fenetre
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Projet Koelis");

	// On active la gestion du tampon de profondeur
	glMatrixMode(GL_PROJECTION); //On active le projection et on met la perspective
	glLoadIdentity();
	gluPerspective(45., 1, 0.5,100);
	
	glEnable(GL_DEPTH_TEST);
	    // Definition de la fonction d'affichage
	glutDisplayFunc(MyDisplayFunction);
	    // Definition de la fonction de gestion des évènement clavier
	glutKeyboardFunc(keyboard);

	    // Boucle de traitement
	glutMainLoop();
}




/**********Gestion du Clavier************/
void keyboard(unsigned char key, int x, int y)
{    

 	switch(key)
    	{

    		case ('x'):
		printf("touche x\n");
		pos.x=pos.x+0.05;		 
		glutPostRedisplay();
      		break;

    		case 'y':
		printf("touche y\n");
		pos.y=pos.y+0.05;
		glutPostRedisplay();
     		break;

    		case 'z':
    		printf("touche z\n");
		pos.z=pos.z+0.05;
		glutPostRedisplay();
      		break;
      		
      		case ('c'):
		printf("touche c\n");
		pos.x=pos.x-0.05;		 
		glutPostRedisplay();
      		break;

    		case 'u':
		printf("touche u\n");
		pos.y=pos.y-0.05;
		glutPostRedisplay();
     		break;

    		case 'e':
    		printf("touche e\n");
		pos.z=pos.z-0.05;
		glutPostRedisplay();
      		break;
      		
      		case 'q':
      		exit(0);
      		break;
      		
      		
     	}

}


/*********Fonction d'affichage ***********/
void MyDisplayFunction()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	pCam.x = 3;
	pCam.y = 3;
	pCam.z = 3;
	gluLookAt(pCam.x, pCam.y, pCam.z, 0, 0, 0.0, 0.0, 0.0, 1.0);


	glPushMatrix();

	//dessine ici
	
	//dessin();
   	drawing.draw();
  
	//fin du dessin
	
	glPopMatrix();
	glutSwapBuffers() ;
}


/*********DESSIN******/

void dessin()
{
		
	glColor3ub(255,255,255);
  	glBegin(GL_QUADS);
  	glVertex3f( 1+pos.x,1+pos.y,1+pos.z);
  	glVertex3f( 1+pos.x,1+pos.y,pos.z);
  	glVertex3f( pos.x,1+pos.y,pos.z);
  	glVertex3f( pos.x,1+pos.y,1+pos.z);  
	
	glColor3ub(255,0,0);	
  	glVertex3f( pos.x,pos.y,pos.z);
  	glVertex3f( pos.x,pos.y,1+pos.z);
  	glVertex3f( pos.x,1+pos.y,1+pos.z);
  	glVertex3f( pos.x,1+pos.y,0+pos.z);

	glColor3ub(0,255,0);  	
  	glVertex3f( pos.x,pos.y,pos.z);
  	glVertex3f( pos.x,pos.y,1+pos.z);
  	glVertex3f( 1+pos.x,pos.y,1+pos.z);
  	glVertex3f( 1+pos.x,pos.y,pos.z);

  	glColor3ub(0,0,255);  	
  	glVertex3f( 1+pos.x,pos.y,1+pos.z);
  	glVertex3f( 1+pos.x,pos.y,pos.z);
  	glVertex3f( 1+pos.x,1+pos.y,pos.z);
  	glVertex3f( 1+pos.x,1+pos.y,1+pos.z);
  	glEnd();

	

/*	glColor3ub(255,0,255);
	glTranslatef(0,0,1.5);
	GLUquadric* soleil;
	soleil = gluNewQuadric();
	gluQuadricDrawStyle(soleil,GLU_FILL);
	gluSphere(soleil,0.5,20,20);
	gluDeleteQuadric(soleil);
	glTranslatef(0,0,-1.5);
	
	
	//REPERE
	glColor3ub(255,0,255); 
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
  	glVertex3f(1,0,0);
	
	glVertex3f(0,0,0);
  	glVertex3f(0,1,0);

	glBegin(GL_LINES);
	glVertex3f(0,0,0);
  	glVertex3f(0,0,1);
	glEnd();*/
}
