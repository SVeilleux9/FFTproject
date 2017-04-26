#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.1415

typedef struct{
	double r;
	double i;
} complex;


int reverseBits(int num, int size){

	int out = 0;

	for (int i = 0; i < size; i++){
		if((num & (1 << i)))
			out |= 1 << ((size - 1) - i);  
	}
	return out;

}

void fft(complex *in, complex *out, int len){

	int s = log(len)/log(2);
	int i, revi, j, k, m, theta, i1, i2;
	complex wm, w, tmp;

	for(i=0; i<len; i++){
		revi = reverseBits(i, s);
		out[revi] = in[i];
	}

	for(i=1; i<=s; i++){
		m = 0x01 << s;
		theta = 2*PI/m;
		
		wm.r = cos(theta);
		wm.i = sin(theta);

		for(j=0; j<len; j+=m){
			
			w.r = 1;
			w.i = 0;

			for(k=0; k<m/2; k++){
				i1 = j+k;
				i2 = j+k+m/2;

				tmp.r = w.r*out[i2].r - w.i*out[i2].i;
				out[i1].r = out[i1].r + tmp.r;
				out[i2].r = out[i1].r - tmp.r;

	      			tmp.i = w.r*out[i2].i + w.i*out[i2].r;
				out[i1].i = out[i1].i + tmp.i;
				out[i2].i = out[i1].i - tmp.i;

				w.r = w.r*wm.r - w.i*wm.i;
				w.i = w.r*wm.i + w.i*wm.r;
		
			}
		}
	}
}

double Cabs(double real, double imag){

	return sqrt(real*real + imag*imag);

}

void main(){

	double data[] = {
		1.000000, -0.104528, -0.978148, 0.309017, 0.913545, -0.500000, -0.809017, 0.669131, 
		0.669131, -0.809017, -0.500000, 0.913545, 0.309017, -0.978148, -0.104528, 1.000000
	};

	int len = sizeof(data)/sizeof(data[0]);

	complex *indataFFT, *outdataFFT;
	indataFFT  = (complex*)calloc(len, sizeof(complex));
	outdataFFT = (complex*)calloc(len, sizeof(complex));
	 

	for(int i=0; i<len; i++){
		indataFFT[i].r = data[i];
	}
	
	fft(indataFFT, outdataFFT, len);

	for(int i=0; i<len; i++){
		printf("%f\n",Cabs(outdataFFT[i].r, outdataFFT[i].i));
	}

}
