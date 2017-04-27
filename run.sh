
#!/bin/bash

#SBATCH -p general	# partition (queue)
#SBATCH -t 0-2:00	# time (D-HH:MM)
#SBATCH -o slurm.before.%N.%j.out # STDOUT
#SBATCH -e slurm.before.%N.%j.err # STDERR

gcc iterativefft.c -lm -fopenmp -lpapi

export OMP_NUM_THREADS=1
time ./a.out

export OMP_NUM_THREADS=2
time ./a.out

export OMP_NUM_THREADS=4
time ./a.out

export OMP_NUM_THREADS=8
time ./a.out

export OMP_NUM_THREADS=16
time ./a.out

export OMP_NUM_THREADS=32
time ./a.out

export OMP_NUM_THREADS=64
time ./a.out

gcc recursivefft.c -lm -fopenmp -lpapi

export OMP_NUM_THREADS=1
time ./a.out

export OMP_NUM_THREADS=2
time ./a.out

export OMP_NUM_THREADS=4
time ./a.out

export OMP_NUM_THREADS=8
time ./a.out

export OMP_NUM_THREADS=16
time ./a.out

export OMP_NUM_THREADS=32
time ./a.out

export OMP_NUM_THREADS=64
time ./a.out
