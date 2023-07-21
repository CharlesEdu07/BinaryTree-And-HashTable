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

void hash_print_dot_body(FILE *file, HashTable *hash_table) {
    fprintf(file, "  main_table [shape=record, label=\"");

    for (int i = 0; i < hash_table->m; i++) {
        if (i > 0) {
            fprintf(file, "|");
        }

        if (hash_table->nodes[i] == NULL) {
            fprintf(file, "<slot%d> NULL", i);
        } else {
            fprintf(file, "<slot%d> %p", i, (void *)hash_table->nodes[i]);
        }
    }

    fprintf(file, "\"];\n");

    for (int i = 0; i < hash_table->m; i++) {
        Node *current = hash_table->nodes[i];

        if (current != NULL) {
            fprintf(file, "  \"%p\" [shape=record, label=\"{%d|%p}\"];\n", (void *)current, current->value, (void *)current->next);
            fprintf(file, "  main_table:slot%d -> \"%p\";\n", i, (void *)current);

            while (current->next != NULL) {
                fprintf(file, "  \"%p\" -> \"%p\" [style=dotted];\n", (void *)current, (void *)current->next);
                current = current->next;
                fprintf(file, "  \"%p\" [shape=record, label=\"{%d|%p}\"];\n", (void *)current, current->value, (void *)current->next);
            }
        }
    }
}

int main(int argc, char **argv) {
    HashTable* table = create_hash_table(1);

    unsigned int n;

    int aux, *v;

    n = atoi(argv[1]);

    v = (int *)malloc(sizeof(int) * n);
    
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        aux = i;
        insert(table, aux);
        v[i] = aux;
    }

    print_hash_table(table);

    int search_index = rand() % n;

    if (search(table, v[search_index])) {
        printf("O valor %d foi encontrado.\n", v[search_index]);
    } else {
        printf("O valor %d não foi encontrado.\n", v[search_index]);
    }

    FILE *dot_file = fopen("hash.dot", "w");
    if (dot_file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    fprintf(dot_file, "digraph G {\n node [shape=record, height=0.6, width=1.5];\n edge [arrowhead=vee, arrowsize=0.8];\n");
    hash_print_dot_body(dot_file, table);
    fprintf(dot_file, "}\n");

    fclose(dot_file);

    destroy_hash_table(table);

    return 0;
}