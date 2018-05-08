#include <stdio.h>
#include <stdlib.h>
#include "DP.h"

#include <phidget22.h>

/*
main file. Declare datafiles and Phidget handles. 
Get input from user and start control loop.
Call plotting functions after run
Close open files and call disconnecting functions for Phidgets

2018 Tore Sæterdal
*/

int main(){
	FILE *input;
	FILE *position;
	FILE *target;
	FILE *gnuPlot;
	
	printf("Main running\n" );
	printf("Opening output files..\n" );
	//Open up output files. Stop the program if the open-action fails
	input = fopen("input.dat","w");
	position = fopen("position.dat","w");
	target = fopen("target.dat","w");
	gnuPlot = fopen("gnu.dat","w");
	if ((input == NULL) || (position == NULL) || (gnuPlot == NULL)){
		printf("The output files could not be opened. Exiting program..");
		exit(0);

	}
	//Create Phidget handles
	PhidgetRCServoHandle motorCh;
	PhidgetVoltageInputHandle ioCh;
	//

	
	//connect to the Phidget units(motor and interface kit)
	printf("Connecting Phidgets\n");
	motorCh=connectMotorPhidget(motorCh);
	ioCh = connectIO(ioCh);
	
	//Get user input for reference position in pool

	float reference = 0.0;
	
	//printFile();
	printf("Select desired position between 0 and 60\n-1 to abort\n");
	//scanf("%f",&reference);
	reference = 30;
	if(reference == -1){
		disconnectMotorPhidget(motorCh);
		disconnectIOPhidget(ioCh);
		exit(0);
	}
	while ((reference<0)|| (reference>maxpos)){//((reference <= 20) || (reference>=180)){
		printf("Please enter a valid position\n");
		scanf("%f",&reference);
	}

	//Run dynamic positioning to reference
	
	
	runDPloop(motorCh,reference,ioCh,gnuPlot);
	disconnectMotorPhidget(motorCh);
	disconnectIOPhidget(ioCh);
	
	//Finish program and shut down connections. Save data files. 


	
	fclose(input);
	fclose(position);
	fclose(target);
	fclose(gnuPlot);
	plotGNUposition();
	plotGNUcontrol();
	printf("Closing down DP. Thank you.\n");

	return 0;
}