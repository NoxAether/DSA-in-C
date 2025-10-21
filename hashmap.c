#include <stdio.h>
#include <stdlib.h>

// hashtable
typedef struct DATA {
    int key;
    int value;
} Data;

// global data array
Data *array;
// can store
int capacity = 10;
// current amount stored
int size = 0;

// returns the unique hash code to given key
int hashcode(int key) { return (key % capacity); }

// check if given input is prime or not
int if_prime(int n) {
    int i;
    if (n == 1 || n == 0)
        return 0;
    for (i = 2; i < n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// returns prime number just greater than arr cap.
int get_prime(int n) {
    if (n % 2 == 0)
        n++;
    for (; !if_prime(n); n += 2)
        ;
    return n;
}

void init_array() {
    int i;
    capacity = get_prime(capacity);
    array = (Data *)malloc(capacity * sizeof(Data));
    for (i = 0; i < capacity; i++) {
        array[i].key = 0;
        array[i].value = 0;
    }
}
// insert
void insert(int key) {
    int index = hashcode(key);
    if (array[index].value == 0) {
        // key not present, insert it
        array[index].key = key;
        array[index].value = 1;
        size++;
        printf("\n Key '%d' has been inserted \n", key);
    } else if (array[index].key == key) {
        // updating already existing key
        printf("\n Key '%d' already present, updating its value \n", key);
        array[index].value += 1;
    } else {
        // key cannot be inserted as the index is already containing some other
        // key
        printf("\n ELEMENT CANNOT BE INSERTED \n");
    }
}

// delete
void delete(int key) {
    int index = hashcode(key);
    if (array[index].value == 0)
        printf("\n This key does not exist");
    else {
        array[index].key = 0;
        array[index].value = 0;
        size--;
        printf("\n Key '%d' has been removed", key);
    }
}
// display
void display() {
    int i;
    for (i = 0; i < capacity; i++) {
        if (array[i].value == 0)
            printf("\n Array [%d] has no elements");
        else
            printf("\n array [%d] has elements -: \n key(%d) and value(%d) \t",
                   i, array[i].key, array[i].value);
    }
}
// size
int get_size() { return size; }
// search

int main(void) {}
