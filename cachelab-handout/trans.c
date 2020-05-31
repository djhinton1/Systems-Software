/*
Part B - Matrix Transposes
*/

/*
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {

  int blockSize;
  int i, j, blocked_i;
  int a, b, c, d, e, f, g, h;

  if(M == 32){
    blockSize = 8;
    for(i = 0; i < M; i += blockSize){
      for(j = 0; j < N; j += blockSize){
        for(blocked_i = i; blocked_i < i + blockSize; blocked_i++){
          a = A[blocked_i][j+0];
          b = A[blocked_i][j+1];
          c = A[blocked_i][j+2];
          d = A[blocked_i][j+3];
          e = A[blocked_i][j+4];
          f = A[blocked_i][j+5];
          g = A[blocked_i][j+6];
          h = A[blocked_i][j+7];
          B[j+0][blocked_i] = a;
          B[j+1][blocked_i] = b;
          B[j+2][blocked_i] = c;
          B[j+3][blocked_i] = d;
          B[j+4][blocked_i] = e;
          B[j+5][blocked_i] = f;
          B[j+6][blocked_i] = g;
          B[j+7][blocked_i] = h;
        }
      }
    }
  }
  else{
    blockSize = 4;
    for(i = 0; i < M; i += blockSize){
      for(j = 0; j < N; j += blockSize){
        for(blocked_i = i; blocked_i < i + blockSize; blocked_i++){
          a = A[blocked_i][j+0];
          b = A[blocked_i][j+1];
          c = A[blocked_i][j+2];
          d = A[blocked_i][j+3];
          B[j+0][blocked_i] = a;
          B[j+1][blocked_i] = b;
          B[j+2][blocked_i] = c;
          B[j+3][blocked_i] = d;
        }
      }
    }
  }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
