#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
  struct Node *prev;
};

struct Node *createNode(int value);

void createLinkedList(struct Node **head, struct Node **tail, int amount) {
  struct Node *current = NULL;

    for (; amount > 0; amount--) {
        struct Node *node = createNode(amount);

      if (!*head) {
        *head = node;
        current = node;
      } else {
          current->next = node;
          node->prev = current;
          current = node;
      }
    }
    *tail = current;
}

void freeLinkedList(struct Node *head) {
    struct Node *node = NULL;
  while (head != NULL) {
    node = head;
    head = node->next;
    free(node);
  }
}

void displayLinkedList(struct Node *head) {
  struct Node *node = head;
  while (node != NULL) {
    printf("%d%s", node->value, node->next ? " -> " : " -> NULL\n");
    node = node->next;
  }
}

struct Node *search(struct Node *head, int value) {
  struct Node *node = head;

  while (node != NULL) {
    if (node->value == value)
      return node;
    node = node->next;
  }
  return NULL;
}

void pushFront(struct Node **head, struct Node **toInsert) {
    (*toInsert)->next = *head;
    (*toInsert)->prev = NULL;

    if (*head) {
        (*head)->prev = *toInsert;
    }
    *head = *toInsert;
}

void pushBack() {}
void reverseList() {}

struct Node *createNode(int value) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node) {
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
  }
  return node;
}

void delete(struct Node **head, struct Node *toDelete) {
  if (toDelete->prev)
    toDelete->prev->next = toDelete->next;
  else
    *head = toDelete->next;

  if (toDelete->next)
    toDelete->next->prev = toDelete->prev;

  free(toDelete);
}

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;

    createLinkedList(&head, &tail, 20);

    displayLinkedList(head);

    struct Node *toInsert = createNode(21);

    pushFront(&head, &toInsert);

    displayLinkedList(head);

    delete(&head, search(head, 14));

    displayLinkedList(head);

    freeLinkedList(head);
}
