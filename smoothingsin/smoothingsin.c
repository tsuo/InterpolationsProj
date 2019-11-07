#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random.h"



/// change the x range for the sin function


double calcSin(double x, double expandy, double xoff, double yoff)
{
	return sin(x + xoff) * expandy + yoff;
}


int main(int argc, char **argv)
{	
	if(argc < 7){
		printf("USAGE: [curve outfile] [dot outfile] [rand seed] [len] [mult] [y max]\n\n");	
		exit(-1);
	}
	
	FILE *f = fopen(argv[1], "w+");
	FILE *f2 = fopen(argv[2], "w+");
	srand(atol(argv[3]));
	
	if(f == NULL || f2 == NULL) exit(-1);	

	int len = atol(argv[4]);
	int mult = atol(argv[5]); ///multiplier expansion
	int lens = len * mult;
	double ymax = atol(argv[6]);
	double vals[len];
	double smooth[lens];	
	double minVal = 0;

	//// randomizing array
	int i;
	for(i = 0; i < len; i++)
		vals[i] = randf(0, ymax);
	
	//// smoothing values
	int tile; 	// fraction of the interval (0pi, pi/4, 2pi/4, 3pi/4 etc)
	double p1;	// the first point  (changing value)
	double p2;	// the second point (changing value)
	double x;	//
	double xoffset;
	double yoffset;
	double ratio = 1;	// ratio between 

	printf("Starting Smoothing...\n");
	for(i = 0; i < lens; i++)
	{
		tile = i%mult;
		p1 = vals[i/mult];
		p2 = vals[(i/mult + 1) % len];
		if(p1 > p2)
		{
			ratio = (p1-p2)/2.0;
			xoffset = M_PI/2.0;
		}		
		else{
			ratio = (p2-p1)/2.0;
			xoffset = -1*M_PI/2.0;
		}
		yoffset = vals[i/mult] - (sin(0 + xoffset)*ratio);
		x = ((double)tile/(double)mult) * M_PI;		
		smooth[i] = calcSin(x, ratio, xoffset, yoffset);		

	}
	printf("...Finished Smoothing!\n\n");	
	
	printf("Printing to Files...\n");
	for(i = 0; i < lens; i++)
	{
		fprintf(f, "%d\t%f\n", i, smooth[i]);
	}
	for(i = 0; i < len; i++)
	{
		fprintf(f2, "%d\t%f\n", i, vals[i]);
	}
	printf("...Finished Printing to File!\n\n");

	fclose(f);
	fclose(f2);

	printf("\nDone\n");

	return 0;
}
