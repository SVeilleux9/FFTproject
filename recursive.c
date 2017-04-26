#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <omp.h>

void parallel(){
	#pragma omp task
	{
		printf("%d\n",omp_get_num_threads());
		sleep(1);
	}
	#pragma omp task
	{
		printf("%d\n",omp_get_num_threads());
		sleep(1);
	}

	#pragma omp taskwait

}


void main(){

	omp_set_num_threads(2);

	#pragma omp parallel sections
		{
			#pragma omp section
			{
				printf("%d\n",omp_get_num_threads());
				parallel();
			}			
			#pragma omp section
			{
				printf("%d\n",omp_get_num_threads());
				parallel();
			}
		}

}
