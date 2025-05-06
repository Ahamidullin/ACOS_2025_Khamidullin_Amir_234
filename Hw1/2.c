//
// Created by Амир Хамидуллин on 16.04.2025.
//

#include <stdio.h>
#include <stdlib.h>

void reverseArr(int* arr, int size){
  for (int i = 0; i < size/2; i++){
    int tmp = arr[size - i - 1];
    arr[size - i - 1] = arr[i];
    arr[i] = tmp;
  }
}

int main(){
  int n;
  scanf("%d", &n);
  int* arr = (int*) malloc(n * sizeof(int));

  for (int i = 0; i < n; i++){
    scanf("%d", &arr[i]);
  }

  reverseArr(arr, n);

  for (int i = 0; i < n; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);
  return 0;
}