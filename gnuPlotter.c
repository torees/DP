#include <stdio.h>
#include <stdlib.h>

/*Create plots using gnuplot 
Declare functions used by the program as well as global definitions 


2018 Tore Sæterdal*/

void plotGNUposition(){

	//open a GNU plot
	FILE *gnuPos = popen("gnuplot -persist","w");

	//set up
	fprintf(gnuPos, "set key reverse Left outside\n" );
	fprintf(gnuPos, "set grid\n" );
	fprintf(gnuPos, "set title 'Position vs reference' font ',20'\n" );
	//plot the contents of gnu.dat
	fprintf(gnuPos, "plot 'gnu.dat' using 1:2 with lines lt 1 title 'Reference','gnu.dat' using 1:3 with lines lt 2 title 'Position'\n" );
	fprintf(gnuPos, "set term png\n" );
	fprintf(gnuPos, "set output 'position.png'\n" );
	//close 
	pclose(gnuPos);


}

void plotGNUcontrol(){

	//open a GNU plot
	FILE *gnuPos = popen("gnuplot -persist","w");

	//set up
	fprintf(gnuPos, "set key reverse Left outside\n" );
	fprintf(gnuPos, "set grid\n" );
	fprintf(gnuPos, "set title 'Control input' font ',20'\n" );
	//plot the contents of plot.dat
	fprintf(gnuPos, "plot 'gnu.dat' using 1:4 with lines lt 1 title 'control input'\n" );
	fprintf(gnuPos, "set term png\n" );
	fprintf(gnuPos, "set output 'control_input.png'\n" );
	//close 
	pclose(gnuPos);

}