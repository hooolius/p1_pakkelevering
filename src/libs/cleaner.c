#include <stdlib.h>
#include <stdio.h>

int **make_array(int row, int col) {
  int ** ptr = (int **) calloc(sizeof(int *), row);
  for(int i = 0; i < row; i++) {
    ptr[i] = (int *) calloc(sizeof(int), col);
  }
  return ptr;
}

void free_array(int **ptr, int row) {
  for (int i = 0; i < row; ++i) {
    free(ptr[i]);
  }
  free(ptr);
}
