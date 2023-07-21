#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    int m;
    int n;
    Node** nodes;
} HashTable;

void insert(HashTable* table, int value);

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

HashTable* create_hash_table(int m) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));

    table->m = m;
    table->n = 0;
    table->nodes = (Node**)malloc(sizeof(Node*) * m);

    for (int i = 0; i < m; i++) {
        table->nodes[i] = NULL;
    }

    return table;
}

int hash(int value, int m) {
    return value % m;
}

void rehash(HashTable* table, int value) {
    int new_m = table->m * 2;

    Node** new_nodes = (Node**)malloc(sizeof(Node*) * new_m);

    for (int i = 0; i < new_m; i++) {
        new_nodes[i] = NULL;
    }

    for (int i = 0; i < table->m; i++) {
        Node* current_node = table->nodes[i];

        while (current_node != NULL) {
            Node* next_node = current_node->next;

            int new_index = hash(current_node->value, new_m);

            current_node->next = new_nodes[new_index];
            new_nodes[new_index] = current_node;
            current_node = next_node;
        }
    }

    free(table->nodes);

    table->nodes = new_nodes;
    table->m = new_m;

    insert(table, value);
}

void insert(HashTable* table, int value) {
    int key = hash(value, table->m);

    if ((float)table->n / table->m >= 1.0) {
        rehash(table, value);
    } else {
        int index = hash(key, table->m);

        Node* new_node = create_node(value);

        if (table->nodes[index] == NULL) {
            table->nodes[index] = new_node;
        } else {
            Node* current_node = table->nodes[index];

            while (current_node->next != NULL) {
                current_node = current_node->next;
            }

            current_node->next = new_node;
        }

        table->n++;
    }
}

int search(HashTable* table, int value) {
    int index = hash(value, table->m);

    Node* current_node = table->nodes[index];

    while (current_node != NULL) {
        if (current_node->value == value) {
            return 1;
        }

        current_node = current_node->next;
    }

    return 0;
}

void print_hash_table(HashTable* table) {
    for (int i = 0; i < table->m; i++) {
        printf("[%d]->", i);

        Node* current_node = table->nodes[i];

        while (current_node != NULL) {
            printf("[%d]->", current_node->value);
            current_node = current_node->next;
        }

        printf("\n");
    }
}

void destroy_hash_table(HashTable* table) {
    for (int i = 0; i < table->m; i++) {
        Node* current_node = table->nodes[i];

        while (current_node != NULL) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            
            free(temp_node);
        }
    }

    free(table->nodes);
    free(table);
}

int main(int argc, char **argv) {
    HashTable* table = create_hash_table(1);

    struct timespec start, end;
    unsigned int t, n;

    n = atoi(argv[1]);
    
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        insert(table, i);
    }

    int search_index = rand() % n;

    clock_gettime(CLOCK_MONOTONIC, &start);
    int found = search(table, search_index);
    clock_gettime(CLOCK_MONOTONIC, &end);

    destroy_hash_table(table);

    t = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    printf("%u\n", t);

    return 0;
}