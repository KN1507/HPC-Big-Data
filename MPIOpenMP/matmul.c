#include <stdio.h>
#include <stdlib.h>
//#include <stdatomics.h>
#include <mpi.h>
#include <omp.h>

#define SIZE 3  // Size of matrix and vector
//mtx_t lock;

int matrix[SIZE*SIZE], vector[SIZE], result[SIZE];

int main(int argc, char *argv[])
{
  int rank, size, matrix_start, matrix_end, n;
  n = SIZE;
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);	/* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &size); /* number of processors */

  if (n%size != 0 || n<size) {
    printf("%d %d",n,size);
    if (rank==0) printf("Number of processors not divisible by matrix size.\n");
    MPI_Finalize();
    exit(-1);
  }

  if (rank==0) {
  	printf("Fill Matrix : \n");
    // #pragma omp parallel sections {
    //     #pragma section {
            #pragma omp parallel for
            for (int i=0; i<n*n; i++) {
                matrix[i] = i;
            }
        //}
        // #pragma section {
            #pragma omp parallel for
            for (int i=0; i<n; i++)
    	        vector[i] = i;
    //     }
    // }
  }

  matrix_start = rank * (SIZE*SIZE)/size;
  matrix_end = (rank+1) * (SIZE*SIZE)/size;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  int *procRow = malloc(sizeof(int) * n*n/size);
  if (procRow == NULL) {
      printf("Error in malloc for procRow in proc: %d",rank);
      exit(1);
  }
  int *procResult = malloc(sizeof(int) * n/size);
  if (procResult == NULL) {
      printf("Error in malloc for procResult in proc: %d",rank);
  }

  #pragma omp parallel for
  for (int i=0;i<n/size;++i) {
    procResult[i] = 0;
  }

  MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(matrix, n*n/size, MPI_INT, procRow, n*n/size, MPI_INT, 0, MPI_COMM_WORLD);

  //MPI_Barrier(MPI_COMM_WORLD);
  printf("computing slice %d (from element %d to %d)\n", rank, matrix_start+1, matrix_end);
  int v_index = 0;
//   printf("\nMatrix row in proc %d:\n",rank);
//   for (int i=0; i<n/size; ++i) {
//       printf("%d",procRow[i]);
//   }
//   printf("\nVector row in proc %d:\n",rank);
//   for (int i=0; i<n; ++i) {
//       printf("%d",vector[i]);
//   }
  printf("\n");
  #pragma omp parallel for collapse(2)
  for (int i=0; i<n/size; i++) { // Rows.. 
    // for (j=0; j<n; j++) {
    //   procResult[i] += procRow[i+j]*vector[j];
    for (int j=0;j<n;++j) {
        //mtx_lock(&lock);
        procResult[i] += procRow[v_index++]*vector[j];
        //mtx_unlock(&lock);    
    }
  }

  MPI_Gather(procResult, n/size, MPI_INT, result, n/size, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank==0) {

    printf("Matrix: \n");
    for(int i=0;i<n*n;++i) {
        if(i%n == 0)
            printf("\n");
        printf("%d\t",matrix[i]);
    }

    printf("\nVector: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",vector[i]);
    }

    printf("\nResult: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",result[i]);
    }


  }

  MPI_Finalize();
  return 0;
}