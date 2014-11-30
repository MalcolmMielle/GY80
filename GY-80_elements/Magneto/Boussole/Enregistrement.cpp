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

void Enreg()
{
	FILE* f;
	f=fopen("Carte.txt","a");
	Carte=ajoutPoint3d_l(Carte,f);
	fprintf(f,"%f %f %f\n",Pos_point.x,Pos_point.y,Pos_point.z);
	Data.nb_mesure=Data.nb_mesure+1;
	printf("On possède %d mesures\n", Data.nb_mesure);
	affichestruct(Carte);
	fclose(f);
}

void Option()
{
	printf("Voici, les options:\nVous pouvez choisir de positionner la sonde a une place de votre choix => tapez 1\n");
	scanf("%d",&flag_option);
	if (flag_option==1)
	{
		int x,y,z;
		printf("Entrez la position en X");
		scanf("%d",&x);
		Pos_point.x=x;
		printf("Entrez la position en Y");
		scanf("%d",&y);
		Pos_point.y=y;
		printf("Entrez la position en Z");
		scanf("%d",&z);
		Pos_point.z=z;
	}
}
