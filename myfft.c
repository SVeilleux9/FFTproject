#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <omp.h>

#define PI 3.141592653589793238462643383279502884197
#define MULT 1024*4
#define THREADS 4

typedef struct{
	double r; 
	double i;
	} complex;

int pow2(int exp);
void myfft(complex *data, int len);
double Cabs(double real, double imag);

void main(){

	double data[] = {
		1.000000, -0.104528, -0.978148, 0.309017, 0.913545, -0.500000, -0.809017, 0.669131, 
		0.669131, -0.809017, -0.500000, 0.913545, 0.309017, -0.978148, -0.104528, 1.000000
		};

	int len = sizeof(data)/sizeof(data[0]);

	complex *dataFFT;
	dataFFT = (complex*)calloc(len, sizeof(complex));	

	for(int i=0; i<len; i++){
		dataFFT[i].r = data[i];
	}

	myfft(dataFFT, len);

	for(int i=0; i<len; i++){
		printf("%f\n",Cabs(dataFFT[i].r,dataFFT[i].i));
	}
}



void myfft(complex *data, int len){

	int base2, numel, size, gap, L, ind;	
	double theta;
	complex w, tmp, even, odd;
	
	base2 = log(len)/log(2);

	for(int i=base2; i>0; i--){
		size = pow2(base2-i+1);
		gap = pow2(i);
		L = len/size;

		
		for(int l=0; l<L; l++){
			for(int n=0; n<size/2; n++){
				ind = l+n*gap;	
				even = data[ind];
				odd = data[ind+L];
				
				theta = 2*PI*ind/(double)len;
				w.r = cos(theta);
				w.i = sin(theta);

				tmp.r = w.r*odd.r - w.i*odd.i;
				data[ ind ].r = even.r + tmp.r;
				data[ind+L].r = even.r - tmp.r;

	      			tmp.i = w.r*odd.i + w.i*odd.r;
				data[ ind ].i = even.i + tmp.i;
				data[ind+L].i = even.i - tmp.i;


				printf("%d,%d  ",ind,ind+L);
			}
			printf("\n");
		}
	}
}

int pow2(int exp){

	int out=1;

	for(int i=0; i<exp; i++){
		out*=2;
	}

	return out;
}

double Cabs(double real, double imag){

	return sqrt(real*real + imag*imag);

}

