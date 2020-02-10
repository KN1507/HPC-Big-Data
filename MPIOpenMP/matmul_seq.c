#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8  // Size of matrix and vector

#define R 10

int matrix[SIZE][SIZE], vector[SIZE], result[SIZE];

int main(int argc, char *argv[])
{
  int rank, size, matrix_start, matrix_end, n;
  n = SIZE;
  clock_t tic = clock();
  	printf("Fill Matrix : \n");
            for (int i=0; i<n*n; i++) {
                for (int j=0;j<n;++j)
                    matrix[i][j] = i+j;
            }
            for (int i=0; i<n; i++)
    	        vector[i] = i;

            for (int i=0;i<n;++i) {
                result[i] = 0;
            }

  int j=0; //Row no..
  for (int p=0; p<R; ++p) {
      for (int i=0; i<n; i++) {
        for (int j=0;j<n;++j) {
            result[i] += matrix[i][j] * vector[j];
        }
      }
  }

  clock_t toc = clock();

    printf("Matrix: \n");
    for(int i=0;i<n;++i) {
        for (int j=0; j< n; ++j) {
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\nVector: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",vector[i]);
    }
    printf("\n");
    printf("\nResult: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",result[i]);
    }
    printf("\n");
    printf("Elapsed time: %f seconds\n",(double)(toc - tic) / CLOCKS_PER_SEC);

  return 0;
}

