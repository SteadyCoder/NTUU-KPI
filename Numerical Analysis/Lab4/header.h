#pragma once

//#include <iostream>
#include <math.h>

//using namespace std;

//composite trapezium rule
double CTR(double (*f)(double), double a, double b, double h)
{
	/*
	if (a>b)
	{
		double temp = a;
		a = b;
		b = temp;
	}
	*/

	double I = (f(a) + f(b))/2;
	double x = a;
	int n = (b-a)/h;

	for (int i=1;i<n;++i)
	{
		x += h;
		I += f(x);
	}

	return h*I;
}

//composite trapezium rule whith refined calculation
double CTR_RC(double (*f)(double),double a, double b, double eps, double* h)
{
	int n = (int)(1/sqrt(eps));
	(*h) = (b - a)/n;
	
	double I_h1,I_h2;

	I_h2 = CTR(f,a,b,(*h));
	
	do {
    I_h1 = I_h2;
	
   (*h) = (*h)/2;

	I_h2 = CTR(f,a,b,(*h));
	
	} while ( (abs(I_h1 - I_h2)/3) > eps );

    return I_h2;
}
