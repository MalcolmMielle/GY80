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

void keyboard(unsigned char key, int x, int y)
{    

	if(key== 'q'){
	glDeleteLists(List_Object,1);
	exit(0);
	}

	else if(key=='0'){
	//      	printf("touche 0\n");
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
	}

	else if(key=='2'){

	phi=phi-0.1;
	//		printf("touche 2et %f\n",phi);
	glutPostRedisplay();
	}

	else if(key=='8'){
	//		printf("touche 8\n");
	phi=phi+0.1;
	glutPostRedisplay();
	}

	else if(key=='4'){
	//		printf("touche 4\n");
	teta-=0.1;
	glutPostRedisplay();
	}

	else if(key=='6'){
	//		printf("touche 6\n");
	teta+=0.1;
	glutPostRedisplay();
	}

	else if(key=='+'){
	//		printf("touche +\n");
	r-=0.1;
	glutPostRedisplay();
	}

	else if(key=='-'){
	//		printf("touche -\n");
	r+=0.1;
	glutPostRedisplay();
	}

	else{
	glutPostRedisplay();
	}

}
