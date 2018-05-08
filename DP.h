/*default header file. 
Declare functions used by the program as well as global definitions 


2018 Tore Sæterdal*/

#include<stdio.h>
#include <phidget22.h>
#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>
#include <ctype.h>

//PID- gain parameters
#define KP 1
#define KI 1
#define KD 1

typedef enum{true,false} bool;




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
void printFile(void);

void connectPhidgets(PhidgetRCServoHandle motorCh1);
void disconnectPhidgets(PhidgetRCServoHandle motorCh);
void setMotorSpeed(double ctrl_input);
int startmotor(void);

static void CCONV onAttachedMotorHandler(PhidgetHandle phid, void *ptr);
static void CCONV onDetachedMotorHandler(PhidgetHandle phid, void *ptr);
static void CCONV ssleep(int seconds);
static void CCONV motorErrorHandler(PhidgetHandle phid, void *ptr, Phidget_ErrorEventCode errorCode, const char *errorString);
static void CCONV onPositionChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double position);
static void CCONV onVelocityChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double velocity);
static void CCONV onTargetPositionReachedHandler(PhidgetRCServoHandle motorCh, void *ctx, double position);


float computeControlInput(float pos,float ref,float dt);
float timedifference_msec(struct timeval t0, struct timeval t1);