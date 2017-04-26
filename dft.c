


void dft(complex *data, int len){

	int k,n;
	double theta, thetan;
	complex *tmp, w;

	tmp = (complex*)calloc(len, sizeof(complex));

	for(k=0;k<len;k++){
		theta = 2*PI*k/(double)len;
		for(n=0;n<len;n++){
			thetan = theta*n;
			w.r = cos(thetan);
			w.i = sin(thetan);
			
			tmp[k].r += data[n].r*w.r - data[n].i*w.i;
			tmp[k].i += data[n].r*w.i + data[n].i*w.r;
		}
	}
	
	memcpy(data, tmp, len*sizeof(complex));


}

