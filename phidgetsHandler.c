#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>
#include <ctype.h>
#include "DP.h"

/*
Connect and initialize Phidgets units needed for the project boat.
Utlizing built-in functions from the libphidgets library downloaded from https://www.phidgets.com/
Following the programming methodology of https://www.phidgets.com/docs/Phidget_Programming_Basics

Functions:

Variables:
*/



static void CCONV ssleep(int seconds) {
	sleep(seconds);
}


static void CCONV onAttachedMotorHandler(PhidgetHandle phid, void *ptr){
	PhidgetReturnCode res;
	int hubPort;
	int channel;
	int serial;

	res = Phidget_getDeviceSerialNumber(phid, &serial);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get device serial number\n");
		return;
	}

	res = Phidget_getChannel(phid, &channel);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get channel number\n");
		return;
	}

	res = Phidget_getHubPort(phid, &hubPort);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get hub port\n");
		hubPort = -1;
	}

	if (hubPort == -1)
		printf("channel %d on device %d attached\n", channel, serial);
	else
		printf("channel %d on device %d hub port %d attached\n", channel, serial, hubPort);
}

static void CCONV onDetachedMotorHandler(PhidgetHandle phid, void *ptr) {
	PhidgetReturnCode res;
	int hubPort;
	int channel;
	int serial;

	res = Phidget_getDeviceSerialNumber(phid, &serial);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get device serial number\n");
		return;
	}

	res = Phidget_getChannel(phid, &channel);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get channel number\n");
		return;
	}

	res = Phidget_getHubPort(phid, &hubPort);
	if (res != EPHIDGET_OK)
		hubPort = -1;

	if (hubPort != -1)
		printf("channel %d on device %d detached\n", channel, serial);
	else
		printf("channel %d on device %d hub port %d detached\n", channel, hubPort, serial);
}

static void CCONV motorErrorHandler(PhidgetHandle phid, void *ptr, Phidget_ErrorEventCode errorCode, const char *errorString) {

	printf("Error somewhere");
}



void setMotorSpeed(double ctrl_input){
	//PhidgetRCServo_setTargetPosition(motorCh,ctrl_input);
	return;
}


static void CCONV onPositionChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double position) {

	printf("Position change \n");
}
static void CCONV onVelocityChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double velocity) {

	printf("Velocity change\n");
}

static void CCONV onTargetPositionReachedHandler(PhidgetRCServoHandle motorCh, void *ctx, double position) {

	printf("Reached target pos\n");
}

void connectPhidgets(PhidgetRCServoHandle motorCh){
	

	PhidgetReturnCode res;
	
	//create motor channel
	res =PhidgetRCServo_create(&motorCh);
	if(res != EPHIDGET_OK){
		printf("Could not create motor channel\n");
	}
	//Set handlers for attach, detach and error
	res = Phidget_setOnAttachHandler((PhidgetHandle)motorCh,onAttachedMotorHandler,NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set attach handler\n");
	}

	res = Phidget_setOnDetachHandler((PhidgetHandle)motorCh,onDetachedMotorHandler,NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set detach handler\n");
	}
	res = Phidget_setOnErrorHandler((PhidgetHandle)motorCh, motorErrorHandler, NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set error handler\n");
	}
	//set change handlers
	res = PhidgetRCServo_setOnPositionChangeHandler(motorCh, onPositionChangeHandler, NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set position change handler\n");
	}
	res = PhidgetRCServo_setOnVelocityChangeHandler(motorCh, onVelocityChangeHandler, NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set velocity change handler\n");
	}
	res = PhidgetRCServo_setOnTargetPositionReachedHandler(motorCh, onTargetPositionReachedHandler, NULL);
	if(res != EPHIDGET_OK){
		printf("Could not set position reached handler\n");
	}

	//open motor channel, try for 5000 ms
	res = Phidget_openWaitForAttachment((PhidgetHandle)motorCh, 5000);
	if(res != EPHIDGET_OK){
		if (res == EPHIDGET_TIMEOUT) {
			printf("TIMEOUT:\n");
			exit(0);
		} else {printf("Could not open motor channel\n Shutting down..");
		}
		
		
	}
	ssleep(2);
	printf("Setting target position to 90\n");
	res = PhidgetRCServo_setTargetPosition(motorCh, 90);
	if(res != EPHIDGET_OK){
		printf("Could not set target position\n");
		
	}
	res = PhidgetRCServo_setEngaged(motorCh, 1);
	if(res != EPHIDGET_OK){
		printf("Could not engage motor\n");
		
	}
	printf("Setting Target Position to 0 for 5 seconds...\n");
	res=PhidgetRCServo_setTargetPosition(motorCh, 0);
	if(res != EPHIDGET_OK){
		printf("Could not set target position\n");
		
	}
	ssleep(5);

	printf("Motor ready...\n");
	
	

}



void disconnectPhidgets(PhidgetRCServoHandle motorCh){

	//Phidget_close((PhidgetHandle)ioCh);
 	//Phidget_release((PhidgetHandle *)&ioCh);

 	Phidget_close((PhidgetHandle)motorCh);
 	PhidgetRCServo_delete(&motorCh);

}