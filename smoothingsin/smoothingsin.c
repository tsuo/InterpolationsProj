#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random.h"
#include "release/sinemapping.c"


///// 
// test for sinemapping.c

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
	
	double *vals;
	double *smooth;		

	printf("\n\n");
	printf("[ARGUMENTS]\nSmooth File: %s\nPlot File: %s\nSeed: %d\nPlot Length: %d\n" 
				"Muliplier: %d\nSmooth Length: %d\nMax Y: %f\n\n", 
				argv[1], argv[2], seed, len, mult, lens, ymax);	

	printf("Start sine mapping...\n");
	sine_map(&vals, &smooth, len, mult, ymax);
	printf("..End sine mapping!\n\n");	

	int i;
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
	free(smooth);
	free(vals);

	printf("\nDone\n");

	return 0;
}
