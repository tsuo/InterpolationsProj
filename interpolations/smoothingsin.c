#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random.h"
#include "release/sinemapping.c"
#include "interpolation.h"

////
// continue working on interpolation.h function noise2D


int main(int argc, char **argv)
{	
	if(argc < 7){
		printf("USAGE: [curve outfile] [dot outfile] [rand seed] [len] [mult] [y max]\n\n");	
		exit(-1);
	}
	
	FILE *f = fopen(argv[1], "w+");
	FILE *f2 = fopen(argv[2], "w+");
	
	if(f == NULL || f2 == NULL) exit(-1);	

	int seed = atol(argv[3]);
	int len = atol(argv[4]);
	int mult = atol(argv[5]); ///multiplier expansion
	
	int lens = len * mult;
	double ymax = atol(argv[6]);

	srand(seed);
	
	double vals[len];
	double smooth[lens];
	//double *vals;
	//double *smooth;		

	printf("\n\n");
	printf("[ARGUMENTS]\nSmooth File: %s\nPlot File: %s\nSeed: %d\nPlot Length: %d\n" 
				"Muliplier: %d\nSmooth Length: %d\nMax Y: %f\n\n", 
				argv[1], argv[2], seed, len, mult, lens, ymax);	

	int i;
	printf("Start interpolation...\n");
	
	///random values	
	for(i = 0; i < len; i++)
	{
		vals[i] = randi(ymax);
	}

	NOISE_TYPE = NOISE_COSINE;

	//for(i = 0; i < lens; i++)
	//{
	//	smooth[i] = noise(vals, len, i/mult, (double)(i%mult)/(double)mult);
	//}

	int width = 5;
	int height = 5;	
	int mult2d = 4;
	int swidth = width * mult2d;
	int sheight = height * mult2d;
	double vals2d[height*width];
	double smooth2d[height*mult2d * width*mult2d];
	int y,x;	
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			vals2d[y*width + x] = randi(ymax);
			printf("val[%d]: %f\n", y*width + x, vals2d[y*width+x]);
		}
	}
	
	for(y = 0; y < sheight; y++)
	{
		for(x = 0; x < swidth; x++)
		{
			smooth2d[y*swidth + x] = noise2D(vals2d, width, height, y*swidth + x,
							(double)(x%mult2d)/(double)mult2d,
							(double)(y%mult2d)/(double)mult2d);
		}
	}
	

	/*
	double x;
	double v1;
	double v2;
	for(i = 0; i < lens; i++)
	{
		x = (double)(i%mult) / (double)mult;
		
		v1 = vals[i/(mult)];
		v2 = vals[(i/mult + 1) % len];
		
		smooth[i] = interpolate_cosine(v1, v2, x);
		//printf("val:%f + %f\n", interpolate_cosine(v1, v2, x), v1);
	}
	*/
	//sine_map(&vals, &smooth, len, mult, ymax);
	printf("..End interpolation!\n\n");	

	/*
	//int i;
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
	*/

	fclose(f);
	fclose(f2);
	//free(smooth);
	//free(vals);

	printf("\nDone\n");

	return 0;
}
