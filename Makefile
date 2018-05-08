
BIN=DP
SRCS=main.c PIDcontrol.c phidgetsHandler.c gnuPlotter.c ../Common/PhidgetHelperFunctions.c
LIBS=-lphidget22
LIBDIR=
INCDIR=-I../Common

CFLAGS=-ggdb3 -Wall -Wno-unused-function

all:
	${CC} ${CFLAGS} -o ${BIN} ${SRCS} ${INCDIR} ${LIBDIR} ${LIBS}
