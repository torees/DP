#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "DP.h"

/*
Main control loop. Runs until the boat is kept within target +- 5 cm for 10 seconds, 
or until 30 seconds of operation. 

Functions:

Variables:



*/


float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

float computeControlInput(float pos,float ref,float dt){
	
	static float prev_pos;
	static float prev_integ;
	float prop;
	float integ;
	float deriv;
	float error = pos-ref;

	//compute control terms of PID

	

	prop = KP*error;

	//the integral term will increase with time, so it need to be kept for each iteration
	integ = prev_integ + KI*error*dt;

	deriv = (pos-prev_pos)/dt;






	prev_integ = integ;
	prev_pos = pos;

	float ctrl_input = prop + integ + deriv;
	//printf("%f\n",ctrl_input );
	//ensure control input is a valid servo position to avoid saturating the motor
	if (ctrl_input<80){ctrl_input=80;}
	if (ctrl_input>125){ctrl_input=125;}



	
	return ctrl_input;


}


void runDPloop(PhidgetRCServoHandle motorCh,float reference,PhidgetVoltageInputHandle ioCh,FILE *gnuptr){
	
	//static float prev_ctrl_input;
	static struct timeval previous_time;
	float dt = 0.020;
	struct timeval tn;
	float elapsed = 0;
	float totaltime = 0;
	bool finished = false;
	float error;
	printf("Starting DP..The controller will run until finished.\nPress 'Ctrl + C' to abort\n");
	
	float counter = 0.0;
	float printcounter = 0.0;
	gettimeofday(&previous_time, 0);
	
	
	float boatPosition = getPosition(ioCh);
	
	//float ctrl_input =computeControlInput(boatPosition,reference,dt);
	//keep while loop until finished or aborted by user
	

	float ctrl_input = 0;
	while(finished == false){
		
		
		gettimeofday(&tn, 0);
   		elapsed = timedifference_msec(previous_time, tn);
   		previous_time = tn;

   		//Every 20 ms, compute new PID input
   		counter += elapsed;
   		printcounter += elapsed;
   		totaltime += elapsed;
   		
   		if(counter >=dt){

   			
   			//Get ship position from IOcard
   			boatPosition = getPosition(ioCh);
   			error = boatPosition - reference;

   			//Compute new input
   			ctrl_input =computeControlInput(boatPosition,reference,dt);

   			//Reset timer
   			counter = 0.0;

   			//print values to file
   			fprintf(gnuptr, "%f %d %f %lf \n",totaltime,0,error,ctrl_input );
   			
   			



   		}
   		if (printcounter >= 0.15){
   			printcounter = 0;
   			printf("%f\n",boatPosition );
   			printf("Position: %f\t Reference: %f\tControl input: %f\t error: %f\t \n",boatPosition,reference,ctrl_input,error );
   		}
   		

   		//give input to motor
   		
   		PhidgetRCServo_setTargetPosition(motorCh,ctrl_input);

   		
   		
		
		if(totaltime >=maxTime){
			finished=true;
		}

	}
}