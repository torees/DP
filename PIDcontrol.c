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
	//ensure control input is a valid servo position to avoid saturating the motor
	if (ctrl_input<107){ctrl_input=107;}
	if (ctrl_input>199){ctrl_input=199;}



	
	return ctrl_input;


}


void runDPloop(float reference){
	
	//static float prev_ctrl_input;
	static struct timeval previous_time;
	float dt = 0.020;
	struct timeval tn;
	float elapsed = 0;
	float totaltime = 0;
	bool finished = false;
	printf("Starting DP..The controller will run until finished.\nPress 'Ctrl + C' to abort\n");
	
	float counter = 0.0;
	gettimeofday(&previous_time, 0);
	//
	float boatPosition = 0;
	float ctrl_input =computeControlInput(boatPosition,reference,dt);
	//keep while loop until finished or aborted by user
	
	while(finished == false){
		
		//Timer functionality, count how long each iteration takes
		gettimeofday(&tn, 0);
   		elapsed = timedifference_msec(previous_time, tn);
   		previous_time = tn;

   		//Every 20 ms, compute new PID input
   		counter += elapsed;
   		totaltime += elapsed;
   		
   		if(counter >=dt){
   			//Get ship position from IOcard
   			//boatPosition=getBoatPos();

   			//Compute new input
   			ctrl_input =computeControlInput(boatPosition,reference,dt);

   			//Reset timer
   			counter = 0.0;

   			//Update data files
   			
   			//fprintf(input, "%f\n",ctrl_input);
   			//fprintf(position, "%f\n",boatPosition);
   			//fprintf(target, "%f\n",reference);



   		}
   		if (counter >= dt*10)
   		{
   			printf("%f\n",boatPosition );
   			
   		}

   		//give input to motor
   		//setMotorSpeed(ctrl_input);
   		

   		setMotorSpeed(90);
   		
   		
		
		if(totaltime >=maxTime){
			finished=true;
		}

	}
}