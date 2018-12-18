#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

void matrix(int n, int **matrix);
int least(int c, int n, int **mat, int *closed, int *dist);
void price(int point, int n, int **mat, int *closed, int *dist);
void min_g(int *dist);
int *run_greedy(int **afstand_matrix, int n);

#define INF INT_MAX

//int mat[30][30], closed[30], n, dist = 0;

/*void matrix() {
  int i, j;
  printf("Please type in the number of addresses\n");
  scanf(" %d", &n);

  for (i = 0; i < n; i++) {
    printf("\n Enter Elements of Row # : %d\n", i + 1);
    for (j = 0; j < n; j++)
      scanf(" %d", &mat[i][j]);
    closed[i] = 0;
  }

  for (i = 0; i < n; i++) {
    printf("\n\n");
    for (j = 0; j < n; j++)
      printf("\t%d", mat[i][j]);
  }
}*/
void matrix(int n, int **matrix) {
  int i, j;

  for (i = 0; i < n; i++) {
    printf("\n\n");
    for (j = 0; j < n; j++) {
      printf("\t%d", matrix[i][j]);
    }
  }
}
// HERE THE ARRAY IS TRANSFERED IN MATRIX

int least(int c, int n, int **mat, int *closed, int *dist) {
  int i, node = INF;
  int min = INF, kmin = 0;
  for (i = 0; i < n; i++) {
    if ((mat[c][i] != 0) && (closed[i] == 0))
      if (mat[c][i] < min) {
        min = mat[i][0] + mat[c][i];
        kmin = mat[c][i];
        node = i;
      }
  }

  if (min != INF) {
    *dist += kmin;
  }
  return node;
}

void price(int point, int n, int **mat, int *closed, int *dist) {
  int i, npoint = 0;
  closed[point] = 1;
  //printf("%d ===> ", point + 1);
  npoint = least(point, n, mat, closed, dist);

  if (npoint == INF) {
    npoint = 0;
    //printf("%d\n", npoint + 1);
    dist += mat[point][npoint];
    return;
  }
  price(npoint, n, mat, closed, dist);
}

void min_g(int *dist) {
  printf("\n The minimum price:\n");
  printf("%d\n", *dist);
}

int *run_greedy(int **afstand_matrix, int n) {
  /*int **afstand_matrix = (int **) calloc(n, sizeof(int *));
  for (int y = 0; y < n; ++y) {
    afstand_matrix[y] = (int *) calloc(n, sizeof(int));
  }
  if (afstand_matrix == NULL) {
    printf("Error! memory not allocated.");
    exit(-1);
  }*/

  int *closed = (int *) calloc(n, sizeof(int));
  if (closed == NULL) {
    printf("Error! memory not allocated.");
    exit(-1);
  }
/*
  afstand_matrix[0][0] = 1;
  afstand_matrix[0][1] = 10;
  afstand_matrix[0][2] = 100;
  afstand_matrix[1][0] = 1;
  afstand_matrix[1][1] = 20;
  afstand_matrix[1][2] = 30;
  afstand_matrix[2][0] = 1;
  afstand_matrix[2][1] = 60;
  afstand_matrix[2][2] = 70;
*/
  //matrix(n, afstand_matrix);
  //printf("\n The rute:\n\n");
  int *dist = (int *) calloc(1, sizeof(int));
  price(0, n, afstand_matrix, closed, dist);
  //min_g(dist);
  free(afstand_matrix);
  free(closed);
  return dist;
}