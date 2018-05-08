
BIN=DP
SRCS=main.c outputHandler.c PIDcontrol.c phidgetsHandler.c printValues.c ../Common/PhidgetHelperFunctions.c
LIBS=-lphidget22
LIBDIR=
INCDIR=-I../Common

CFLAGS=-ggdb3 -Wall -Wno-unused-function

all:
	${CC} ${CFLAGS} -o ${BIN} ${SRCS} ${INCDIR} ${LIBDIR} ${LIBS}
