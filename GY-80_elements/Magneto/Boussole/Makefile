CPP=g++    #Commande du compilateur
CFLAGS=-O3 #Option d'optimisation du programme
LDFLAGS=-lSDL -lSDL_mixer #Linker

all: Point clean

	
####################################################################	
	
	
Point: Draw.o Point.o key.o dessin.o Enregistrement.o affichestruct.o Affiche.o Mag.o Koelis.h Draw.hpp
	${CPP} $(CFLAGS) -g -Wall -o Point Point.o key.o dessin.o Enregistrement.o Mag.o affichestruct.o Affiche.o Draw.o ${LDFLAGS} -lGLU -lglut -lGL -lserial -lstdc++

Point.o: Point.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o Point.o -c Point.cpp

key.o: key.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o key.o -c key.cpp

dessin.o: dessin.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o dessin.o -c dessin.cpp
	
Enregistrement.o: Enregistrement.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o Enregistrement.o -c Enregistrement.cpp

Affiche.o: affiche.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o Affiche.o -c affiche.cpp

affichestruct.o: Struct.cpp Koelis.h
	${CPP} $(CFLAGS) -g -Wall -o affichestruct.o -c Struct.cpp
	
Mag.o : Magnetometre.cpp Magnetometre.hpp
	${CPP} $(CFLAGS) -g -Wall -o Mag.o -c Magnetometre.cpp
	

clean:	
	rm -fr *.o
	rm -fr *~

mrproper: clean
	rm -fr Point
