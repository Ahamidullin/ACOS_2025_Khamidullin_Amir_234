#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node* next; // иначе бы была бесконечная рукурсия. Указатель является остановкой
} Node;

Node* CreateNode(int d){
  Node* noda = (Node*) malloc(sizeof(Node)); // malloc возвращает *void
  noda->data = d;
  // (*noda).data = d; или так, делаем разименование указателя тем самым получаем доступ к полю
  noda->next = NULL;
  return noda;
}

Node* PushBack(Node* head,int d){
  Node* noda = (Node*) malloc(sizeof(Node)); // malloc - выделяет на куче, а без него на стеке функции которая потом очищается \
  а надо еще вернуть
  noda->data = d;
  noda->next = NULL;

  if (head == NULL){
    return noda;
  }

  Node* current = head;

  while (current->next != NULL){
    current = current->next;
  }
  current->next = noda;
  return head;
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
    if (val == 0){
      break;
    }
    head = PushBack(head, val);
  }

  printList(head);
  head = reverseList(head);
  printList(head);
  freeList(head);

  return 0;
}

