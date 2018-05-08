#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>
#include <ctype.h>
#include "DP.h"
#include "PhidgetHelperFunctions.h"

/*
Connect and initialize Phidgets units needed for the project boat.
Utlizing built-in functions from the libphidgets library downloaded from https://www.phidgets.com/
Following the programming methodology of https://www.phidgets.com/docs/Phidget_Programming_Basics

2018 Tore Sæterdal
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
		printf("Could not get serial number\n");
		
	}

	res = Phidget_getChannel(phid, &channel);
	if (res != EPHIDGET_OK) {
		printf("Could not get channel number\n");
		
	}

	res = Phidget_getHubPort(phid, &hubPort);
	if (res != EPHIDGET_OK) {
		printf("Could not get hub port\n");
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

	printf("Error in motor");
}


static void CCONV onPositionChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double position) {

	
}
static void CCONV onVelocityChangeHandler(PhidgetRCServoHandle motorCh, void *ctx, double velocity) {

	
}

static void CCONV onTargetPositionReachedHandler(PhidgetRCServoHandle motorCh, void *ctx, double position) {

	
}

PhidgetRCServoHandle connectMotorPhidget(PhidgetRCServoHandle motorCh){
	
	//Use res variable to determine if all actions succeed
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
			printf("TIMEOUT attaching motor\n");
			
		} else {
			printf("Could not open motor channel\n Shutting down..");

		}
		exit(0);	
		
	}

	ssleep(2);
	//Set the servo to 90 before engaging
	printf("Initializing motor\n");
	res = PhidgetRCServo_setTargetPosition(motorCh, 90);
	if(res != EPHIDGET_OK){
		printf("Could not initialize motor\n");
		
	}
	res = PhidgetRCServo_setEngaged(motorCh, 1);
	if(res != EPHIDGET_OK){
		printf("Could not engage motor\n");
		
	}
	
	res=PhidgetRCServo_setTargetPosition(motorCh, 0);
	if(res != EPHIDGET_OK){
		printf("Could not set motor to initial pos\n");
		
	}
	
	

	printf("Motor ready...\n");
	return motorCh;

}

static void CCONV onAttachedIOHandler(PhidgetHandle ioCh,void *ptr){
	PhidgetReturnCode res;
	int channel;
	int serial;
	int datInterval = 20;
	float voltLim = 0.0;

	res = PhidgetVoltageInput_setDataInterval((PhidgetVoltageInputHandle)ioCh, datInterval);
	if (res != EPHIDGET_OK) {
		printf("Could not set data interval\n");
	}

	res = PhidgetVoltageInput_setVoltageChangeTrigger((PhidgetVoltageInputHandle)ioCh, voltLim);
	if (res != EPHIDGET_OK) {
		printf("Could not set voltage trigger limit\n");
	}

	res = Phidget_getDeviceSerialNumber(ioCh, &serial);
	if (res != EPHIDGET_OK) {
		printf("Could not get device serial nr\n");
	}
	res= Phidget_getChannel(ioCh, &channel);
	if (res != EPHIDGET_OK) {
		printf("Could not get channel\n");
	}

}

static void CCONV onDetachedIOHandler(PhidgetHandle ioCh, void *ptr){
	PhidgetReturnCode res;
	int channel;
	int serial;

	res = Phidget_getDeviceSerialNumber(ioCh, &serial);
	if (res != EPHIDGET_OK) {
		printf("Could not get device serial nr\n");
	}
	res= Phidget_getChannel(ioCh, &channel);
	if (res != EPHIDGET_OK) {
		printf("Could not get channel\n");
	}
}

static void CCONV onErrorIOHandler(PhidgetHandle ioCh, void *ptr, Phidget_ErrorEventCode errorCode, const char *errorString){
	printf("Error in IO module\n");
}

static void CCONV onVoltageChangeHandler(PhidgetVoltageInputHandle ioCh, void *ptr, double voltage) {	
}

static PhidgetReturnCode CreateVoltageInput(PhidgetVoltageInputHandle *ioCh){
	PhidgetReturnCode res;
	res =  PhidgetVoltageInput_create(ioCh);
	if (res != EPHIDGET_OK) {
		printf("Could not create voltage input\n");
		return res;
	}
	return EPHIDGET_OK;
}

static PhidgetReturnCode SetVoltageHandler(PhidgetVoltageInputHandle ioCh, PhidgetVoltageInput_OnVoltageChangeCallback ptr){
	PhidgetReturnCode res;
	res= PhidgetVoltageInput_setOnVoltageChangeHandler(ioCh, ptr, NULL);
	if (res != EPHIDGET_OK) {
		printf("Could not set voltage handler\n");
		return res;
	}
	return EPHIDGET_OK;
}

PhidgetVoltageInputHandle connectIO(PhidgetVoltageInputHandle ioCh){
	PhidgetReturnCode res;
	int32_t deviceSerialNumber = 76241;
	res = CreateVoltageInput(&ioCh);
	if (res != EPHIDGET_OK) {
		exit(0);
	}

	
	Phidget_setDeviceSerialNumber((PhidgetHandle)ioCh, deviceSerialNumber);
		
	Phidget_setChannel((PhidgetHandle)ioCh,2);
	

	res = Phidget_setOnAttachHandler((PhidgetHandle)ioCh, onAttachedIOHandler, NULL);
	if (res != EPHIDGET_OK) {
		printf("Could not set IO attach handler\n");
		exit(0);
	}

	res = Phidget_setOnDetachHandler((PhidgetHandle)ioCh, onDetachedIOHandler, NULL);
	if (res != EPHIDGET_OK) {
		printf("Could not set IO detach handler\n");
		exit(0);
	}

	res = Phidget_setOnErrorHandler((PhidgetHandle)ioCh, onErrorIOHandler, NULL);
	if (res != EPHIDGET_OK) {
		printf("Could not set IO error handler\n");
		exit(0);
	}



	SetVoltageHandler(ioCh,onVoltageChangeHandler);

	if (OpenPhidgetChannel_waitForAttach((PhidgetHandle)ioCh, 5000))
	{
		printf("TIMEOUT in waiting for IO channel attachment\n");
		exit(0);
	}

	return ioCh;

}

double getPosition(PhidgetVoltageInputHandle ioCh){
	
	double voltage;
	PhidgetVoltageInput_getVoltage(ioCh,&voltage);
	

	double pos;
	double voltrange = maxvolt-minvolt;
	double rel = maxpos/voltrange;
	pos = (maxvolt - voltage)*rel;
	return pos;
}

void disconnectIOPhidget(PhidgetVoltageInputHandle ioCh){



 	Phidget_close((PhidgetHandle)ioCh);
 	PhidgetVoltageInput_delete(&ioCh);
}

void disconnectMotorPhidget(PhidgetRCServoHandle motorCh){


 	Phidget_close((PhidgetHandle)motorCh);
 	PhidgetRCServo_delete(&motorCh);

}