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
#define KP -4
#define KI 0
#define KD 0

typedef enum{true,false} bool;




//Define pool size 
#define Plength 60 


//maximum runtime for test
#define maxTime 20000

//the potmeter reads 5 V at rest, set origin here
#define maxpos 60.0
#define minpos 0.0
#define minvolt 3.7
#define maxvolt 5.0

//Define physical size of boat.
#define boatLength 100
#define boatWidth 30
#define boatHeight 40


FILE openFile(char selectType);

void closeFiles(FILE fp);
void runDPloop(PhidgetRCServoHandle motorCh,float reference,PhidgetVoltageInputHandle ioCh,FILE *gnuptr);
void printFile(void);

PhidgetRCServoHandle connectPhidgets(PhidgetRCServoHandle motorCh1);
void disconnectPhidgets(PhidgetRCServoHandle motorCh);
void disconnectIOPhidget(PhidgetVoltageInputHandle ioCh);
void setMotorSpeed(double ctrl_input);
PhidgetVoltageInputHandle connectIO(PhidgetVoltageInputHandle ioCh);

static void CCONV onAttachedMotorHandler(PhidgetHandle phid, void *ptr);
static void CCONV onDetachedMotorHandler(PhidgetHandle phid, void *ptr);
static void CCONV ssleep(int seconds);
static void CCONV motorErrorHandler(PhidgetHandle phid, void *ptr, Phidget_ErrorEventCode errorCode, const char *errorString);
static void CCONV onPositionChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double position);
static void CCONV onVelocityChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double velocity);
static void CCONV onTargetPositionReachedHandler(PhidgetRCServoHandle motorCh, void *ctx, double position);


static void CCONV onAttachedIOHandler(PhidgetHandle ioCh,void *ptr);
static void CCONV onDetachedIOHandler(PhidgetHandle ioCh, void *ptr);
static void CCONV onErrorIOHandler(PhidgetHandle ioCh, void *ptr, Phidget_ErrorEventCode errorCode, const char *errorString);
static void CCONV onVoltageChangeHandler(PhidgetVoltageInputHandle ioCh, void *ptr, double voltage);
static PhidgetReturnCode CreateVoltageInput(PhidgetVoltageInputHandle *ioCh);
static PhidgetReturnCode SetVoltageHandler(PhidgetVoltageInputHandle ioCh, PhidgetVoltageInput_OnVoltageChangeCallback fptr);
double getPosition(PhidgetVoltageInputHandle ioCh);

float computeControlInput(float pos,float ref,float dt);
float timedifference_msec(struct timeval t0, struct timeval t1);