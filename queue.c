#include <stdio.h>
#include <stdlib.h>

// double linked list for constant time
struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

struct Queue {
    struct Node *head;
    struct Node *tail;
    // used as a temp for positions in the linked list.
    struct Node *tmp;
};

struct Node *createNode(int value) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node) {
        node->value = value;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

void deleteHead(struct Queue *queue) {
    // if there is no queue
    if (!queue->head)
        return;
    // just remove the head
    if (queue->head->next) {
        queue->tmp = queue->head->next;
        queue->tmp->prev = NULL;
        free(queue->head);
        queue->head = queue->tmp;
    }
    // else the head is the only one there
    else {
        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
    }
}

struct Queue *initQueue() {
    struct Queue *queue = malloc(sizeof(struct Queue));

    queue->head = NULL;
    queue->tail = NULL;
    queue->tmp = NULL;

    return queue;
}
void freeQueue(struct Queue *queue) {
    // first ensure all internal nodes are freed;
    queue->tmp = NULL;
    while (queue->head != NULL) {
        queue->tmp = queue->head->next;
        free(queue->head);
        queue->head = queue->tmp;
    }

    // now free the queue
    free(queue);
}

void displayQueue(struct Queue *queue) {
    if (!queue->head)
        return;
    queue->tmp = queue->head;
    while (queue->tmp != NULL) {
        printf("%d%s", queue->tmp->value,
               queue->tmp->next != NULL ? " -> " : " -> NULL\n");
        queue->tmp = queue->tmp->next;
    }
}
// to implement
// return the value at the front
int peakFront(struct Queue *queue) { return queue->head->value; }
// return the value at the end.
int peekBack(struct Queue *queue) { return queue->tail->value; }
// return 1 or 0
int isEmpty(struct Queue *queue) {
    if (!queue->head)
        return 1;
    return 0;
}

// Would be cool
// return the size of the queue
int getSize(struct Queue *queue);
// search for the node that contains a value and assign that node to Queue->tmp
void contains(struct Queue *queue, int value);
// deep copy the queue
struct Queue *copyQueue(struct Queue *queue);
struct Queue *queueToArray(struct Queue *queue);

// Push back
void enqueue(struct Queue *queue, int value) {
    queue->tmp = createNode(value);
    if (!queue->tmp)
        return;

    if (!queue->tail) {
        // empty queue - new node is both head and tail
        queue->head = queue->tmp;
        queue->tail = queue->tmp;
    }
    // add to tail
    else {
        queue->tail->next = queue->tmp;
        queue->tmp->prev = queue->tail;
        queue->tail = queue->tmp;
    }
}

// Delete front
void dequeue(struct Queue *queue) {
    // deleteNode takes care of deleting and re arranging the "front"
    deleteHead(queue);
}

int main(void) {

    struct Queue *queue = initQueue();

    for (int i = 0; i < 100; i++) {
        enqueue(queue, i + 1);
    }

    displayQueue(queue);

    for (int i = 0; i < 50; i++) {
        dequeue(queue);
    }

    printf("\n\n");

    displayQueue(queue);
    freeQueue(queue);

    return 0;
}
