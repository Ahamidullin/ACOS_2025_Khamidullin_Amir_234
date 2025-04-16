//
// Created by Амир Хамидуллин on 16.04.2025.
//

#include <stdio.h>
#include <stdlib.h>

int** transpose(int** arr, int n, int m){
  int **new_arr = (int**) malloc(m * sizeof(int*));
  for (int i = 0; i < m; i++) {
    new_arr[i] = (int*) malloc(n * sizeof(int));
  }
  for(int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      new_arr[j][i] = arr[i][j];
    }
  }
  free(arr);
  return new_arr;
}

/*
  0 1 2 3
0 1 2 3 4
1 5 6 7 8

  0 1
0 1 5
1 2 6
2 3 7
3 4 8
*/

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int **arr = (int**) malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    arr[i] = (int*) malloc(m * sizeof(int));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &arr[i][j]);
    }
  }
  printf("\n");
  arr = transpose(arr, n, m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  free(arr);
  return 0;
}