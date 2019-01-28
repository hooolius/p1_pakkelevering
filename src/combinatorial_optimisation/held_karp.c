#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "held_karp.h"
#include "../libs/dynamic_array.h"
#include "../libs/cleaner.h"

void setup(int **matrix, int **memo, int start_node, int size);
void solve(int **matrix, int **memo, int start_node, int size);
int calc_min_cost(int **matrix, int **memo, int start_node, int size);
void calc_best_plan(int **matrix, int **memo,
    int start_node, int size, int plan[]);
int in_subset(int i, int subset);
int combinations(int r, int n);
void combinations_subset(int r, int n, dyn_array_int *subsets);
void combinations_subset_helper(int set,
    int index_pos, int r, int n, dyn_array_int *subsets);

/**
 * @brief Main function of held_karp, from which all other functions are called
 * @param[in] matrix is the matrix of distances
 * @param[in] size is the size of the memo array
 * @param[in] start_node is the starting node
 * @param[out] plan is an array containing the total route
 * @return the total minimum cost of the solution 
 */
int held_karp(int **matrix, int size,
    int start_node, int plan[]) {

  int **memo = make_array(size, pow(2, size));
  int min_cost = INT_MAX;
  setup(matrix, memo, start_node, size);
  solve(matrix, memo, start_node, size);
  min_cost = calc_min_cost(matrix, memo, start_node, size);
  calc_best_plan(matrix, memo, start_node, size, plan);

  free_array(memo, size);
  free_array(matrix, size);

  return min_cost;
}

/**
 * @brief This function finds the optimal route from start_node to every other
 * node, as given in the distance matrix. There is no reason to calculate the
 * optimal route from start to start, so we skip that case
 * @param[in] matrix is a distance matrix
 * @param[out] memo is the bitshift table used to store the optimal route as 1's
 * @param[in] start_node is the starting node from which the route begins
 * @param[in] size is the size of the memo array
 */
void setup(int **matrix, int **memo, int start_node, int size) {
  for (int i = 0; i < size; i++) {
    if (i != start_node) {
      memo[i][1 << start_node | 1 << i] = matrix[start_node][i];
    }
  }
}
/**
 * @brief 
 * @param[in] matrix is a matrix of distances
 * @param[out] memo is the bitshift table used to store the optimal route as 1's
 * @param[in] start_node is the starting note from which the route begins
 * @param[in] size is the size of the memo array
 */
void solve(int **matrix, int **memo, int start_node, int size) {
  for (int r = 3; r <= size; r++) {
    dyn_array_int *subsets = make_dyn_array_i(10);
    combinations_subset(r, size, subsets);
    for (int i = 0; i < subsets->items; i++) {
      if (in_subset(start_node, subsets->integers[i])) {
        for (int next = 0; next < size; next++) {
          int min_dist = INT_MAX;
          if (next != start_node && in_subset(next, subsets->integers[i])) {
            int state = subsets->integers[i] ^ (1 << next);
            for (int end = 0; end < size; end++) {
              if (end != start_node && end != next
                  && in_subset(end, subsets->integers[i])) {
                int new_dist = memo[end][state] + matrix[end][next];
                if (new_dist < min_dist) {
                  min_dist = new_dist;
                }
              }
            }
          }
          memo[next][subsets->integers[i]] = min_dist;
        }
      }
    }
    free(subsets->integers);
    free(subsets);
  }
}


/**
 * @brief checks whether or not bit i in the subset is a 1 and returns a bool
 * @param[in] i is counter value in the subset which counts bits
 * @param[in] subset is a set of the matrix containing distances
 * @return if the bit is in the subset or not
 */
int in_subset(int i, int subset) {
  return !(((1 << i) & subset) == 0);
}


/**
 * @brief Generates all possible subsets of size n with r bits set to 1
 * @param[in] r how many bits in each set should be 1
 * @param[in] n the size of the subset
 * @param[out] subsets array of the generated subsets
 */
void combinations_subset(int r, int n, dyn_array_int *subsets) {
  combinations_subset_helper(0, 0, r, n, subsets);
}
/**
 * @brief Recursively generates all subsets
 * @param[in] set current set
 * @param[in] index_pos current index position
 * @param[in] r how many bits should be 1
 * @param[in] n the size of the subset
 * @param[out] subsets array of the generated subsets
 */
void combinations_subset_helper(int set,
    int index_pos, int r, int n, dyn_array_int *subsets) {
  if (r == 0) {
    add_int_to_end_i(subsets, set);
  }
  else {
    for (int i = index_pos; i < n; i++) {
      set = set | (1 << i);

      combinations_subset_helper(set, i + 1, r - 1, n, subsets);

      set = set & ~(1 << i);
    }
  }
}
/**
 * @brief Calculates the minimum cost of the total route
 * @param[in] matrix is a matrix of distance
 * @param[in] memo is the bitshift table used to store the optimal route as 1's
 * @param[in] start_node is the starting note from which the route begins
 * @param[in] size is the size of the matrix
 * @return the minimal cost of the total plan thorugh all notes
 */
int calc_min_cost(int **matrix, int **memo, int start_node, int size) {
  int plan_cost = INT_MAX;
  int end_state = (1 << size) - 1;
  int min_plan_cost = INT_MAX;

  for (int i = 0; i < size; i++) {
    if (i != start_node) {
      plan_cost = memo[i][end_state] + matrix[i][start_node];
      if (plan_cost < min_plan_cost) {
        min_plan_cost = plan_cost;
      }
    }
  }
  return min_plan_cost;
}
/**
 * @brief Finds the optimal route, and outputs it to the plan array
 * @param[in] matrix is a matrix of distances
 * @param[in] memo is the bitshift table used to store the optimal route as 1's
 * @param[in] start_node is the starting note from which the route begins
 * @param[in] size is the size of the matrix
 * @param[out] plan an array holding the optimal tour, by their index
 * in the matrix array
 */
void calc_best_plan(int **matrix, int **memo,
    int start_node, int size, int plan[]) {
  int last_index = start_node;
  int end_state = (1 << size) - 1;

  for (int i = size - 1; i >= 1; i--) {
    int index = -1;
    for (int j = 0; j < size; j++) {
      if (j != start_node && in_subset(j, end_state)) {
        if (index == -1) {
          index = j;
        }
        int prev_dist = memo[index][end_state] + matrix[index][last_index];
        int new_dist = memo[j][end_state] + matrix[j][last_index];
        index = new_dist < prev_dist ? j : index;
      }
    }
    plan[i] = index;
    end_state = end_state ^ (1 << index);
    last_index = index;
  }
  plan[0] = plan[size] = start_node;
}
