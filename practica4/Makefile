#------------------------------------------------------------------------------
# File:   Makefile
# Author: Alain Villagrasa
# Date:   abril 2022
# Coms:   Makefile para la práctica 4 de Programación II
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -I. -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: costemsolape
#-----------------------------------------------------------
# Compilacion
costemsolape.o: costemsolape.cpp
	${CC} -c costemsolape.cpp ${CPPFLAGS}
# Linkado
costemsolape: costemsolape.o maxsolape.o
	${CC} costemsolape.o maxsolape.o -o costemsolape ${LDFLAGS}
maxsolape.o: maxsolape.cpp maxsolape.hpp
	${CC} -c maxsolape.cpp ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} maxsolape.o costemsolape.o costemsolape

