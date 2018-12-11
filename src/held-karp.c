#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "held-karp.h"

void setup(int **matrix, int **memo, int start_node, int size);
void solve(int **matrix, int **memo, int start_node, int size);
int calc_min_cost(int **matrix, int **memo, int start_node, int size);
void calc_best_plan(int **matrix, int **memo,
    int start_node, int size, int plan[]);
int in_subset(int i, int subset);
int combinations(int r, int n);
void combinations_subset(int r, int n, int *subsets);
void combinations_subset_helper(int j, int set,
    int at, int r, int n, int *subsets);
unsigned long factorial(unsigned long i);

int main(void) {
  int **matrix;
  matrix = calloc(20, sizeof(int*));
  int q;
  for(q=0;q<20;q++)
    matrix[q]=(int *) calloc(20, sizeof(int));

  int x, y;
  for(x = 0; x < 20; x ++) {
    for(y = 0; y < 20; y ++) matrix[x][y] = x+y;
  }
  int min_cost = 0;
  int start_node = 0;
  int a[20];
  int size = sizeof(a) / sizeof(int);
  held_karp(matrix, size, start_node, &min_cost, a);
}

void held_karp(int **matrix, int size,
    int start_node, int *min_cost, int plan[]) {
  int i; 
  int **memo; 
  memo = calloc(size, sizeof(int*));
  for(i=0;i<size;i++) {
    matrix[i]=(int *) calloc((int) pow(2, size), sizeof(int));
  }

  setup(matrix, memo, start_node, size);
}

/* finds the optimal route from start_node to i, as given in the distance
 * matrix. We bitshift the memo table to store the optimal route as 1's.
 * There's obviously no reason to calculate the otpimal route from start to 
 * start, so we skip that case */
void setup(int **matrix, int **memo, int start_node, int size) {
  for (int i = 0; i < size; i++) {
    if (i != start_node) {
      memo[i][1 << start_node | 1 << i] = matrix[start_node][i];
    }
  }
}

void solve(int **matrix, int **memo, int start_node, int size) {
  for (int i = 3; i < size; i++) {

  }
}

/* checks whether or not bit i in the subset is a 1 and returns a bool */
int in_subset(int i, int subset) {
  return ((1 << i) & subset) == 1;
}

int combinations(int r, int n) {
  return (factorial(n))/(factorial(r) * (factorial(n-r)));
} 

unsigned long factorial(unsigned long i) {
  if (i == 0) {
    return 1;
  }
  else {
    return (i * factorial(i - 1));
  }
}

void combinations_subset(int r, int n, int *subsets) {
  combinations_subset_helper(0, 0, 0, r, n, subsets);
}

void combinations_subset_helper(int j, int set,
    int at, int r, int n, int *subsets) {
  if (r == 0) {
    subsets[j] = set;
  }
  else {
    for (int i = at; i < n; i++) {
      set = set | (1 << i);

      combinations_subset_helper(j, set, i + 1, r - 1, n, subsets);

      set = set & ~(1 << i);
    }
  }
}
