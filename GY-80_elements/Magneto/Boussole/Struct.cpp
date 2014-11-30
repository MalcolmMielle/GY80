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

Point3d_l* ajoutPoint3d_l(Point3d_l* in,FILE* f) //Ajout des structures couleurs
{
	Point3d_l *nouveau;
	nouveau=(Point3d_l *)malloc(sizeof(Point3d_l));
	nouveau->x=Pos_point.x;
	nouveau->y=Pos_point.y;
	nouveau->z=Pos_point.z;
	nouveau->next=in;
	return nouveau;
}

void affichestruct(Point3d_l* Point1) //Affichage des structures de la liste Ouverte
{
	Point3d_l* val = Point1;
	while(val!=NULL)
	{
		printf("x = %f   ", val->x);
		printf("y = %f", val->y);
		printf("z = %f", val->z);
		printf("Son papa : %p\n", val->next);
//		printf("Le pointeur suivant est %p\n", val);
		val=val->next;
	}
	printf("\n");
}

void freelist(Point3d_l* Point1)
{
	Point3d_l* val = Point1;
	while(Point1!=NULL)
	{
		Point1=Point1->next;
		free(val);
		val=Point1;
	}
}
