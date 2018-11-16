/* transpif.c
 * I pledge my honor that I have abided by the Stevens Honor System.
 * Justin Ho
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMTESTS 100
#define MATRIX_HEIGHT atoi(argv[1])
#define MATRIX_WIDTH atoi(argv[2])
#define BLOCK_WIDTH atoi(argv[3])
#define SECONDS (after.tv_sec - before.tv_sec)
#define MICROSECONDS (after.tv_usec - before.tv_usec)
#define ELAPSED_TIME (SECONDS + (MICROSECONDS / 1000000.0))

void createMatrix (float* in, int w, int h) {
  for (int i = 0; i < w*h; i++)
    in[i] = rand();
}

void transpose (float* in, float* out, int w, int h, int block) {
  for (int i = 0; i < h; i += block) {
    for (int j = 0; j < w; j++) {
      int x = j*h;
      for (int k = 0; k < block && i + k < h; k++)
	out[x + i + k] = in[(i+k)*w + j];
    }
  }
}

int main (int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "ERROR: Wrong number of command-line arguments.\n");
    fprintf(stderr, "USAGE: %s matrix_height matrix_width block_width\n", argv[0]);
    return -1;
  }

  float* in = (float*) malloc(MATRIX_WIDTH * MATRIX_HEIGHT * sizeof(float));
  float* out = (float*) malloc(MATRIX_WIDTH * MATRIX_HEIGHT * sizeof(float));
  createMatrix(in, MATRIX_WIDTH, MATRIX_HEIGHT);

  struct timeval before, after;
  gettimeofday(&before, NULL);

  for (int i = 0; i < NUMTESTS; i++)
    transpose(in, out, MATRIX_WIDTH, MATRIX_HEIGHT, BLOCK_WIDTH);

  gettimeofday(&after, NULL);
  printf("Total runtime: %f\n", ELAPSED_TIME);
  printf("Individual runtime: %f\n", ELAPSED_TIME / NUMTESTS);

  free(in);
  free(out);
  return 0;
}
