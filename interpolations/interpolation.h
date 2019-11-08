#ifndef H_INTERP
#define H_INTERP

#define NOISE_LINEAR 	0
#define NOISE_COSINE 	1
#define NOISE_CUBIC 	2
#define NOISE_HERMITE 	3

#include <math.h>
#include <stdio.h>

int NOISE_TYPE = 0;

///////////////////////////////////////////
// references:
// 	paulbourke.net
//
// values of x are between 0 and 1 inclusive

int pmod(int a, int b)
{
	return ((a%b) + b) % b;
}

double interpolate_linear(double v1, double v2, double x)
{
	return v1*(1-x) + v2*x;
}

double interpolate_cosine(double v1, double v2, double x)
{
	double x2 = (1-cos(x * M_PI))/2;
	return v1*(1-x2) + v2*x2;
}

double interpolate_cubic(double v0, double v1, double v2, double v3, double x)
{
	double x2 = x*x;
	double a0 = v3 - v2 - v0 + v1;
	double a1 = v0 - v1 - a0;
	double a2 = v2 - v0;
	double a3 = v1;
	//printf("vals: %f, %f, %f, %f, %f\n", x, v0, v1, v2, v3);

	//printf("vals: %f, %f, %f, %f, %f\n", x2, a0, a1, a2, a3);	
	//printf("vals: %f, %f, %f\n\n", a0*x*x2, a1*x2, a2*x*a3);	

	return (a0*x*x2 + a1*x2 + a2*x + a3);
}

/// tension and bias between -1 and 1
double interpolate_hermite(double v0, double v1, double v2, double v3, 
			   double x, double tension, double bias)
{
	double x2 = x*x;
	double x3 = x2*x;
	
	double x0 = (v1-v0)*(1+bias)*(1-tension)/2.0;
	x0 += (v2-v1)*(1-bias)*(1-tension)/2.0;
	
	double x1 = (v2-v1)*(1+bias)*(1-tension)/2.0;
	x1 += (v3-v2)*(1-bias)*(1-tension)/2.0;
	
	double a0 = 2*x3 - 3*x2 + 1;
	double a1 = x3 - 2*x2 + x;
	double a2 = x3 - x2;
	double a3 = -2*x3 + 3*x2;

	return (a0*v1 + a1*x0 + a2*x1 + a3*v2);
}

////////////////
/// generate 1D noise:
/// args: [random Array]  [array length]  [array index]  [0.0 to 1.0]
double noise(double *vals, int len, int index, double x)
{
	if(index >= len || len < 4) return -1;

	double v0, v1, v2, v3;	
	v0 = vals[pmod((index - 1), len)];	
	v1 = vals[index];
	v2 = vals[pmod((index + 1), len)];
	v3 = vals[pmod((index + 2), len)];

	//fprintf(stdout, "vals: %d, %d, %f\n%f, %f, %f, %f\n", len, index, x, v0, v1, v2, v3);

	if(NOISE_TYPE == NOISE_LINEAR)
	{
		return interpolate_linear(v1, v2, x);
	}
	else if(NOISE_TYPE == NOISE_COSINE)
	{
		return interpolate_cosine(v1, v2, x);
	}
	else if(NOISE_TYPE == NOISE_CUBIC)
	{
		//printf("vals: %f, %f, %f, %f, %f\n", x, v0, v1, v2, v3);
		return interpolate_cubic(v0, v1, v2, v3, x);
	}
	else if(NOISE_TYPE == NOISE_HERMITE)
	{
		double tension = -1;
		double bias = 0.2;
		return interpolate_hermite(v0, v1, v2, v3, x, tension, bias);
	}
}


////////////////
/// generate 2D noise:
/// args: [random Array]  [array width]  [array height]  [1D array index]  [0.0 to 1.0] [0.0 to 1.0]
double noise2D(double *vals, int width, int height, int index, double x, double y)
{
	int len = width * height;
	if(index >= len || len < 4) return -1;

	double va0, va1, va2, va3;
	double vb0, vb1, vb2, vb3;
	int windex = index%width;
	int hindex = index/width;

	va0 = vals[(pmod((windex - 1), width) + width*hindex)];	
	va1 = vals[index];
	va2 = vals[(pmod((windex + 1), width) + width*hindex)];
	va3 = vals[(pmod((windex + 2), width) + width*hindex)];


	vb0 = vals[((pmod((hindex - 1), height)*width) + windex)];	
	vb1 = vals[index];
	vb2 = vals[((pmod((hindex + 1), height)*width) + windex)];
	vb3 = vals[((pmod((hindex + 2), height)*width) + windex)];


	printf("ARGS 1: %d, %d, %d, %.3f, %.3f\n", width, height, index, x, y);
	printf("ARGS 2: %d, %d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n\n",
			len, windex, hindex, va0, va1, va2, va3, vb0, vb1, vb2, vb3);


	/*
	//fprintf(stdout, "vals: %d, %d, %f\n%f, %f, %f, %f\n", len, index, x, v0, v1, v2, v3);

	if(NOISE_TYPE == NOISE_LINEAR)
	{
		return interpolate_linear(v1, v2, x);
	}
	else if(NOISE_TYPE == NOISE_COSINE)
	{
		return interpolate_cosine(v1, v2, x);
	}
	else if(NOISE_TYPE == NOISE_CUBIC)
	{
		//printf("vals: %f, %f, %f, %f, %f\n", x, v0, v1, v2, v3);
		return interpolate_cubic(v0, v1, v2, v3, x);
	}
	else if(NOISE_TYPE == NOISE_HERMITE)
	{
		double tension = -1;
		double bias = 0.2;
		return interpolate_hermite(v0, v1, v2, v3, x, tension, bias);
	}
	*/
}


#endif //H_INTERP
