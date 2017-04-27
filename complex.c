#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

void main(){

	double complex a = 1+0*I,b=2+0*I;
	a = creal(3) + cimag(0)*I;

	double complex c = a*b;

	printf("%f\n", creal(c));

}
