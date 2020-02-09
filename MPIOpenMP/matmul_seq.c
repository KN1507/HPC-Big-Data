#include <stdio.h>
#include <stdlib.h>

#define SIZE 3  // Size of matrix and vector

int matrix[SIZE][SIZE], vector[SIZE], result[SIZE];

int main(int argc, char *argv[])
{
  int rank, size, matrix_start, matrix_end, n;
  n = SIZE;
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
  for (int i=0; i<n; i++) {
      for (int j=0;j<n;++j) {
              result[i] += matrix[i][j] * vector[j];
      }
  }

    printf("Matrix: \n");
    for(int i=0;i<n;++i) {
        for (int j=0; j< n; ++j) {
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nVector: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",vector[i]);
    }

    printf("\nResult: \n");
    for(int i=0;i<n;++i){
        printf("%d\t",result[i]);
    }

  return 0;
}