#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tree_node {
    int value;
    struct tree_node *left_child;
    struct tree_node *right_child;
};

void insert(struct tree_node **root, int value) {
    if (*root == NULL) {
        *root = malloc(sizeof(struct tree_node));
        (*root)->value = value;
        (*root)->left_child = NULL;
        (*root)->right_child = NULL;
    } else {
        if ((*root)->value < value) {
            insert(&(*root)->right_child, value);
        } else {
            insert(&(*root)->left_child, value);
        }
    }
}

struct tree_node *search(struct tree_node *root, int value) {
    if (root != NULL) {
        if (root->value == value) {
            return root;
        }

        if (root->value < value) {
            return search(root->right_child, value);
        }

        return search(root->left_child, value);
    }

    return NULL;
}

int main(int argc, char **argv) {
    struct tree_node *root = NULL;

    struct timespec start, end;
    unsigned int t, n;
    
    int i, aux;

    n = atoi(argv[1]);

    int *arr = malloc(n * sizeof(int));

    srand(time(NULL));
    
    for (i = 0; i < n; i++) {
        aux = rand();
        insert(&root, aux);
        arr[i] = aux;
    }

    int random_value = arr[rand() % n];

    clock_gettime(CLOCK_MONOTONIC, &start);
    struct tree_node *node = search(root, random_value);
    clock_gettime(CLOCK_MONOTONIC, &end);

    t = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    printf("%u\n", t);

    return 0;
}