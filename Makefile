
BIN=DP
SRCS=main.c outputHandler.c PIDcontrol.c phidgetsHandler.c
LIBS=-lphidget22
LIBDIR=
INCDIR=

CFLAGS=-ggdb3 -Wall

all:
	${CC} ${CFLAGS} -o ${BIN} ${SRCS} ${INCDIR} ${LIBDIR} ${LIBS}
