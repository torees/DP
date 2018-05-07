#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>
#include <ctype.h>


/*
Connect and initialize Phidgets units needed for the project boat.
Utlizing built-in functions from the libphidgets library downloaded from https://www.phidgets.com/
Following the programming methodology of https://www.phidgets.com/docs/Phidget_Programming_Basics

Functions:

Variables:
*/

//We will use the servo motor and the phidget interface kit
static PhidgetRCServoHandle motorCh;
static PhidgetVoltageInputHandle ioCh; //in Phidgets 22, the part of the 
	//interface kit we need is referenced DigitalInput

void onAttachedMotorHandler(PhidgetHandle motorCh, void *userPtr){
	printf("Motor connected\n");
	//Enable motor
	
	

	//Control the motor
}
void onAttachedIOHandler(PhidgetHandle ch, void *userPtr){
	printf("Interface card connected\n");
	//Read from the interface
	PhidgetRCServo_setEngaged(motorCh,1);
}

double getBoatPos(void){
	double pos;
	PhidgetVoltageInput_getSensorValue(ioCh,&pos);
	return pos;

}

void setMotorSpeed(double ctrl_input){
	PhidgetRCServo_setTargetPosition(motorCh,ctrl_input);
	return;
}


void connectPhidgets(){
	


	//create interface objects and open them
	PhidgetVoltageInput_create(&ioCh);
	PhidgetRCServo_create(&motorCh);

	Phidget_open((PhidgetHandle) ioCh); 
	Phidget_open((PhidgetHandle) motorCh); 

	Phidget_setOnAttachHandler((PhidgetHandle)ioCh,onAttachedIOHandler,NULL);
	Phidget_setOnAttachHandler((PhidgetHandle)motorCh,onAttachedMotorHandler,NULL);
	//PhidgetRCServo_setEngaged(motorCh,1);
	
}



void disconnectPhidgets(){

	Phidget_close((PhidgetHandle)ioCh);
 	Phidget_release((PhidgetHandle *)&ioCh);

 	Phidget_close((PhidgetHandle)motorCh);
 	Phidget_release((PhidgetHandle *)&motorCh);

}