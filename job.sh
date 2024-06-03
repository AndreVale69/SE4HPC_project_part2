#!/bin/bash

#SBATCH --job-name=matrixMultiplication
#SBATCH --time=00:30
#SBATCH --ntasks=2
#SBATCH --nodes=1
#SBATCH -o output.log # File to which STDOUT will be written
#SBATCH -e errors.log # File to which STDERR will be written

module load singularity

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

singularity exec --bind $TMPDIR:$TMPDIR  matrix-multiplication.sif bash -c "export OMPI_MCA_tmpdir_base=$TMPDIR && mpirun -np 2 /prj/main"