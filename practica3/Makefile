#------------------------------------------------------------------------------
# File:   Makefile
# Author: Alain Villagrasa
# Date:   abril 2022
# Coms:   Makefile para la práctica 3 de Programación II
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -I. -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: calmsolape
#-----------------------------------------------------------
# Compilacion
calmsolape.o: calmsolape.cpp
	${CC} -c calmsolape.cpp ${CPPFLAGS}
# Linkado
calmsolape: calmsolape.o maxsolape.o
	${CC} calmsolape.o maxsolape.o -o calmsolape ${LDFLAGS}
maxsolape.o: maxsolape.cpp maxsolape.hpp
	${CC} -c maxsolape.cpp ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} maxsolape.o calmsolape.o calmsolape

