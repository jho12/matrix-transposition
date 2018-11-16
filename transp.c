/* transp.c
 * I pledge my honor that I have abided by the Stevens Honor System.
 * Justin Ho
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMTESTS 100
#define MATRIX_WIDTH atoi(argv[1])
#define BLOCK_WIDTH atoi(argv[2])
#define SECONDS (after.tv_sec - before.tv_sec)
#define MICROSECONDS (after.tv_usec - before.tv_usec)
#define ELAPSED_TIME SECONDS + (MICROSECONDS / 1000000.0)

void createMatrix (float* in, int N) {
  for (int i = 0; i < N*N; i++)
    in[i] = rand();
}

void transpose (float* in, float* out, int N, int block) {
  for (int i = 0; i < N; i += block) {
    for (int j = 0; j < N; j += block) {
      for (int x = i; x < (i + block); x++) {
	int X = x*N;
	for (int y = j; y < (j + block); y++)
	  out[X + y] = in[y*N + x];
      }
    }
  }
}

int main (int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "ERROR: Wrong number of command-line arguments.\n");
    fprintf(stderr, "USAGE: %s matrix_width transpose_width\n", argv[0]);
    return -1;
  }

  if (MATRIX_WIDTH < BLOCK_WIDTH) {
    fprintf(stderr, "ERROR: Block width should not be larger than matrix width.\n");
    return -1;
  }
  
  float* in = (float*) malloc(MATRIX_WIDTH * MATRIX_WIDTH * sizeof(float));
  float* out = (float*) malloc(MATRIX_WIDTH * MATRIX_WIDTH * sizeof(float));
  createMatrix(in, MATRIX_WIDTH);

  struct timeval before, after;
  gettimeofday(&before, NULL);
  
  for (int i = 0; i < NUMTESTS; i++)
    transpose(in, out, MATRIX_WIDTH, BLOCK_WIDTH);

  gettimeofday(&after, NULL);
  printf("Total runtime: %f\n", ELAPSED_TIME);
  printf("Individual runtime: %f\n", (ELAPSED_TIME) / NUMTESTS);

  free(in);
  free(out);
  return 0;
}
