#------------------------------------------------------------------------------
# File:   Makefile
# Author: Alain Villagrasa (NIP 816787) & Carlos de Vera (NIP 848481),
#		  Programación II. Universidad de Zaragoza.
# Date:   abril 2022
# Coms:   Makefile para el trabajo práctico de la asignatura "Betris".
#------------------------------------------------------------------------------

#-----------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -I. -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: mainB
#-----------------------------------------------------------
# Compilacion
mainB.o: mainB.cpp
	${CC} -c mainB.cpp ${CPPFLAGS}
# Linkado
mainB: mainB.o betris.o
	${CC} mainB.o betris.o -o mainB ${LDFLAGS}
maxsolape.o: betris.cpp betris.hpp
	${CC} -c betris.cpp ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. 
# Nota: se borrarán los siguentes archivos sin preguntar
clean:
	${RM} betris.o mainB.o mainB

