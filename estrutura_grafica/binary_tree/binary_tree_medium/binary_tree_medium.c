#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

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

void tree_print_dot_body(struct tree_node *root) {
    if (root != NULL)
    {
        tree_print_dot_body(root->left_child);
        printf("  \"%p\" [label=\"{%p|%d|{%p|%p}}\"];\n",
               (void *) root,
	       root,
	       root->value,
	       root->left_child,
	       root->right_child);
	if (root->left_child)
            printf("  \"%p\" -> \"%p\";\n", root, root->left_child);
	if (root->right_child)
            printf("  \"%p\" -> \"%p\";\n", root, root->right_child);
        tree_print_dot_body(root->right_child);
    }
}
 
void tree_print_dot(struct tree_node *root)
{
    printf("%s", DOT_HEADER);
    tree_print_dot_body(root);
    printf("%s", DOT_FOOTER);
}

void print_tree(struct tree_node *root) {
    if (root != NULL) {
        print_tree(root->left_child);
        printf("%d\n", root->value);
        print_tree(root->right_child);
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

    unsigned int n;
    
    int i, aux;

    n = atoi(argv[1]);

    int *v = malloc(n * sizeof(int));

    srand(time(NULL));
    
    for (i = 0; i < n; i++) {
        aux = rand();
        insert(&root, aux);
        v[i] = aux;
    }

    struct tree_node *node = search(root, v[rand() % n]);

    if (node != NULL) {
        printf("%d\nFound\n", node->value);
    } else {
        printf("\nNot found\n");
    }

    tree_print_dot(root);

    return 0;
}