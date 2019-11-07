#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random.h"


/// change the x range for the sin function

int main(int argc, char **argv)
{	
	if(argc < 2) exit(-1);
	
	FILE *f = fopen(argv[1], "w+");
	FILE *f2 = fopen("smooth2.txt", "w+");
	if(f == NULL) exit(-1);	

	int len = 20;
	int mult = 100;
	int lens = len * mult;
	double ymax = 50;
	double vals[len];
	double smooth[lens];	
	double minVal = 0;

	vals[0] = randf(0, ymax);
	minVal = vals[0];

	int i;
	for(i = 1; i < len; i++)
	{
		vals[i] = randf(0, ymax);
		if(vals[i] < minVal) minVal = vals[i];
		printf("%d\t%f\n", i, vals[i]);
	}	
	
	
	int tile; 	// fraction of the period
	double v1;	// the first array val
	double v2;	// the second array val
	double x;
	double xoffset;
	double yoffset;
	double ratio = 1;	// ratio between 
	for(i = 0; i < lens; i++)
	{
		/// new function is sin(x * mult) * ratio + offset
		/// or cos(x * mult) * ratio + offset
		
		tile = i%mult; 
		x = ((double)tile/(double)mult) * M_PI;
		v1 = vals[i/mult];
		v2 = vals[(i/mult + 1)%len];
		
		if(v1 == v2) smooth[i] = v1;	
		else
		{
			if(v1 > v2)
			{
				ratio = (v1-v2) / 2.0;
				xoffset = M_PI/-2;
				yoffset = v2;
				//printf("ratio: %f/%f=%f\nxoffset: %f\n\n", v1-v2, 2.0, ratio, xoffset);
			}
			else
			{
				ratio = (v2-v1) / 2.0;
				xoffset = M_PI/2;
				yoffset = v1;
				//printf("ratio: %f/%f=%f\noffset: %f\n\n", v2-v1, 2.0, ratio, xoffset);
			}
			
			/// set smooth[i] to new sin value
			smooth[i] = sin(x + xoffset) * ratio + yoffset;
			printf("%d, %d, %d\n", i/mult, (i/mult + 1)%len,  i);
		}
	}
	
	
	for(i = 0; i < 250; i++)
	{
		fprintf(f, "%d\t%f\n", i, smooth[i]);
	}
	for(i = 0; i < len; i++)
	{
		fprintf(f2, "%d\t%f\n", i, vals[i]);
	}
	fclose(f);
	fclose(f2);

	printf("\nDone\n");

	return 0;
}
