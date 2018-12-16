#include <stdlib.h>
#include <stdio.h>


void freeArray(int **a, int m) {
  int i;
  for (i = 0; i < m; ++i) {
    free(a[i]);
  }
  free(a);
}