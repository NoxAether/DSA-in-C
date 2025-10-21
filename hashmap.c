#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HashMap with linked lists

// node in linked list
typedef struct Node {
  char *key;
  int value;
  struct Node *next;
} Node;

// hash table
typedef struct {
  Node **buckets; // array of linked list heads.
  int capacity; // number of buckets
  int size; // total key-value pairs
} HashTable;

// create a new node
Node *createNode(const char *key, int value) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = strdup(key);
  node->value = value;
  node->next = NULL;
  return node;
}
// free a node
void freeNode(Node *node) {
  free(node->key);
  free(node);
}
// Create hash table
HashTable *createTable(int capacity) {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  table->capacity = capacity;
  table->size = 0;
  table->buckets = (Node **)calloc(capacity, sizeof(Node*)); // all NULL
  return table;
}

unsigned int hash(const char *key, int capacity) {
  unsigned long hash = 5381;
  int c;

  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % capacity;
}
// insert key-value pair
void insert(HashTable *table, const char *key, int value) {
  unsigned int index = hash(key, table->capacity);
  Node *head = table->buckets[index];

  // check if key already exists
  Node *current = head;
  while (current) {
    if (strcmp(current->key, key) == 0) {
      // key exists so update
      current->value = value;
      return;
    }
    current = current->next;
  }
  // key does not exist
  Node *node = createNode(key, value);
  node->next = table->buckets[index]; // point to old head
  table->buckets[index] = node; // become new head
  table->size++;
}

// search for a key - returns value or -1 if not found
int search(HashTable *table, const char *key) {
  unsigned int index = hash(key, table->capacity);
  Node *current = table->buckets[index];

  while (current) {
    if (strcmp(current->key, key) == 0) {
      return current->value; // found
    }
    current = current->next;
  }
  return -1; // not found
}

// delete a key value pair
void delete(HashTable *table, const char *key) {
   unsigned int index = hash(key, table->capacity);
   Node *current = table->buckets[index];
   Node *prev = NULL;

   while (current) {
     if (strcmp(current->key, key) == 0) {
       if (prev == NULL) {
         // deleting head of list
         table->buckets[index] = current->next;
       } else {
         // deleting from middle/end
         prev->next = current->next;
       }
       freeNode(current);
       table->size--;
       return;
     }
     prev = current;
     current = current->next;
   }
   // key not found
}

// display hash table
void display(HashTable *table) {
  printf("Hash-Table\t(Capacity: %d, Size: %d):\n", table->capacity,
         table->size);
  for (int i = 0; i < table->capacity; i++) {
    printf(" Bucket[%d]: ", i);
    Node *current = table->buckets[i];
    if (!current)
      printf("EMPTY");
    else {
      while (current != NULL) {
        printf("{%s:%d}", current->key, current->value);
        if (current->next)
          printf(" -> ");
      current = current->next;
      }
    }
  printf("\n");
  }
}
// free the HashTable
void freeTable(HashTable *table) {
  for (int i = 0; i < table->capacity; i++) {
    Node *current = table->buckets[i];
    while (current) {
      Node *tmp = current;
      current = current->next;
      freeNode(tmp);
    }
  }
  free(table->buckets);
  free(table);
}

// iterator structure
typedef struct {
    HashTable *table;
    int current_bucket;    // which bucket we're in
    Node *current_node;    // which node in that bucket
} Iterator;

// create iterator
Iterator* createIterator(HashTable *table) {
    Iterator *it = (Iterator*)malloc(sizeof(Iterator));
    it->table = table;
    it->current_bucket = 0;
    it->current_node = NULL;

    // find first non-empty bucket
    while (it->current_bucket < table->capacity &&
           table->buckets[it->current_bucket] == NULL) {
        it->current_bucket++;
    }

    if (it->current_bucket < table->capacity) {
        it->current_node = table->buckets[it->current_bucket];
    }

    return it;
}

// get next key-value pair
int iteratorNext(Iterator *it, char **key, int *value) {
    if (it->current_node == NULL) {
        return 0;  // no more elements
    }

    // return current node's data
    *key = it->current_node->key;
    *value = it->current_node->value;

    // move to next node
    it->current_node = it->current_node->next;

    // if we reached end of current bucket, find next non-empty bucket
    while (it->current_node == NULL) {
        it->current_bucket++;
        if (it->current_bucket >= it->table->capacity) {
            break;  // reached end of table
        }
        it->current_node = it->table->buckets[it->current_bucket];
    }

    return 1;  // success
}

// free iterator
void freeIterator(Iterator *it) {
    free(it);
}

// reset iterator to beginning
void iteratorReset(Iterator *it) {
    it->current_bucket = 0;
    it->current_node = NULL;

    // find first non-empty bucket
    while (it->current_bucket < it->table->capacity &&
           it->table->buckets[it->current_bucket] == NULL) {
        it->current_bucket++;
    }

    if (it->current_bucket < it->table->capacity) {
        it->current_node = it->table->buckets[it->current_bucket];
    }
}

void step_through(Iterator *it, int steps, void (*callback)(char*, int)) {
    char *key;
    int value;

    for (int i = 0; i < steps && iteratorNext(it, &key, &value); i++) {
        if (callback != NULL) {
            callback(key, value);
        }
    }
}

// example callback function
void print_pair(char *key, int value) {
    printf("Stepped to: {%s: %d}\n", key, value);
}

int main() {
    HashTable* table = createTable(10);

    // insert some key-value pairs
    insert(table, "John", 12345);
    insert(table, "Alice", 67890);
    insert(table, "Bob", 11111);
    insert(table, "Sara", 22222);

    printf("=== Initial Table ===\n");
    display(table);

    printf("\n=== Search Tests ===\n");
    printf("John's value: %d\n", search(table, "John"));
    printf("Alice's value: %d\n", search(table, "Alice"));
    printf("Unknown key: %d\n", search(table, "Unknown"));

    printf("\n=== Update John's Value ===\n");
    insert(table, "John", 77777);  // Update existing key
    printf("John's updated value: %d\n", search(table, "John"));

    printf("\n=== Delete Bob ===\n");
    delete(table, "Bob");
    display(table);

    Iterator *it = createIterator(table);
    char *key;
    int value;

    // iterate through ALL pairs
    while (iteratorNext(it, &key, &value)) {
        printf("Key: '%s', Value: %d\n", key, value);
    }

    printf("\n=== Reset and Iterate Again ===\n");
    iteratorReset(it);

    while (iteratorNext(it, &key, &value)) {
        printf("Key: '%s', Value: %d\n", key, value);
    }

    freeIterator(it);
    freeTable(table);
    return 0;
}
