#ifndef H_INTERP
#define H_INTERP

#define NOISE_LINEAR 	0
#define NOISE_COSINE 	1
#define NOISE_CUBIC 	2
#define NOISE_HERMITE 	3

#include <math.h>
#include <stdlib.h>

int NOISE_TYPE = 0;

///////////////////////////////////////////
// references:
// 	paulbourke.net
//
// values of x are between 0 and 1 inclusive

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
		
	return (a0*x*x2 + a1*x2 + a2*x*a3);
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
}

////////////////
/// generate 1D noise:
/// args: [random Array]  [array length]  [array index]  [0.0 to 1.0]
double noise(double *vals, int len, int index, double x)
{
	if(index >= len || len < 4) return -1;

	double v0, v1, v2, v3;	
	v0 = vals[(index - 1)%len];	
	v1 = vals[index];
	v2 = vals[(index + 1)%len];
	v3 = vals[(index + 2)%len];
	
	//fprintf(stdout, "vals: %f, %f, %f, %f\n", v0, v1, v2, v3);

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
		return interpolate_cubic(v0, v1, v2, v3, x);
	}
	else if(NOISE_TYPE == NOISE_HERMITE)
	{
		double tension = 0;
		double bias = 0;
		return interpolate_hermite(v0, v1, v2, v3, x, tension, bias);
	}
}

#endif //H_INTERP
