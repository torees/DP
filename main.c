#include <stdio.h>
#include <stdlib.h>
#include "DP.h"

#include <phidget22.h>


int main(){
	
	printf("Main running\n" );
	printf("Opening output files..\n" );
	//Open up output files. Stop the program if the open-action fails
	FILE *input = fopen("input.dat","w");
	FILE *position = fopen("position.dat","w");
	if ((input == NULL) || (position == NULL)){
		printf("The output files could not be opened. Exiting program..");
		exit(0);

	}

	//connect to the Phidget units(motor and interface kit)

	connectPhidgets();

	//Get user input for reference position in pool

	float reference = 0.0;
	printf("Select desired position between 20 and 180\n");
	scanf("%f",&reference);
	while ((reference<20)|| (reference>180)){//((reference <= 20) || (reference>=180)){
		printf("Please enter a valid position\n");
		scanf("%f",&reference);
	}

	//Run dynamic positioning to reference

	runDPloop(reference);

	//Finish program and shut down connections. Save data files. 


	disconnectPhidgets();
	fclose(input);
	fclose(position);
	printf("Closing down DP. Thank you.\n");

	return 0;
}