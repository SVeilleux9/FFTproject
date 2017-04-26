#include <stdio.h>
#include <math.h>

#define PI 3.1415

struct complex {
	double re;
	double im;
} complex;


int reverseBits(int num, int size){

	int out = 0;

	for (int i = 0; i < size; i++){
		if((num & (1 << i)))
			out |= 1 << ((size - 1) - i);  
	}
	return out;

}

void fft(struct complex in, struct complex out, int len){

	int s = log(len)/log(2);

	for(int i=0; i<len; i++){
		out[i] = reverseBits(out[i], s);
	}

	for(int i=1; i<s; i++){
		int m = 0x01 << s;
		int theta = 2*PI/m;
		struct complex wm;
		wm.re = cos(theta);
		wm.im = sin(theta);

		for(int j=0; j<len; j+=m){
			struct complex w;
			w.re = 1;
			w.im = 0;

			for(int k=0; k<m/2; k++){
				int ind1 = j+k;
				int ind2 = j+k+m/2;

				struct complex u;
				u.re = out[ind1].re;
				u.im = out[ind1].im;

				struct complex t;
				t.re = out[ind2].re*w.re;
				



}

void main(){

	int length = 8;
}