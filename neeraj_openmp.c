// O(n^2) Matrix Multiplication (Using N processors)

#include <mpi.h>
#include <stdio.h>

#define SIZE 3			/* Size of matrices */

int A[SIZE][SIZE], B[SIZE], C[SIZE];

void print_matrix(int m[SIZE][SIZE], int n)
{
  int i, j = 0;
  for (i=0; i<n; i++) {
    printf("\n\t| ");
    for (j=0; j<n; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}


void print_matrix2(int m[SIZE], int n)
{
  int i;
  for (i=0; i<n; i++) {
      printf("%2d ", m[i]);
  }
}

int main(int argc, char *argv[])
{
  int myrank, P, from, to, i, j, k, n, from1, to1;
  int tag = 666;		/* any value will do */
  n = SIZE;
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);	/* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &P); /* number of processors */

  //MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  /* Just to use the simple variants of MPI_Gather and MPI_Scatter we */
  /* impose that SIZE is divisible by P. By using the vector versions, */
  /* (MPI_Gatherv and MPI_Scatterv) it is easy to drop this restriction. */

  if (P != n) {
    if (myrank==0) printf("Number of processors not divisible by matrix size.\n");
    MPI_Finalize();
    exit(-1);
  }

  from = myrank * (n*n)/P;
  to = (myrank+1) * (n*n)/P;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  if (myrank==0) {
  	printf("Fill Matrix A : \n");
    for (i=0; i<n; i++)
    	for (j=0; j<n; j++)
       		A[i][j] = i+j;
    printf("Fill Matrix B : \n");
    for (i=0; i<n; i++)
    	B[i] = i;
  }

  MPI_Bcast (B, n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (A, n*n/P, MPI_INT, A[from], n*n/P, MPI_INT, 0, MPI_COMM_WORLD);

  printf("computing slice %d (from element %d to %d)\n", myrank, from+1, to);
  for (i=from; i<to; i++) 
    for (j=0; j<n; j++) {
      C[i] += A[i][j]*B[j];
    }

  MPI_Gather (C+from, n/P, MPI_INT, C, n, MPI_INT, 0, MPI_COMM_WORLD);

  if (myrank==0) {
    printf("\n\n");
    print_matrix(A,n);
    printf("\n\n\t       * \n");
    print_matrix2(B,n);
    printf("\n\n\t       = \n");
    print_matrix2(C,n);
    printf("\n\n");
  }

  MPI_Finalize();
  return 0;
}
