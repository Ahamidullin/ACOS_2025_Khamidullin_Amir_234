//
// Created by Амир Хамидуллин on 16.04.2025.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node* next; // иначе бы была бесконечная рукурсия. Указатель является остановкой
} Node;

// Выделить память под один Node (через malloc)
// Записать в поле data переданное значение
// Установить next = NULL
// Вернуть указатель на созданный узел


Node* CreateNode(int d){
  Node* noda = (Node*) malloc(sizeof(Node)); // malloc возвращает *void
  noda->data = d;
  // (*noda).data = d; или так, делаем разименование указателя тем самым получаем доступ к полю
  noda->next = NULL;
  return noda;
}

// void printNodes(Node* first_node){
//     while (first_node != NULL){
//         int data = first_node->data;
//         printf("%d ", data);
//         first_node = first_node->next;
//     }
//     printf("null\n");
// }

// Создаёт новый узел
// Устанавливает его next так, чтобы он указывал на старую голову (head)
// Возвращает этот новый узел — теперь он новый head

Node* AddFront(Node* head,int d){
  Node* noda = (Node*) malloc(sizeof(Node));
  noda->data = d;
  noda->next = head;
  return noda;
}

Node* reverseList(Node* head) {
  Node* prev = NULL;
  Node* current = head;
  Node* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  return prev;
}

void printList(Node* head){
  while (head != NULL){
    int data = head->data;
    printf("%d ", data);
    head = head->next;
  }
  printf("null\n");

}

void freeList(Node* head) {
  Node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int main(){
  int val;
  Node* head = NULL;

  while(1){
    scanf("%d", &val);
    if (val == 0) break;
    head = AddFront(head, val);
  }
  head = reverseList(head);

  printList(head);

  freeList(head);



  return 0;
}

