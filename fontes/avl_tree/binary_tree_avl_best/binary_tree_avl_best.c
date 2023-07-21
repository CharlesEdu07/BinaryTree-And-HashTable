#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct tree_node {
    int value;
    struct tree_node* left_child;
    struct tree_node* right_child;
    unsigned int height;
};

int get_height(struct tree_node* node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int get_difference(struct tree_node* node) {
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left_child) - get_height(node->right_child);
}

void update_height(struct tree_node* node) {
    if (node == NULL) {
        return;
    }

    int left_height = get_height(node->left_child);
    int right_height = get_height(node->right_child);

    node->height = (left_height > right_height ? left_height : right_height) + 1;
}

struct tree_node* rotate_left(struct tree_node* node) {
    struct tree_node* new_root = node->right_child;

    node->right_child = new_root->left_child;

    new_root->left_child = node;

    update_height(node);
    update_height(new_root);

    return new_root;
}

struct tree_node* rotate_right(struct tree_node* node) {
    struct tree_node* new_root = node->left_child;

    node->left_child = new_root->right_child;

    new_root->right_child = node;

    update_height(node);
    update_height(new_root);
    
    return new_root;
}

struct tree_node* insert(struct tree_node* root, int value) {
    if (root == NULL) {
        root = malloc(sizeof(struct tree_node));
        root->value = value;
        root->left_child = NULL;
        root->right_child = NULL;
        root->height = 1;
    } else if (value < root->value) {
        root->left_child = insert(root->left_child, value);
    } else if (value > root->value) {
        root->right_child = insert(root->right_child, value);
    } else {
        return root;
    }

    update_height(root);

    int difference = get_difference(root);

    if (difference > 1 && value < root->left_child->value) {
        return rotate_right(root);
    }
    if (difference < -1 && value > root->right_child->value) {
        return rotate_left(root);
    }
    if (difference > 1 && value > root->left_child->value) {
        root->left_child = rotate_left(root->left_child);
        return rotate_right(root);
    }
    if (difference < -1 && value < root->right_child->value) {
        root->right_child = rotate_right(root->right_child);
        return rotate_left(root);
    }

    return root;
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
    struct tree_node* root = NULL;

    struct timespec start, end;
    unsigned int t, n;

    int i, aux, *arr;

    n = atoi(argv[1]);

    arr = malloc(n * sizeof(int));
    
    srand(time(NULL));

    for (i = 0; i < n; i++) {
        aux = rand();
        root = insert(root, aux);
        arr[i] = aux;
    }

    int search_value = root->value;

    clock_gettime(CLOCK_MONOTONIC, &start);
    struct tree_node *node = search(root, search_value);
    clock_gettime(CLOCK_MONOTONIC, &end);

    t = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

    printf("%u\n", t);

    return 0;
}