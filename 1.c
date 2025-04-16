//
// Created by Амир Хамидуллин on 16.04.2025.
//
#include <stdio.h>

void swap(int *arg1, int *arg2){
  printf("swap: %p %p\n", arg1, arg2);
  int tmp = (*arg1); // значение по адрессу
  (*arg1) = (*arg2);
  (*arg2) = tmp;

}

int main(){
  int x, y;
  scanf("%d %d", &x, &y);
  printf("main: %p %p\n", &x, &y);

  swap(&x, &y);
  printf("%d %d", x, y);
  return 0;
}