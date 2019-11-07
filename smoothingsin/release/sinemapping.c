#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "xmalloc.h"
#include "random.h"

double calcSin(double x, double expandy, double xoff, double yoff)
{
	return sin(x + xoff) * expandy + yoff;
}

void sine_map(double **vals, double **smooth, int len, int mult, double ymax)
{
	int lens = len * mult;
	*vals = (double*)xmalloc(sizeof(double) * len);
	*smooth = (double*)xmalloc(sizeof(double) * lens);

	//// randomizing array
	int i;
	for(i = 0; i < len; i++)
		(*vals)[i] = randf(0, ymax);
	
	//// smoothing values
	int tile; 	// fraction of the interval (0pi, pi/4, 2pi/4, 3pi/4 etc)
	double p1;	// the first point  (changing value)
	double p2;	// the second point (changing value)
	double x;	// the x value for the sine function
	double xoffset; // x offset for the sine function
	double yoffset; // y offset for the sine function
	double ratio = 1;	// ratio of verticle expansion

	for(i = 0; i < lens; i++)
	{
		tile = i%mult;
		p1 = (*vals)[i/mult];
		p2 = (*vals)[(i/mult + 1) % len];
		if(p1 > p2)
		{
			ratio = (p1-p2)/2.0;
			xoffset = M_PI/2.0;
		}		
		else{
			ratio = (p2-p1)/2.0;
			xoffset = -1*M_PI/2.0;
		}
		yoffset = (*vals)[i/mult] - (sin(0 + xoffset)*ratio);
		x = ((double)tile/(double)mult) * M_PI;		
		(*smooth)[i] = calcSin(x, ratio, xoffset, yoffset);		
	}
	
}
