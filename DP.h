/*default header file. 
Declare functions used by the program as well as global definitions 


2018 Tore Sæterdal*/

#include<stdio.h>
#include <phidget22.h>

//PID- gain parameters
#define KP 1
#define KI 1
#define KD 1

typedef enum{true,false} bool;

//log files for saving data
static FILE *input;
static FILE *position;
static FILE *target;


//Define pool size (no need for depth)
#define Plength 280 
#define Pwidth 80

//maximum runtime for test
#define maxTime 20000

//Define physical size of boat.
#define boatLength 100
#define boatWidth 30
#define boatHeight 40


FILE openFile(char selectType);

void closeFiles(FILE fp);
void runDPloop(float reference);

void connectPhidgets();
void disconnectPhidgets();
double getBoatPos(void);
void setMotorSpeed(double input);

void onAttachedMotorHandler(PhidgetHandle ch, void *userPtr);
void onAttachedIOHandler(PhidgetHandle ch, void *userPtr);

float computeControlInput(float pos,float ref,float dt);
float timedifference_msec(struct timeval t0, struct timeval t1);