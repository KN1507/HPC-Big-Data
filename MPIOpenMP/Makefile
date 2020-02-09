
EXECUTABLES=hello primes-omp primes-mpi stencil-mpi matmul matmul2

EXPENSIVE_JUNK += $(EXECUTABLES)

SRC = hello.c primes-omp.c primes-mpi.c stencil-mpi.c matmul.c matmul2.c

JUNK +=

CFLAGS += -O3 -Wall -W --std=c11 -lm
OMP_CFLAGS = $(CFLAGS) -fopenmp
MPI_CFLAGS = $(CFLAGS) -lmpi

help:
        @echo "help\tShow this help text"
        @echo "all\tMake all executables"
        @echo "clean\tThrow away all files that are easy to produce again"
        @echo "empty\tThrow away all files that can be produced again"

all: $(EXECUTABLES)

clean:
        rm -rf $(JUNK)

empty:
        rm -rf $(JUNK) $(EXPENSIVE_JUNK)

hello: hello.c
        $(CC) $(CFLAGS) -o hello hello.c

primes-omp: primes-omp.c
        $(CC) $(OMP_CFLAGS) -o primes-omp primes-omp.c

primes-mpi: primes-mpi.c
        mpiCC $(MPI_CFLAGS) -o primes-mpi primes-mpi.c

stencil-mpi: stencil-mpi.c
        mpiCC $(MPI_CFLAGS) -o stencil-mpi stencil-mpi.c

matmul: matmul.c
        mpicc $(OMP_CFLAGS) $(MPI_CFLAGS) -o matmul matmul.c

matmul2: matmul2.c
        mpicc $(MPI_CFLAGS) -o  matmul2 matmul2.c

matmul3: matmul.c
        mpicc -O3 -Wall -W --std=c11 -lm -fopenmp -lmpi -o matmul matmul.c

