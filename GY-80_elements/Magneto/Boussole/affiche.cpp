#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Koelis.h"

void Affiche()
{
	printf("Affichage !\n");	
	affichestruct(Carte);

	Point3d_l* Carte2 = Carte;
	if(Carte!=NULL)
	{
		while(Carte2->next!=NULL)
		{
			printf("\nJe souhaiterais dessiner\n");

			glBegin(GL_LINES);
			glVertex3f(Carte2->x,Carte2->y,Carte2->z);
			glVertex3f(Carte2->next->x,Carte2->next->y,Carte2->next->z);
			glEnd();	
			Carte2=Carte2->next;

		}
	}
	
	//Version lu dans le fichier est 1.5 fois plus grande
	
	FILE* f;
	float Tab[6];
	int i;
	f=fopen("Carte.txt","r");
	fscanf(f,"%f %f %f %f %f %f",Tab+0,Tab+1,Tab+2,Tab+3,Tab+4,Tab+5);
	printf("Deuxième dessin %f %f\n",Tab[0],Tab[1]);
	glColor3ub(0,0,255);
	glBegin(GL_LINES);
	glVertex3f(1.5*Tab[0],1.5*Tab[1],1.5*Tab[2]);
	glVertex3f(1.5*Tab[3],1.5*Tab[4],1.5*Tab[5]);
	glEnd();
	for(i=0;i<3;i++)
	{
		Tab[i]=Tab[i+3];
	}	
	while(feof(f)==0)
	{
		fscanf(f,"%f %f %f",Tab+3,Tab+4,Tab+5);
		printf("Deuxième dessin %f %f\n",Tab[0],Tab[1]);
		glBegin(GL_LINES);
		glVertex3f(1.5*Tab[0],1.5*Tab[1],1.5*Tab[2]);
		glVertex3f(1.5*Tab[3],1.5*Tab[4],1.5*Tab[5]);
		glEnd();
		for(i=0;i<3;i++)
		{
			Tab[i]=Tab[i+3];
		}	
	}
	
	
	
	alerte=0;

}
